#include <stdio.h>
#include "common.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "helpers.h"
#include "main.h"
#include <pthread.h>
#include <string.h>
#include <vector>
#include <pthread.h>

using namespace std;

int main(int argc, char *argv[])
{
    char *serverIP, *clientIP;
    int serverPort, clientPort;
    serverPort = atoi(argv[1]);
    clientPort = atoi(argv[2]);
    serverIP = argv[3];
    clientIP = argv[4];

    // Define the arguments
    bool stopListening = false;
    bool stopReading = false;
    bool stopSending = false;
    bool sentPacketACKs[WINDOWSIZE];
    memset(sentPacketACKs, false, sizeof(sentPacketACKs));
    vector<packet> packets;
    int windowBase = 0;
    int senderNextSeqNum = 0;
    int receiverNextSeqNum = 0;
    bool clockRunning = false;
    clock_t clockStartTime = 0;
    bool terminationACKSent = false;
    pthread_t listenerId = 0;
    pthread_t senderId = 0;
    pthread_t readerId = 0;
    pthread_mutex_t shutdownMutex, windowBaseMutex;
    pthread_mutex_init(&shutdownMutex, NULL);
    pthread_mutex_init(&windowBaseMutex, NULL);
    int numOfAck = 0;
    struct sockaddr_in serverAddr, clientAddr;

    // Create the socket used for listening the other end
    int socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0);
    if (socketDescriptor < 0)
    {
        cerr << "Socket could not be opened" << endl;
        return -1;
    }

    serverAddr = constructSocketAddress(serverPort, serverIP);
    clientAddr = constructSocketAddress(clientPort, clientIP);

    connectionRequest request;
    request.connection = true;

    // Bind the socket to the address given in the command line argument
    int bindRes = bind(socketDescriptor, (const sockaddr *)&clientAddr, sizeof(clientAddr));
    if (bindRes < 0)
    {
        cerr << "Bind failed" << endl;
        return -2;
    }

    cerr << "Will send connection request to the server" << endl;

    sendto(socketDescriptor, &request, 1, MSG_CONFIRM, (const sockaddr *)&serverAddr, sizeof(serverAddr));

    threadArgs threadArguments;
    threadArguments.otherSide = serverAddr;
    threadArguments.socketDescriptor = socketDescriptor;
    threadArguments.stopListening = &stopListening;
    threadArguments.stopReading = &stopReading;
    threadArguments.stopSending = &stopSending;
    threadArguments.packets = &packets;
    threadArguments.packetsACKArray = sentPacketACKs;
    threadArguments.windowBase = &windowBase;
    threadArguments.senderNextSeqNum = &senderNextSeqNum;
    threadArguments.receiverNextSeqNum = &receiverNextSeqNum;
    threadArguments.clockRunning = &clockRunning;
    threadArguments.clockStartTime = &clockStartTime;
    threadArguments.terminationACKSent = &terminationACKSent;
    threadArguments.listenerId = &listenerId;
    threadArguments.readerId = &readerId;
    threadArguments.senderId = &senderId;
    threadArguments.shutdownMutex = &shutdownMutex;
    threadArguments.windowBaseMutex = &windowBaseMutex;
    threadArguments.numOfAck = &numOfAck;

    // Start the threads
    pthread_create(&readerId, nullptr, &readStdin, (void *)&threadArguments);
    pthread_create(&senderId, nullptr, &sendReadPackets, (void *)&threadArguments);
    pthread_create(&listenerId, nullptr, &listenAndPrint, (void *)&threadArguments);

    pthread_join(readerId, nullptr);
    pthread_join(senderId, nullptr);
    pthread_join(listenerId, nullptr);

    close(socketDescriptor);
    return 0;
}