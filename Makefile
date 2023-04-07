CC = gcc
CFLAGS = -W -Wall -Werror -std=c99

all: client server

server: server.o errorproc.o
		$(CC) $(LDFLAGS) -o $@ $^

client: client.o errorproc.o
		$(CC) $(LDFLAGS) -o $@ $^

client.o: client.c errorproc.h
		$(CC) $(CFLAGS) -c -o $@ $<

server.o: server.c errorproc.h
		$(CC) $(CFLAGS) -c -o $@ $<

errorproc.r: errorproc.c errorproc.h
		$(CC) $(CFLAGS) -c -o $@ $<

clean:
		rm -f *.o $(client) $(server)

