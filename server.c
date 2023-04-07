#include "errorproc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define CLIENT_COUNT 5

int main(){
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(50555);
    Bind(server, (struct sockaddr *) &adr, sizeof(adr));
    Listen(server, CLIENT_COUNT);
    socklen_t adrlen = sizeof(adr);
    int fd = Accept(server, (struct sockaddr *) &adr, &adrlen);
    
    char buf[256];
    size_t nread = read(fd, buf, 256);      
    if (nread == (size_t)-1){
        perror("read failed");
        exit(EXIT_FAILURE);
    }
    if (nread == 0) {
        printf("End of file\n");
    }
     
    char ready_massege[50] = "server ready... \n";
    write(fd, ready_massege, sizeof ready_massege);


    while (1) {
        write(STDOUT_FILENO, buf, nread);
        
        nread = read(fd, buf, sizeof buf);
        char server_buf[50] = "send for ";
        strcat(server_buf, buf);
        strcat(server_buf, "\n");

        //clientin patasxan uxarkel 
        write(fd, server_buf, sizeof server_buf);
        
    }


    sleep(2);
    close(fd);
    close(server);

    return 0;
}
