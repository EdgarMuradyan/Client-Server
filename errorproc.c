
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>



int Socket(int domain, int type, int protocol){
    int ret = socket(domain, type, protocol);
    if (ret == -1){
        perror("Socket failed\n");
        exit(EXIT_FAILURE);
    }
    return ret;
}


void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int ret = bind(sockfd, addr, addrlen);
    if (ret == -1){
        perror("Bind failed\n");
        exit(EXIT_FAILURE);
    }
}


int Listen(int sockfd, int backlog){
    int ret = listen(sockfd, backlog);
    if (ret == -1){
        perror("Listen failed\n");
        exit(EXIT_FAILURE);
    }
    return ret;
}


int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
    int ret = accept(sockfd, addr, addrlen);
    if (ret == -1){
        perror("Accept failed\n");
        exit(EXIT_FAILURE);
    }
    return ret;
}


void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
    int ret = connect(sockfd, addr, addrlen);
    if (ret == -1){
        perror("Connect failed\n");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *src, void *dst){
    int ret = inet_pton(af, src, dst);
    if (ret == -1){
        perror("Inet failed\n");
        exit(EXIT_FAILURE);
    }
    if (ret == 0){
        printf("Src does't contain a character string representing\n" );
        exit(EXIT_FAILURE);
    }
}
