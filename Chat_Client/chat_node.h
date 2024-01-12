#ifndef chat_node_h
#define chat_node_h
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
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>




// Struct that holds client information
typedef struct chat_node_struct {
    char* name;
    char* ip;
    int port;
    struct chat_node_struct* nextNode;
} Chat_Node;



typedef struct node_list_struct {
    Chat_Node* first;
    Chat_Node* last;
} Nodes;


void add_node();
Chat_Node* create_node(char *name, char ip, int port);
bool is_joined(Nodes *nodes, char *message);
Chat_Node* get_node(char *name, Nodes *nodes);
void remove_node(Nodes *nodes, Chat_Node *node);
int send_all_nodes_except_sender(Nodes *nodes, Chat_Node *node, char *message);



Nodes* new_chat_list(void);


#endif
