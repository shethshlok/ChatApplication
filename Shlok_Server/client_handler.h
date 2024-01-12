#ifndef client_handler_h
#define client_handler_h
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
#include <stdbool.h>


#include "misc.h"
#include "message.h"
#include "chat_node.h"

/* Function prototypes */
typedef struct args_struct {
    Nodes *chat_room;
    int client_socket;
} Args;




void handle_client(Args *args);


#endif
