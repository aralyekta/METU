#include <stdio.h>
#include "common.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "helpers.h"
#include <pthread.h>
#include <string.h>
#include <vector>
#include <pthread.h>
#include <signal.h>
#include <time.h>

using namespace std;

// Listens for the packets from the other end
// In the case of a termination packet, initiate the termination sequence
//      (it could be either the initial termination packet or its ACK)
// In the case of a data packet, process it according to its seq/ack number
//      If the seq number matches, keep on reading the next packets
//      If not, resend an ACK for the latest read packet
void *listenAndPrint(void *args)
{
    threadArgs *castedArguments = (threadArgs *)args;
    packet curPacket;
    sockaddr_in otherSide = castedArguments->otherSide;
    int socketDescriptor = castedArguments->socketDescriptor;
    bool *stopReading = castedArguments->stopReading;
    bool *stopListening = castedArguments->stopListening;
    bool *stopSending = castedArguments->stopSending;
    bool *ackArray = castedArguments->packetsACKArray;
    int *windowBase = castedArguments->windowBase;
    int *senderNextSeqNum = castedArguments->senderNextSeqNum;
    int *receiverNextSeqNum = castedArguments->receiverNextSeqNum;
    vector<packet> *packets = castedArguments->packets;
    bool *clockRunning = castedArguments->clockRunning;
    clock_t *clockStartTime = castedArguments->clockStartTime;
    pthread_mutex_t *shutdownMutex = castedArguments->shutdownMutex;
    pthread_mutex_t *windowBaseMutex = castedArguments->windowBaseMutex;
    int *numOfAck = castedArguments->numOfAck;

    socklen_t leng = sizeof(otherSide);
    while (true)
    {
        recvfrom(socketDescriptor, &curPacket, PACKETSIZE, MSG_WAITALL, (sockaddr *)&otherSide, &leng);
        cerr << "Received packet. Seq: " << curPacket.Seq << " Ack: " << curPacket.Ack << " Type: " << curPacket.type << "\n";

        pthread_mutex_lock(shutdownMutex);
        // If we are in a termination sequence or the received packet is a termination packet
        if (*stopListening || curPacket.type == TERMINATE)
        {
            cerr << "The received packet will be used for termination\n";
            // I am the sender and I received the ACK message of the termination request I sent
            if ((*stopListening || curPacket.Seq == *receiverNextSeqNum) && curPacket.Ack != -1)
            {
                cerr << "Received the termination ACK packet\n";
                *stopReading = true;
                pthread_mutex_unlock(shutdownMutex);
                break;
            }
            // I am the receiver of the initial terminate packet
            else if (curPacket.Seq == *receiverNextSeqNum && curPacket.Ack == -1)
            {
                cerr << "Received the termination request\n";
                *stopListening = true;
                packet shutdownAckPacket;
                shutdownAckPacket.Ack = *receiverNextSeqNum;
                shutdownAckPacket.type = TERMINATE;
                // Add the ACK packet of the termination request
                packets->push_back(shutdownAckPacket);
                *stopReading = true;

                pthread_mutex_unlock(shutdownMutex);
            }
        }
        else
        {
            if (curPacket.type == DATA)
            {
                pthread_mutex_lock(windowBaseMutex);
                // Update the window base according to the ACK message
                // Since the window base is updated, update the number of acks (used while sending) in it as well
                if (curPacket.Ack + 1 > *windowBase)
                {
                    *windowBase = curPacket.Ack + 1;
                    *numOfAck = 0;
                }
                pthread_mutex_unlock(windowBaseMutex);
                if (*windowBase == *senderNextSeqNum)
                {
                    // If the received packet is expected, stop the timer
                    *clockRunning = false;
                }
                else
                {
                    // If the received packet is not expected, start the timer
                    *clockRunning = true;
                    *clockStartTime = clock() / CLOCKS_PER_SEC;
                }

                // If the received packet is an ACK packet, increment the seq number we expect
                if (curPacket.Ack != -1)
                {
                    (*receiverNextSeqNum)++;
                }
                // If we got the expected data packet, process it and wait for the next ones
                if (curPacket.Seq == *receiverNextSeqNum && curPacket.Ack == -1)
                {
                    printPacket(curPacket);
                    packet ACKPacket;
                    ACKPacket.Ack = *receiverNextSeqNum;
                    ACKPacket.type = DATA;
                    packets->push_back(ACKPacket);
                    cerr << "Added an ACK packet for the received packet with Seq: " << (*receiverNextSeqNum) << "\n";
                    (*receiverNextSeqNum)++;
                }
                // If we got an unexpected data packet, send an ACK for the latest processed packet and wait for the expected packet
                else if (curPacket.Ack == -1)
                {
                    packet ACKPacket;
                    ACKPacket.Ack = (*receiverNextSeqNum) - 1;
                    ACKPacket.type = DATA;
                    packets->push_back(ACKPacket);
                    cerr << "Readded an ACK with Ack: " << ACKPacket.Ack << "\n";
                }
            }
            pthread_mutex_unlock(shutdownMutex);
        }
        clearPacket(curPacket);
    }
    // While exiting, kill the other threads
    pthread_kill(*(castedArguments->readerId), SIGINT);
    pthread_kill(*(castedArguments->senderId), SIGINT);
}

// Reads the processed packets list and pushes them to the other application
// Sends data in accordance with the window. ACK packets are not included in this window and are ignored while
//   doing the window calculations
void *sendReadPackets(void *args)
{
    threadArgs *castedArguments = (threadArgs *)args;

    sockaddr_in otherSide = castedArguments->otherSide;
    int socketDescriptor = castedArguments->socketDescriptor;
    bool *stopReading = castedArguments->stopReading;
    bool *stopListening = castedArguments->stopListening;
    bool *stopSending = castedArguments->stopSending;
    vector<packet> *packets = castedArguments->packets;
    bool *ackArray = castedArguments->packetsACKArray;
    int *windowBase = castedArguments->windowBase;
    int *senderNextSeqNum = castedArguments->senderNextSeqNum;
    int *receiverNextSeqNum = castedArguments->receiverNextSeqNum;
    bool *clockRunning = castedArguments->clockRunning;
    clock_t *clockStartTime = castedArguments->clockStartTime;
    pthread_mutex_t *shutdownMutex = castedArguments->shutdownMutex;
    pthread_mutex_t *windowBaseMutex = castedArguments->windowBaseMutex;
    int *numOfAck = castedArguments->numOfAck;

    while (true)
    {
        if (*stopSending)
            continue;

        // If we have packets to process
        if (!packets->empty() && *senderNextSeqNum < packets->size())
        {
            pthread_mutex_lock(windowBaseMutex);
            // If either we still have packets not sent in the window or the current packet is an ACK
            if (*senderNextSeqNum < *windowBase + WINDOWSIZE + (*numOfAck) || (*packets)[*senderNextSeqNum].Ack != -1)
            {
                // If it is an ACK, we increase the practical window size as we ignore ACKs
                if ((*packets)[*senderNextSeqNum].Ack != -1)
                    numOfAck++;
                if (*senderNextSeqNum > packets->size())
                {
                    pthread_mutex_unlock(windowBaseMutex);
                    continue;
                }
                packet curPacket = (*packets)[*senderNextSeqNum];
                curPacket.Seq = *senderNextSeqNum;
                sendto(socketDescriptor, &curPacket, PACKETSIZE, MSG_CONFIRM, (const sockaddr *)&otherSide, sizeof(otherSide));

                if (curPacket.type == TERMINATE)
                {
                    *stopSending = true;
                    // If it is a termination packet, notify the other threads
                    pthread_mutex_lock(shutdownMutex);
                    *stopListening = true;
                    pthread_mutex_unlock(shutdownMutex);
                    if (curPacket.Ack == -1)
                        cerr << "Sent a termination request\n";
                    else // If this termination packet is an ACK packet, shut down the application as the other end is
                         // already shut down
                    {
                        cerr << "Sent a termination ACK\n";
                        pthread_kill(*(castedArguments->listenerId), SIGINT);
                        pthread_kill(*(castedArguments->readerId), SIGINT);
                        pthread_mutex_unlock(windowBaseMutex);
                        break;
                    }
                }
                cerr << "Sent a packet from the window. Seq: " << curPacket.Seq << " Ack: " << curPacket.Ack << " Type: " << curPacket.type << "\n";
                (*senderNextSeqNum)++;
            }
            pthread_mutex_unlock(windowBaseMutex);
        }
    }
}

// Reads the stdin and processes the input to packets and adds them to the packet list shared by every thread
// In the case of 3 consecutive newline characters, constructs a termination packet
void *readStdin(void *args)
{
    threadArgs *castedArguments = (threadArgs *)args;
    sockaddr_in otherSide = castedArguments->otherSide;
    int socketDescriptor = castedArguments->socketDescriptor;
    bool *stopReading = castedArguments->stopReading;
    bool *stopListening = castedArguments->stopListening;
    bool *stopSending = castedArguments->stopSending;
    vector<packet> *packets = castedArguments->packets;
    string line;
    int shutdownCount = 0;
    int *senderNextSeqNum = castedArguments->senderNextSeqNum;
    while (true)
    {
        // If the program is in an exit state
        if (*stopReading)
        {
            sleep(0.5);
            break;
        }

        // If the program sent a termination packet but waits for its ACK packet
        if (*stopListening)
        {
            continue;
        }

        getline(cin, line);

        if (line[0] == '\0')
        {
            shutdownCount++;
            if (shutdownCount == 3)
            // Assuming that packets coming from the other end does not reset the shutdown sequence
            {
                packet shutdownPacket;
                clearPacket(shutdownPacket);
                shutdownPacket.type = TERMINATE;
                shutdownPacket.Ack = -1;
                packets->push_back(shutdownPacket);
                continue;
            }
        }
        else
        {
            // If the input is not a newline, shutdown sequence is reset
            shutdownCount = 0;
        }

        // Separate the input into packets and add them to the given packets argument
        addInputToPackets(line, packets);
    }
}