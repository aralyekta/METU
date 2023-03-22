#include <iostream>
#include "common.h"

using namespace std;

void printPacket(packet packet)
{
    for (int i = 0; i < PAYLOADSIZE; i++)
    {
        if (packet.payload[i] != '\0')
            cout << packet.payload[i];
        else
            break;
    }
}

void clearPacket(packet &packet)
{
    for (int i = 0; i < PAYLOADSIZE; i++)
    {
        packet.payload[i] = '\0';
    }
}
