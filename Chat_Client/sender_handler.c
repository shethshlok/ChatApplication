#include "sender_handler.h"

/************************************************************************
 * MAIN
 ************************************************************************/
int sender_handler() {
    char *input;                    // buffer for user input
    int client_socket;                  // client side socket
    struct sockaddr_in client_address;  // client socket naming struct
    char message;
    char command[20];
    char arg2[20];
    int arg3;
    bool joined = false;
    pthread_t thread1;
    char buffer[100];
    Message messageData;
    
    printf("Echo client\n");
    // Property* propertyPtr = property_read_properties(PROPERTY_FILE);
    // char name = property_get_property(propertyPtr, "NAME");

    char name[20] = "Shlok";
    
    // take in the ip addr of server
    // handling the cient before connection

    while( true )
    {
        printf("Enter Command: ");
        fgets(buffer, 100, stdin);
        sscanf(buffer, "%s ", command );


        if( strcmp(command, "JOIN") == 0 )
        {
            sscanf(buffer, "%s %s %d", command, arg2, &arg3);
            
            // create an unnamed socket, and then name it
            client_socket = socket(AF_INET, SOCK_STREAM, 0);
            // create addr struct
            client_address.sin_family = AF_INET;
            client_address.sin_addr.s_addr = inet_addr(&arg2);
            client_address.sin_port = htons(arg3);

            // connect to server socket
            if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1) {
                perror("Error connecting to server!\n");
                exit(EXIT_FAILURE);
            }

            // set the message struct to send over
            strcpy(messageData.name, name);
            strcpy(messageData.message, arg2);
            messageData.port = arg3;
            messageData.type = JOIN;


            write(client_socket, &messageData, sizeof(Message));
            close(client_socket);

            joined = true;

            printf("Connected to Server!\n");

            Args *args = (Args*) malloc (sizeof(Args));
            args->client_socket = client_socket;
            strcpy(args->ip, arg2);
            args->port = arg3;

            if (pthread_create(&thread1, NULL, &getMessage, (void*)args) != 0) {
                perror("Error creating thread");
                exit(EXIT_FAILURE);
            }

        }
        else if( strcmp(command, "SHUTDOWN") == 0 )
        {
            sscanf(buffer, "%s %s", command, arg2);

            // connect to server socket
            if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1) {
                perror("Error connecting to server!\n");
                exit(EXIT_FAILURE);
            }
            
            if( joined )
            {
                messageData.type = SHUTDOWN;
                strcpy(messageData.name, name);
                message = "LEFT";
                strcpy(messageData.message, message);
                // send Client left the chat
                write(client_socket, &input, sizeof(char) );
            }
            if( strcmp(arg2, "ALL") == 0 )
            {
                input = "Exit now";
                write(client_socket, &input, sizeof(char) );
            }
            pthread_exit(thread1);
            close(client_socket);
            printf("Client Program exited!!\n");
            exit(EXIT_SUCCESS);
        }
        else if( strcmp(command, "LEAVE") == 0 )
        {
            // connect to server socket
            if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1) {
                perror("Error connecting to server!\n");
                exit(EXIT_FAILURE);
            }
            
            // send Client left the chat
            write(client_socket, &input, sizeof(char) );
            pthread_exit(thread1);
            close(client_socket);
        }
        else
        {
            if( joined )
            {
                // connect to server socket
                if (connect(client_socket, (struct sockaddr *)&client_address, sizeof(client_address)) == -1) {
                    perror("Error connecting to server!\n");
                    exit(EXIT_FAILURE);
                }
                
                char *full_message = malloc(strlen(name) + strlen(input) + 5);
                strcat(full_message, ": ");
                strcat(full_message, input);
                write(client_socket, full_message, sizeof(full_message));
                printf("You: %c", input);

                close(client_socket);
            }
            else
            {
                printf("Please JOIN a server first\n");
            }
        }  
    }

    return EXIT_SUCCESS;
}


