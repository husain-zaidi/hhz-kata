// Server side C/C++ program to demonstrate Socket programming 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
#include <iostream>
#define PORT 8080 
#define BUFF_SIZE 1024

using namespace std;

void game(int socket_fd)
{
    char buff[BUFF_SIZE];
    int n;
    int score = 0;

    //infinite
    for(;;){
        bzero(buff, BUFF_SIZE);
        read(socket_fd,buff,sizeof(buff));
        cout << "Player 1: " << buff << endl;
        char c = buff[0];
        bzero(buff,BUFF_SIZE);

        cout << "Your turn:" << endl;
        n=0;
        while ((buff[n++] = getchar()) != '\n'); 
        write(socket_fd,buff,sizeof(buff));
        if(c == buff[0])
            score++;

        if(strncmp("exit",buff,4) == 0){
            cout << "Score = " << score << endl;
            break;
        }
    }
}
int main(int argc, char const *argv[]) 
{ 
    int server_fd, socket_fd, valread; 
    struct sockaddr_in server_address; 
    int opt = 1; 
    int addrlen = sizeof(server_address); 
    char buffer[1024] = {0}; 
    char hello[100] = "Hello from server"; 
       
    // Creating socket file descriptor 
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) 
    { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
    { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    server_address.sin_family = AF_INET; 
    server_address.sin_addr.s_addr = INADDR_ANY; 
    server_address.sin_port = htons( PORT ); 
       
    // Forcefully attaching socket to the port 8080 
    if (bind(server_fd, (struct sockaddr *)&server_address, sizeof(server_address))<0) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    if (listen(server_fd, 3) < 0) 
    { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    addrlen = sizeof(server_address);
    socket_fd = accept(server_fd, (struct sockaddr *)&server_address, (socklen_t*)&addrlen);
    if (socket_fd<0) 
    { 
        perror("accept"); 
        exit(EXIT_FAILURE); 
    } 

    game(socket_fd);
    close(server_fd);
    /*
    valread = read( socket_fd , buffer, 1024); 
    printf("%s\n",buffer ); 
    send(socket_fd , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    */
    return 0; 
} 
