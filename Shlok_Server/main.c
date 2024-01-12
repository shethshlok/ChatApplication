#include "main.h"


/* ************************************************************************* */
/* MAIN                                                                      */
/* ************************************************************************* */

int main(int argc, char** argv) {
    int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket
    char *buffer;
    

    // create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // name the socket (making sure the correct network byte ordering is observed)
    server_address.sin_family      = AF_INET;           // accept IP addresses
    server_address.sin_addr.s_addr = htonl(INADDR_ANY); // accept clients on any interface
    server_address.sin_port        = htons(PORT);       // port to listen on
    
    // binding unnamed socket to a particular port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) != 0) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }
    
    // listen for client connections (pending connections get put into a queue)
    if (listen(server_socket, NUM_CONNECTIONS) != 0) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }
    
    // server loop
    printf("Starting Chat!\n");

    Chat_Node *new = NULL;
    Nodes *chat_room = new_chat_list();

    // create a structure to hold our thread arguments, the chatroom list and the client socket
    Args *args = (Args*) malloc(sizeof(Args));

    


    //Mutex Lock

    // Main Server Loop
    while (true) {


        int client_socket = accept(server_socket, NULL, NULL);

        // Assign struct arguments and pass them along to the thread
        args->chat_room = chat_room;

        read_complete(client_socket, buffer, 4);

        printf("%s\n", buffer);

        printf("first read done\n");
        
        

        // create thread to handle the client
        pthread_t thread;

        // put thread arguments into a struct to hand to the thread
        if (pthread_create(&thread, NULL, &handle_client, (void*)args) != 0) {
            perror("Error creating thread");
            exit(EXIT_FAILURE);
        }
        
        // detach the thread so that we don't have to wait (join) with it to reclaim memory.
        // memory will be reclaimed when the thread finishes.
        if (pthread_detach(thread) != 0) {
            perror("Error detaching thread");
            exit(EXIT_FAILURE);
        }

        // unlock here
    }
}
