
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[])
{
    int socket_fd;
    struct sockaddr_in serverAddress;
    socket_fd = socket(AF_INET,SOCK_STREAM,0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);
    inet_pton(AF_INET,"127.0.0.1",&serverAddress.sin_addr);
    connect(socket_fd,(struct sockaddr*)&serverAddress,sizeof(serverAddress));
    return 0;
}
