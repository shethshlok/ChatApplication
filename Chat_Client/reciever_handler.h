#include <stdio.h>      // for perror()
#include <stdlib.h>     // for exit()
#include <string.h>     // for strlen()
#include <unistd.h>     // for close()
#include <sys/types.h>  // for select()
#include <sys/socket.h> // for socket(), bind(), listen(), accept(), send(), recv()
#include <netinet/in.h> // for sockaddr_in, htons(), INADDR_ANY
#include "properties.h"
#include <signal.h>
#include "misc.h"



/************************************************************************
 * function prototype declarations
 ************************************************************************/
// void reciever_handler(int client_socket);
void* getMessage(void* arg);
/************************************************************************
 * preprocessor directives
 ************************************************************************/
// #define SERVER_ADDR "142.11.244.236" // loopback ip address
// #define PORT 23657              // port the server will listen on

// // I cannot let go of the old-fashioned way :) - for readability ...
// #define FALSE false
// #define TRUE !false

// // number of pending connections in the connection queue
// #define NUM_CONNECTIONS 1