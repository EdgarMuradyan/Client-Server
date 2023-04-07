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

enum Command
{
    CONNECT,
    DISCONNECT,
    LS,
    NOT,
    HISTORY,
    CD,
    CLEAR 
    

};
 


int command_handler(const char *command) {
    //printf("%s", command);
    if (strcmp(command, "disconnect") == 0) {
        return DISCONNECT;
    }
    else if (strcmp(command, "ls") == 0) {
        return LS;
    }
    else if (strcmp(command, "history") == 0) {
        return HISTORY;
    }

    else {
        return NOT;
    };
    return NOT;

}



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
    
    int history[100];
    int i = 0;
     
    while (nread > 0) {
        write(STDOUT_FILENO, buf, nread);
        //command parser


        nread = read(fd, buf, sizeof buf);
        int command = command_handler(buf);
        history[i] = command;
        i++;
        if (command == DISCONNECT) {
            close(fd);

        }
        else if (command == LS) {
            char cd[100];

            //write(fd, getcwd(cd, sizeof(cd)) , sizeof cd);
            char server_buf[512] = "corrend directorry is: ";
            strcat(server_buf, getcwd(cd, sizeof(cd)));
            strcat(server_buf, "\n");
            write(fd, server_buf, sizeof server_buf);

        }
        else if (command == HISTORY) {
            printf("%d", history[0]);
            char server_buf[512] = "";
            strcat(server_buf, "history: ");
            strcat(server_buf, "\n");
            write(fd, server_buf, sizeof server_buf);
        }
        else if (command == NOT) {
            //clientin patasxan uxarkel 
            char server_buf[50] = "YOU send: ";
            strcat(server_buf, buf);
            strcat(server_buf, "\n");
            write(fd, server_buf, sizeof server_buf);
        }
    }

    sleep(2);
    close(fd);
    close(server);
    return 0;
}
