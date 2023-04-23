// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <string.h> 
#include <iostream>
#include <unistd.h> 
#define PORT 8080 
#define BUFF_SIZE 1024

using namespace std;

void game(int socket_fd)
{
    char buff[BUFF_SIZE];
    int n;

    //infinite
    for(;;){
        bzero(buff, sizeof(buff));
        cout << "Your turn:" << endl;
        n=0;
        while ((buff[n++] = getchar()) != '\n'); 
        
        write(socket_fd,buff,sizeof(buff));
        bzero(buff,sizeof(buff));
        read(socket_fd,buff,sizeof(buff));
        cout << "Player 2: " << buff << endl;
        

        if(strncmp("exit",buff,4) == 0){
            cout << "Exiting" << endl;
            break;
        }
    }
}
   
int main(int argc, char const *argv[]) 
{ 
    int socket_fd = 0, valread; 
    struct sockaddr_in serv_addr; 
    char hello[100] = "Hello from client"; 
    char buffer[1024] = {0}; 
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        printf("\n Socket creation error \n"); 
        return -1; 
    } 
   
    memset(&serv_addr, '0', sizeof(serv_addr)); 
   
    serv_addr.sin_family = AF_INET; 
    serv_addr.sin_port = htons(PORT); 
       
    // Convert IPv4 and IPv6 addresses from text to binary form 
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        printf("\nInvalid address/ Address not supported \n"); 
        return -1; 
    } 

    // cout << "Enter Word" << endl;
    // cin >> hello;
   
    if (connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        printf("\nConnection Failed \n"); 
        return -1; 
    } else
    {
        cout << "Connected to server" << endl;
    }
    
    game(socket_fd);
    close(socket_fd);
    /*
    send(sock , hello , strlen(hello) , 0 ); 
    printf("Hello message sent\n"); 
    valread = read( sock , buffer, 1024); 
    printf("%s\n",buffer );
    */ 
    return 0; 
} 
