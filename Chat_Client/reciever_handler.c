#include "reciever_handler.h"

/************************************************************************
 * MAIN
 ************************************************************************/


void* getMessage(void* arg) {
    Args* para = (Args*) arg;
    int server_socket;                 // descriptor of server socket
    struct sockaddr_in server_address; // for naming the server's listening socket
    int client_socket;
    char buffer[100];

    // sent when ,client disconnected
    signal(SIGPIPE, SIG_IGN);
    
    // create unnamed network socket for server to listen on
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    
    // name the socket (making sure the correct network byte ordering is observed)
    server_address.sin_family      = AF_INET;           // accept IP addresses
    server_address.sin_addr.s_addr = *para->ip; // accept clients on any interface
    server_address.sin_port        = para->port;       // port to listen on

    free(arg);
    
    // binding unnamed socket to a particular port
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    
    // listen for client connections (pending connections get put into a queue)
    if (listen(server_socket, 5) == -1) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

    while( true )
    {
        read_complete(client_socket, &buffer, sizeof(buffer));
        printf("%c\n", buffer );
    }

    close(client_socket);

}

