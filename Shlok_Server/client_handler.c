#include "client_handler.h"


// Thread function that handles the servers clients
void handle_client(Args *args) {
    char input[100];

    Nodes *chat_room = args->chat_room;
    int client_sock = args->client_socket;


    printf("handle client\n");



    // Read in the message from the client
    read_complete(client_sock, &input, sizeof(input));

    close(client_sock);
    printf("After read comeplete\n");


    // Handle the message through our message handler
    handle_message(input, chat_room);
    
}




