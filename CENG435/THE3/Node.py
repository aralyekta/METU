import sys
import socket
import selectors
import time
import jsonpickle


class Payload:
    def __init__(self, port_num, distance_vectors):
        self.port_num = port_num
        self.distance_vectors = distance_vectors


port_num = int(sys.argv[1])
distance_vectors = dict()
host = '127.0.0.1'
neighbors = []
selector = selectors.DefaultSelector()
timer = None
send_queue = {}
TIMEOUT = 5
ports = [port_num]


def update_distances(given_payload):
    updated = False
    sender_port_num = int(given_payload.port_num)
    received_distances = given_payload.distance_vectors
    for neighbor in received_distances:
        if distance_vectors.get(int(neighbor)) is None:
            distance_vectors[int(neighbor)] = distance_vectors[sender_port_num] + \
                int(received_distances[neighbor])
            updated = True
    for received_node in received_distances:
        if received_node == port_num:
            continue
        try:
            calculated_distance = distance_vectors[sender_port_num] + \
                int(received_distances[received_node])
            if calculated_distance < distance_vectors[int(received_node)]:
                updated = True
                distance_vectors[int(
                    received_node)] = calculated_distance
        except:
            pass
    if updated:
        payload = Payload(port_num, distance_vectors)
        for key in send_queue:
            send_queue[key].append(obj_to_binary_string(payload))


def obj_to_binary_string(object):
    json_string = jsonpickle.encode(object)
    return json_string.encode()


def read_node_info(port_num):
    file = open(str(port_num) + '.costs', 'r')
    lines = [line.strip() for line in file]
    distance_vectors[port_num] = 0
    for line in lines[1:]:
        splitted = line.split()
        port = int(splitted[0])
        distance = int(splitted[1])
        distance_vectors[port] = distance
        neighbors.append(port)
        ports.append(port)


def initiate_connections(host, ports):
    for port in ports:
        server_addr = (host, port)
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.setblocking(False)
        sock.connect_ex(server_addr)
        events = selectors.EVENT_READ | selectors.EVENT_WRITE
        selector.register(sock, events)
        send_queue[sock] = [obj_to_binary_string(
            Payload(port_num, distance_vectors))]


def accept_connection(sock):
    conn, addr = sock.accept()
    conn.setblocking(False)
    events = selectors.EVENT_READ | selectors.EVENT_WRITE
    selector.register(conn, events)


def read_or_send(key, mask):
    global timer
    sock = key.fileobj
    # If the server is the receiver
    if mask & selectors.EVENT_READ and sock.getsockname() == (host, port_num):
        recvd_data = sock.recv(1)
        if recvd_data:
            recvd_list = [recvd_data.decode()]
            braces = 1
            while (braces >= 1):
                recvd_data = sock.recv(1)
                decoded = recvd_data.decode()
                recvd_list.append(decoded)
                if decoded == '}':
                    braces -= 1
                elif decoded == '{':
                    braces += 1
            decoded_data = ''.join(recvd_list)
            decoded_payload = jsonpickle.decode(decoded_data.encode())

            update_distances(decoded_payload)
            timer = time.time()
        else:
            selector.unregister(sock)
            sock.close()
    # If the server is the sender
    elif mask & selectors.EVENT_WRITE and sock.getpeername()[1] in ports:
        if send_queue[sock]:
            data = send_queue[sock].pop(0)
            while (data != b''):
                sent = sock.send(data)
                data = data[sent:]


read_node_info(port_num)

# Set the socket up
server_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_sock.bind((host, port_num))
server_sock.listen()
server_sock.setblocking(False)
selector.register(server_sock, selectors.EVENT_READ)

time.sleep(0.1)
# Connect to the neighbors
initiate_connections(host, neighbors)
time.sleep(0.1)

timer = time.time()

while True:
    if (time.time() - timer >= TIMEOUT):
        break
    events = selector.select(timeout=None)
    for key, mask in events:
        if key.fileobj == server_sock:
            accept_connection(key.fileobj)
        else:
            read_or_send(key, mask)

time.sleep((port_num - 3000) * 0.01)
sorted_distances = []
for neighbor in distance_vectors:
    sorted_distances.append((neighbor, distance_vectors[neighbor]))

sorted_distances.sort(key=lambda el: el[0])
for sorted_distance in sorted_distances:
    neighbor = sorted_distance[0]
    distance = sorted_distance[1]
    print(f"{port_num} - {neighbor} | {distance}")
