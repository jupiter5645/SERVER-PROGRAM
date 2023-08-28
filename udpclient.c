#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define MAXLINE 1024

int main()
{
int sockfd;
char buffer[MAXLINE];
char *hello="Hello from Server";
struct sockaddr_in serveraddr;
if ((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
{
perror("Socket  creation failed");
exit (EXIT_FAILURE);
}
memset (&serveraddr, 0, sizeof (serveraddr)) ; 
serveraddr.sin_family = AF_INET; 
serveraddr.sin_addr.s_addr = INADDR_ANY;
serveraddr.sin_port = htons(PORT);
int len, n;
sendto( sockfd, (const char *)hello, strlen(hello),MSG_CONFIRM, (const struct sockaddr *) &serveraddr,sizeof(serveraddr));
printf ("Hello message sent. \n");
n=recvfrom(sockfd,(char *)buffer,MAXLINE, MSG_WAITALL,(struct sockaddr *)&serveraddr,&len);
buffer[n]='\0';
printf("Server: %s\n",buffer);
close(sockfd);
return 0;
}
