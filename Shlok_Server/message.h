#ifndef message_h
#define message_h
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


#include "properties.h"
#include "chat_node.h"


#define JOIN 0
#define LEAVE 1
#define SHUTDOWN 2
#define SHUTDOWN_ALL 3
#define NOTE 4


typedef struct message_struct{
    int type;
    char name[20];
    char message[80];
} Message;


void handle_message(Message *input, Nodes *chat_list);

#endif 
