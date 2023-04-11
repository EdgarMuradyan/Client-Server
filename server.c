#include "errorproc.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define CLIENT_COUNT 5
#define HOST_NUM  25525

enum Command
{
    CONNECT,
    DISCONNECT,
    LS,    
    HISTORY,
    TIME,
    HOST,
    NOT 
    

};
 
char* int_to_string(const int num) {
    char *str = malloc(10);
    snprintf(str, sizeof(str) + 1, "%d", num);
    return str;
}

int command_handler(const char *command) {
    //printf("%s", command);
    if (strcmp(command, "disconnect") == 0) {
        return DISCONNECT;
    }
    else if ((strcmp(command, "ls") == 0) || (strcmp(command, "pwd") == 0)) {
        return LS;
    }
    else if (strcmp(command, "history") == 0) {
        return HISTORY;
    }
    else if (strcmp(command, "time") == 0) {
        return TIME;
    }
    else if (strcmp(command, "host") == 0) {
        return HOST;
    }
    else {
        return NOT;
    };
    return NOT;

}

 
char* get_time() { 
    time_t current_time;
    time(&current_time);
     
    return ctime(&current_time);
}


int main(){
    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(HOST_NUM);
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
    int history_size = 0;
    
    char server_buf[100] = "";
    while (nread > 0) {
        write(STDOUT_FILENO, buf, nread);
        
        //clientin uxarkvox bufy maqrum enq 
        memset(server_buf, 0, 100);

        //command parser
        nread = read(fd, buf, sizeof buf);
        int command = command_handler(buf);
        history[history_size] = command;
        history_size++;
        if (command == DISCONNECT) {
            break;
            close(fd);

        }
        else if (command == LS) {
            char cd[100];

            strcat(server_buf, "corrend directorry is: ");
            //get path in OS
            strcat(server_buf, getcwd(cd, sizeof(cd)));
            strcat(server_buf, "\n");
            write(fd, server_buf, sizeof server_buf);
        }
        else if (command == HISTORY) {
            printf("%d", history[0]);
            char server_buf[50] = "";
            strcat(server_buf, "history: ");
            for (int i = 0; i < history_size; ++i) {

                strcat(server_buf, int_to_string(history[i]));
            }

            strcat(server_buf, "\n");
            write(fd, server_buf, sizeof server_buf);
        }
        else if (command == TIME) {
            
            char server_buf[50] = "";
            strcat(server_buf, "time: ");
            strcat(server_buf, get_time());
            write(fd, server_buf, sizeof server_buf);
        }
        else if (command == HOST) {
             
            char server_buf[50] = "";
            strcat(server_buf, "host: ");
            
            strcat(server_buf, int_to_string(HOST_NUM));
            strcat(server_buf, "\n");
            write(fd, server_buf, sizeof server_buf);
        }
        else if (command == NOT) {
            //clientin patasxan uxarkel             
            strcat(server_buf, buf);
            strcat(server_buf, ": command not found\n");
            write(fd, server_buf, sizeof server_buf);
        }
    }

    close(fd);
    close(server);
    return 0;
}
