#ifndef MAIN
#define MAIN

#include <netdb.h>

void *listenAndPrint(void *args);

void *readStdin(void *args);

void *sendReadPackets(void *args);

#endif