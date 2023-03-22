#ifndef COMMON
#define COMMON

#define PACKETSIZE 16
#define PAYLOADSIZE 8
#define WINDOWSIZE 8
#define TIMEOUTTIME 1

#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <vector>

using namespace std;

enum packetType // Assuming that this type has a size of 4 bytes
{
    DATA,
    TERMINATE
};

typedef struct
{
    // TODO: Add Seq and Ack num functionality in the future
    packetType type;
    short int Seq;
    short int Ack;
    char payload[8]; // It should end with a \0

} packet;

typedef struct
{
    int socketDescriptor;
    sockaddr_in otherSide;
    bool *stopReading;
    bool *stopListening;
    bool *stopSending;
    bool *packetsACKArray;
    vector<packet> *packets;
    int *windowBase;
    int *senderNextSeqNum;
    int *receiverNextSeqNum;
    bool *clockRunning;
    clock_t *clockStartTime;
    bool *terminationACKSent;
    pthread_t *listenerId, *senderId, *readerId;
    pthread_mutex_t *shutdownMutex, *windowBaseMutex;
    int *numOfAck;

} threadArgs;

typedef struct
{
    bool connection;
} connectionRequest;

void printPacket(packet packet);

void clearPacket(packet &packet);

#endif