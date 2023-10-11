#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main()
{
    struct sockaddr_in server;
    struct sockaddr_in client;
    int clientlen;
    char buffer[1500];

    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    memset((char*)&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);             //htonl host order to network order, l is long
    server.sin_port = htons(9090);

    bind(sockfd, (struct sockaddr *)&server, sizeof(server));

    recvfrom(sockfd, buffer, 1500 ,0 ,(struct sockaddr *)&client, (struct sockaddr_in *)&clientlen);
    printf("Data received: %s\n", buffer);
    close(sockfd);
    return 0;
} 