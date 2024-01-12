/************************************************************************
 * libraries
 ************************************************************************/
#include <stdio.h>     // for printf(), fgets()
#include <stdlib.h>    // for exit()
#include <string.h>    // for strlen(), strcpy()
#include <unistd.h>    // for close()
#include <sys/socket.h>// for send()
#include "properties.h"
#include <stdbool.h>
#include "reciever_handler.h"
#include "message.h"

/************************************************************************
 * function prototype declarations
 ************************************************************************/
int sender_handler();

/************************************************************************
 * preprocessor directives
 ************************************************************************/
// #define SERVER_ADDR "142.11.244.236" // loopback ip address
// #define PORT 23657              // port the server will listen on

// I cannot let go of the old-fashioned way :) - for readability ...
#define FALSE false
#define TRUE !false

// number of pending connections in the connection queue
#define NUM_CONNECTIONS 1

#define PROPERTY_FILE "Property.txt"