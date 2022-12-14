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
 
int main(int argc, char *argv[]) 
{ 
int fd, new_fd, struct_len, numbytes,i; 
struct sockaddr_in server_addr; 
struct sockaddr_in client_addr; 
char buff[BUFSIZ]; 
server_addr.sin_family = AF_INET; 
server_addr.sin_port = htons(8000); 
server_addr.sin_addr.s_addr = INADDR_ANY; 
bzero(&(server_addr.sin_zero), 8); 
struct_len = sizeof(struct sockaddr_in); 
fd = socket(AF_INET, SOCK_STREAM, 0); 
while(bind(fd, (struct sockaddr *)&server_addr, struct_len) == -1);
printf("Bind Success!\n"); 
while(listen(fd, 10) == -1); 
printf("Listening....\n"); 
printf("Ready for Accept,Waitting...\n"); 
new_fd = accept(fd, (struct sockaddr *)&client_addr, &struct_len); 
printf("accept return: %d\n", new_fd); 
printf("Get the Client~\n"); 
numbytes = send(new_fd,"Welcome to my server\n",21,0); 
while((numbytes = recv(new_fd, buff, BUFSIZ, 0)) > 0) 
{ 
buff[numbytes] = '\0'; 
printf("%s\n",buff); 
if(send(new_fd,buff,numbytes,0)<0) 
{ 
perror("write"); 
return 1; 
} 
} 
close(new_fd); 
close(fd); 
}

