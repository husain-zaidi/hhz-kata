
#include <netinet/in.h>
#include <sys/socket.h>

#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char const *argv[])
{
    int server_fd, socket_fd;
    struct sockaddr_in serverAddress;
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(8080);
    bind(server_fd,(struct sockaddr *)&serverAddress, sizeof(serverAddress));
    listen(server_fd,3);
    int addrlen = sizeof(serverAddress);
    socket_fd = accept(server_fd,(struct sockaddr *)&serverAddress,(socklen_t*)&addrlen);
    return 0;
}
