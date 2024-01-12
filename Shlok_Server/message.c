#include "message.h"


// message will be in the form - "[NAME] [TYPE] [MESSAGE]"
void handle_message(Message *input, Nodes *chat_list){

    char *message;
    char test[80];

    Chat_Node *temp;


    // JOIN
    if( input->type == 0 ){

        // if ip DOES NOT exist in the existing nodes we can continue and create a node
        if (!is_joined(chat_list, input->name)){
            
            Chat_Node *newNode = create_node(&input->name, &input->message);
            // add node to chat room list
            
            printf("PORT: %d\n", newNode->port);
            printf("ip: %s\n", newNode->ip);
            
            add_node(chat_list, newNode);

            strcat(test, input->name);
            strcat(test, " has joined the chat\n");

            message = &test;

            // send the joined message to everyone except sender, which is our new node
            send_all_nodes_except_sender(chat_list, newNode, message);

            printf("Hello9\n");
        }

        else{
            message = 'Already Joined!\n';
            write(socket, message, 4);
        }
  
    } 

    // LEAVE
    else if( input->type == 1 ){

        
        if (is_joined(chat_list, input->name)){
            temp = get_node(input->name, chat_list);
            message = strcat(input->name, ' left the chat\n');
            send_all_nodes_except_sender(chat_list, temp, message);
        }

        remove_node(chat_list, temp);   

    } 

    // Shutdown
    else if( input->type == 2 ){

        if (is_joined(chat_list, input->name)){
            temp = get_node(input->name, chat_list);
            message = strcat(input->name, ': SHUTDOWN\n');
            send_all_nodes_except_sender(chat_list, temp, message);
        }
        remove_node(chat_list, temp);
    }

    // SHUTDOWN ALL
    else if( input->type == 3){
        
        if (is_joined(chat_list, input->name)){
            temp = get_node(input->name, chat_list);
            message = strcat(input->name, ': SHUTDOWN ALL\n');
            send_all_nodes_except_sender(chat_list, temp, message);
        }
        exit(0);

    }

    // Must be a NOTE
    else{

        if (is_joined(chat_list, input->name)){
            temp = get_node(input->name, chat_list);
            message = strcat(input->name, input->message);
            send_all_nodes_except_sender(chat_list, temp, message);
        }

    }
}


