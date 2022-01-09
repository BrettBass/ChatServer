// everything done client side will be in file
// this chat server is meant to be encryped and authenticated
// messages will be decrypted and verified
// messages will be encrypted and sent to the client
// client.cpp
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

#define BUFFER_SIZE 1024

int main(int __argc, char *__argv){
    //when accessing the server we want to use a specific port and ip
    if(__argc != 3){
        std::cout << "Usage: ./client <ip> <port>" << std::endl;
        exit(EXIT_FAILURE);
    }

    //hold the port number and ip
    int port = atoi(__argv[2]);
    std::string ip = __argv[1];

    //create a socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        std::cout << "Error creating socket" << std::endl;
        exit(EXIT_FAILURE);
    }

    //connect to the server
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1){
        std::cout << "Error connecting to server" << std::endl;
        exit(EXIT_FAILURE);
    }

    //create a buffer to hold the message
    char buffer[BUFFER_SIZE];

    //create a file to hold the message
    std::ofstream outfile;
    outfile.open("message.txt");

    //read the message from the server
    int bytes_read = read(sockfd, buffer, BUFFER_SIZE);
    if(bytes_read == -1){
        std::cout << "Error reading from server" << std::endl;
        exit(EXIT_FAILURE);
    }

    //write the message to the file
    outfile << buffer;

    //close the file
    outfile.close();

    //close the socket
    close(sockfd);

    return 0;
}