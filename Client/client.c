#include "../errorproc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#define BUF_SIZE 256

int main(){
    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(25525);
    Inet_pton(AF_INET, "127.0.0.2", &adr.sin_addr);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr);
    
    char client_buf_1[] = "start\n";
    write(fd, client_buf_1, sizeof client_buf_1); 
    
    char buf[BUF_SIZE] = ""; 
    size_t nread;
    nread = Read(fd, buf, sizeof(buf)); 
    
    char client_path[50];
    getcwd(client_path, sizeof(client_path));
    while (nread > 0) {
        
        //to read the message sent from the server
        write(STDOUT_FILENO, buf, sizeof buf);
        memset(buf, 0, BUF_SIZE);
        strcat(buf, client_path);
        strcat(buf, ": ");
        write(STDOUT_FILENO, buf, sizeof buf); 
         
        //send command to server
        char client_buf[16] = "";
        scanf("%s", client_buf);       
        write(fd, client_buf, sizeof client_buf);
        memset(buf, 0, BUF_SIZE);
        nread = Read(fd, buf, sizeof buf );
    }
    
    close(fd);

    return 0;
}




