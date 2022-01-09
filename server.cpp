// everything done server side will be in file
// this chat server is meant to be encryped and authenticated
// messages will be decrypted and verified
// messages will be encrypted and sent to the client
// server.cpp

#include <iostream>
#include <string>
#include <stdio.h>

//unix libraries
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <fstream>

//define 1024 for messages
#define BUFFER_SIZE 1024

//chat server, server side
int main(int __argc, char *__argv){
    //when accessing the server we want to use a specific port
    if(__argc != 2){
        std::cout << "Usage: ./server <port>" << std::endl;
        exit(EXIT_FAILURE);
    }

    //hold the port number
    int port = atoi(__argv[1]);

    //create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        std::cout << "Error creating socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    //bind the socket to a port
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    if(bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        std::cout << "Error binding socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    //listen for connections
    if(listen(sockfd, 5) == -1){
        std::cout << "Error listening" << std::endl;
        exit(EXIT_FAILURE);
    }

    //accept connections
    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    int client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len);
    if(client_sockfd == -1){
        std::cout << "Error accepting connection" << std::endl;
        exit(EXIT_FAILURE);
    }

    //create a buffer to hold the message
    char buffer[BUFFER_SIZE];

    //read the message from the client
    int bytes_read = read(client_sockfd, buffer, BUFFER_SIZE);
    if(bytes_read == -1){
        std::cout << "Error reading from client" << std::endl;
        exit(EXIT_FAILURE);
    }

    //write the message to the client
    int bytes_written = write(client_sockfd, buffer, bytes_read);
    if(bytes_written == -1){
        std::cout << "Error writing to client" << std::endl;
        exit(EXIT_FAILURE);
    }

    //close the socket
    close(sockfd);
    close(client_sockfd);
    return 0;

}