#ifndef main_h
#define main_h
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <syslog.h>

#include "chat_node.h"
#include "client_handler.h"



/* Preprocessor directives */
#define SERVER_ADDR "127.0.0.1" // loopback ip address
#define PORT 23657              // port the server will listen on


#define NUM_CONNECTIONS 5       // number of pending connections in the connection queue


#endif
