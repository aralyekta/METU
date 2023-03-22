import sys
import socket
import selectors
import types
import time
import jsonpickle


class Payload:
    def __init__(self, port_num, distance_vectors):
        self.port_num = port_num
        self.distance_vectors = distance_vectors


port_num = int(sys.argv[1])
payload = Payload(port_num, dict())
host = '127.0.0.1'
neighbors = []
sel = selectors.DefaultSelector()
timer = None
sent_counter = 0


def update_distances(given_payload):
    global payload
    global sent_counter
    updated = False
    sender_port_num = int(given_payload.port_num)
    received_distances = given_payload.distance_vectors
    if port_num == 3000:
        print(f"Received {sender_port_num}: {received_distances}")
        print(f"Before {payload.port_num}: {payload.distance_vectors}")
    for neighbor in received_distances:
        if payload.distance_vectors.get(int(neighbor)) is None:
            payload.distance_vectors[int(neighbor)] = payload.distance_vectors[sender_port_num] + \
                int(received_distances[neighbor])
            updated = True
    for received_node in received_distances:
        if received_node == port_num:
            continue
        try:
            calculated_distance = payload.distance_vectors[sender_port_num] + \
                int(received_distances[received_node])
            if calculated_distance < payload.distance_vectors[received_node]:
                updated = True
                payload.distance_vectors[int(
                    received_node)] = calculated_distance
        except:
            pass
    if port_num == 3000:
        print(f"After {payload.port_num}: {payload.distance_vectors}")
        print(f"Updated? {updated}")
    return updated


def obj_to_binary_string(object):
    json_string = jsonpickle.encode(object)
    return json_string.encode()


def read_node_info(port_num):
    global sent_counter
    global payload
    file = open(str(port_num) + '.costs', 'r')
    lines = [line.strip() for line in file]
    total_num = int(lines[0])
    for line in lines[1:]:
        splitted = line.split()
        port = int(splitted[0])
        distance = int(splitted[1])
        payload.distance_vectors[port] = distance
        neighbors.append(port)
    payload.distance_vectors[port_num] = 0
    sent_counter = len(neighbors)


def initiate_connections(host, ports):
    for port in ports:
        server_addr = (host, port)
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.setblocking(False)
        sock.connect_ex(server_addr)
        events = selectors.EVENT_READ | selectors.EVENT_WRITE
        data = types.SimpleNamespace(
            payload=obj_to_binary_string(payload))
        sel.register(sock, events, data=data)


def accept_connection(sock):
    conn, addr = sock.accept()
    conn.setblocking(False)
    data = types.SimpleNamespace(payload=None)
    events = selectors.EVENT_READ | selectors.EVENT_WRITE
    sel.register(conn, events, data=data)


def handle_data(key, mask):
    global timer
    global sent_counter
    sock = key.fileobj
    data = key.data
    if mask & selectors.EVENT_READ:
        recvd_data = sock.recv(1024)
        if recvd_data:
            decoded_data = jsonpickle.decode(recvd_data)
            if port_num == 3005:
                print(
                    f"Received data: {decoded_data.port_num} {decoded_data.distance_vectors}")
            if update_distances(decoded_data):
                data.payload = obj_to_binary_string(payload)
                sent_counter = len(neighbors)
            timer = time.time()
        else:
            sel.unregister(sock)
            sock.close()
    if mask & selectors.EVENT_WRITE:
        if data.payload and sent_counter >= 0:
            if port_num == 3000:
                print(f"Data will be sent to {sock}, {data.payload}")
            sent = sock.send(data.payload)
            data.payload = data.payload[sent:]
            if (data.payload is None):
                data.payload = obj_to_binary_string(payload)
                sent_counter -= 1


read_node_info(port_num)

# Set the port up
lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
lsock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
lsock.bind((host, port_num))
lsock.listen()
lsock.setblocking(False)
sel.register(lsock, selectors.EVENT_READ, data=None)

time.sleep(0.1)
# Connect to the neighbors
initiate_connections(host, neighbors)
time.sleep(0.1)

timer = time.time()

try:
    while True:
        if (time.time() - timer >= 5):
            # print(port_num, time.time(), timer)
            break
        events = sel.select(timeout=None)
        for key, mask in events:
            if key.data is None:
                accept_connection(key.fileobj)
            else:
                handle_data(key, mask)
except KeyboardInterrupt:
    pass
finally:
    sel.close()

for neighbor in payload.distance_vectors:
    print(f"{port_num} -{neighbor} | {payload.distance_vectors[neighbor]}")
