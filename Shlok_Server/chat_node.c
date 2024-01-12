#include "chat_node.h"

// A set of functions to handle the clients of a given chat room through a linked list


// add a node to the chatroom list of nodes
void add_node(Nodes *nodes, Chat_Node *newNode){
    nodes->last->nextNode = newNode;
    nodes->last->nextNode = (Chat_Node*) malloc(sizeof(Chat_Node));
    nodes->last->nextNode->nextNode = NULL;
    nodes->last = nodes->last->nextNode;
}


// given attributes, assign them into a new node
Chat_Node* create_node(char *name, char* ipPort){

    Chat_Node *temp; // Declare a node

    temp = (Chat_Node*)malloc(sizeof(Chat_Node)); // allocate memory using malloc()

    char *token = strtok(ipPort, " ");

    temp->name = name;
    temp->ip = token;
    token = strtok(NULL, " ");
    temp->port = atoi(token);
    temp->nextNode = NULL;

    return temp; // return the new node
}

// Get a node by name
Chat_Node* get_node(char *name, Nodes *nodes){
    Chat_Node *temp = nodes->first;

    while(temp->nextNode){
        if (strcmp(temp->name, name) == 0){
            return temp;
        }
        temp = temp->nextNode;
    }
    return NULL;
}


// Remove a node from the current list of connected clients
void remove_node(Nodes *nodes, Chat_Node *node){

    Chat_Node *temp = nodes->first;

    // loop through chat list
    while(temp->nextNode){

        // if we get to the node that needs removing
        if (strcmp(temp->name,node->name) == 0 ){

            temp->nextNode = node->nextNode;
            free(node);
        }
        temp = temp->nextNode;
    }
}



Nodes* new_chat_list(void){
    // make room for a PropertyList

    Nodes* node_list = (Nodes*) malloc(sizeof(Nodes));

    node_list->first = (Chat_Node*) malloc(sizeof(Chat_Node));

    node_list->first->nextNode = NULL;
    node_list->last = node_list->first;
    
    return node_list;
}



// Given a name and the chat_room list, check if the name exists inside a connected node
bool is_joined(Nodes *nodes, char *name){

    Chat_Node *temp = nodes->first;

    // Loop through the chat room list
    while(temp->nextNode != NULL){

        // check if the ip address' match
        if (strcmp(name, temp->name) == 0){
            // the name exists, bool must also be set to true already
            return true;
        }
    }
    return false;  
}



// Send all nodes a given message, except for the given node, which is our sender
int send_all_nodes_except_sender(Nodes *nodes, Chat_Node *node, char *message){

    Chat_Node *temp = nodes->first;
    int client_socket;                  // client side socket
    struct sockaddr_in client_address;  // client socket naming struct

    bool hello = false;
    

    // loop through list
    while(temp->nextNode){

        printf("114\n");
        
        // if we are not looking at the sender node we can wrtie to the socket of that node
        if (hello){
            
            // create an unnamed socket, and then name it
            client_socket = socket(AF_INET, SOCK_STREAM, 0);
            // create addr struct
            client_address.sin_family = AF_INET;

            printf("124\n");


            client_address.sin_addr.s_addr = inet_addr(temp->ip);
            client_address.sin_port = htons(temp->port);

            printf("130 inside the if\n");

            // connect to server socket
            if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1) {
                perror("Error connecting to server!\n");
                exit(EXIT_FAILURE);
            }

            printf("138 after connecting\n");

            write(client_socket, &message, sizeof(message));

            printf("Hello8\n");

            close(client_socket);
        }
        else
        {
            
            // create an unnamed socket, and then name it
            client_socket = socket(AF_INET, SOCK_STREAM, 0);
            // create addr struct
            client_address.sin_family = AF_INET;

            printf("PORT: %d\n", temp->port);
            printf("ip: %s\n", *temp->ip);
            
            client_address.sin_addr.s_addr = inet_addr(temp->ip);
            printf("Hello8\n");

            client_address.sin_port = htons(temp->port);
            
            printf("Hello9\n");
            
            // connect to server socket
            if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1) {
                perror("Error connecting to server!\n");
                exit(EXIT_FAILURE);
            }

            write(client_socket, &message, sizeof(message));

            close(client_socket);

            printf("Hello10\n");
        }

        temp = temp->nextNode;
    }
    return 0;
}
