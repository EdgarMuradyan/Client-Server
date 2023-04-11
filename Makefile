CC = gcc
CFLAGS = -W -Wall -Werror -std=c99

all: Client/client Server/server

Server/server: Server/server.o errorproc.o
		$(CC) $(LDFLAGS) -o $@ $^

Client/client: Client/client.o errorproc.o
		$(CC) $(LDFLAGS) -o $@ $^

Client/client.o: Client/client.c errorproc.h
		$(CC) $(CFLAGS) -c -o $@ $<

Server/server.o: Server/server.c errorproc.h
		$(CC) $(CFLAGS) -c -o $@ $<

errorproc.r: errorproc.c errorproc.h
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
		rm -f *.o $(Client/client) $(Server/server)

