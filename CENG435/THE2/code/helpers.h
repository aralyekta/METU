#ifndef HELPERS
#define HELPERS

#include <arpa/inet.h>
#include <vector>

using namespace std;

sockaddr_in constructSocketAddress(int portNum, const char *IP);

void addInputToPackets(string &line, vector<packet> *packets);

void *listenAndPrint(void *args);

#endif