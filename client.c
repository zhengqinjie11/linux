#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
int main(int argc,char *argv[]) 
{ 
int sockfd,numbytes; 
char buf[BUFSIZ]; 
struct sockaddr_in their_addr; 
printf("break!"); 
while((sockfd = socket(AF_INET,SOCK_STREAM,0)) == -1); 
printf("We get the sockfd~\n"); 
their_addr.sin_family = AF_INET; 
their_addr.sin_port = htons(8000); 
their_addr.sin_addr.s_addr=inet_addr("127.0.0.1"); 
bzero(&(their_addr.sin_zero), 8); 
while(connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr)) == -1); 
printf("connect return: %d\n", connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr))); 
printf("Get the Server~\n"); 
numbytes = recv(sockfd, buf, BUFSIZ,0);//接 收 服 务 器 端 信 息 
buf[numbytes]='\0'; 
printf("buf: %s\n",buf); 
while(1) 
{ 
printf("Entersome thing:"); 
scanf("%[^\n]%*c",buf); 
printf("scanf: %s\n", buf); 
numbytes = send(sockfd, buf, strlen(buf), 0); 
printf("send numbytes: %d\n", numbytes); 
numbytes=recv(sockfd,buf,BUFSIZ,0); 
printf("recv numbytes: %d\n", numbytes); 
buf[numbytes]='\0'; 
printf("received:%s\n",buf); 
} 
close(sockfd); 
return 0; 
} 
