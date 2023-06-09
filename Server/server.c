#include "../errorproc.h"
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
#define SERVER_BUF_SIZE 256
#define HISTORY_SIZE 256

enum Command
{
    CONNECT,
    DISCONNECT,
    PWD,    
    HISTORY,
    TIME,
    HOST,
    NOT    

};
 
char* int_to_string(const int num) {
    char *str = malloc(10);
    // +1 for "\0" this char
    snprintf(str, sizeof(str) + 1, "%d", num);
    return str;
}

int command_handler(const char *command) {
     
    if (strcmp(command, "disconnect") == 0) {
        return DISCONNECT;
    }
    else if ((strcmp(command, "pwd") == 0)) {
        return PWD;
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


char* command_to_string(int command) {

    if (command == DISCONNECT) {
        return "disconnect\n";
    }
    else if (command == PWD) {
        return "pwd\n";
    }
    else if (command == TIME) {
        return "time\n";
    }
    else if (command == HOST) {
        return "host\n";
    }
    else if (command == HISTORY) {
        return "history\n";
    }
    else if (command == NOT) {
        return "error comand\n";
    }
    return "incorrect command\n";

}

 


//return time in type string
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
    
    int history[HISTORY_SIZE];
    int history_size = 0;
    
    char server_buf[SERVER_BUF_SIZE] = "";
    while (nread > 0) {
        write(STDOUT_FILENO, buf, nread); 
        write(STDOUT_FILENO, "\n", 4);
        
        //clean server_buf         
        memset(server_buf, 0, SERVER_BUF_SIZE);
        
        //command parser
        nread = Read(fd, buf, sizeof buf);
        int command = command_handler(buf);  
         
        if (command == DISCONNECT) {
            history[history_size] = command;
            history_size++;
            break;
            close(fd);

        }
        else if (command == PWD) {
            history[history_size] = command;
            history_size++;
            memset(server_buf, 0, SERVER_BUF_SIZE);
            char tmp[256] = "";
            //get path in OS
            getcwd(tmp, sizeof(tmp));             
            strcat(server_buf, tmp);
            strcat(server_buf, "\n");            
            write(fd, server_buf, sizeof server_buf);
             
        }
        else if (command == HISTORY) {
            history[history_size] = command;
            history_size++;
            for (int i = 0; i < history_size; ++i) {
                strcat(server_buf, command_to_string(history[i]));
            }

            strcat(server_buf, "\n");
            write(fd, server_buf, sizeof server_buf);
        }
        else if (command == TIME) { 
            history[history_size] = command;
            history_size++;
            strcat(server_buf, get_time());
            write(fd, server_buf, sizeof server_buf);
        }
        else if (command == HOST) { 
            history[history_size] = command;
            history_size++;
            strcat(server_buf, int_to_string(HOST_NUM));
            strcat(server_buf, "\n");
            write(fd, server_buf, sizeof server_buf);
        }
        else if (command == NOT) {
            strcat(server_buf, buf);
            strcat(server_buf, ": command not found\n");
            write(fd, server_buf, sizeof server_buf);
        }

    }

    close(fd);
    close(server);
    return 0;
}
