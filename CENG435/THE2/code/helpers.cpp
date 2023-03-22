#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <vector>
#include <string>
#include "common.h"
#include <iostream>

using namespace std;

sockaddr_in constructSocketAddress(int portNum, const char *IP)
{
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(IP);
    address.sin_port = htons(portNum);
    address.sin_zero[0] = 0;
    address.sin_zero[1] = 0;
    address.sin_zero[2] = 0;
    address.sin_zero[3] = 0;
    address.sin_zero[4] = 0;
    address.sin_zero[5] = 0;
    address.sin_zero[6] = 0;
    address.sin_zero[7] = 0;
    return address;
}

// Splits the read line into packets of the specified size
void addInputToPackets(string &line, vector<packet> *packets)
{
    packet curPacket;
    curPacket.type = DATA;
    curPacket.Ack = -1;
    curPacket.Seq = -1;
    clearPacket(curPacket);
    int payloadIndex = 0;
    int leng = line.length();
    for (int i = 0; i < leng; i++) // Does not include \0 at the end
    {
        if (payloadIndex < PAYLOADSIZE - 1)
        {
            curPacket.payload[payloadIndex] = line[i];
            payloadIndex++;
        }
        // The last byte of the payload
        else if (payloadIndex == PAYLOADSIZE - 1)
        {
            curPacket.payload[payloadIndex] = '\0';
            packets->push_back(curPacket);
            payloadIndex = 0;
            clearPacket(curPacket);
            curPacket.payload[payloadIndex] = line[i];
            payloadIndex++;
        }
        else
        {
            cerr << "A problem with the packet creation from input" << endl;
        }
    }

    // At the end of the loop, process the last packet if it exists
    if (payloadIndex < PAYLOADSIZE - 1)
    {
        curPacket.payload[payloadIndex] = '\n';
    }
    else if (payloadIndex == PAYLOADSIZE - 1)
    {
        curPacket.payload[payloadIndex] = '\0';
        packets->push_back(curPacket);
        payloadIndex = 0;
        clearPacket(curPacket);
        curPacket.payload[payloadIndex] = '\n';
    }

    packets->push_back(curPacket);
}
