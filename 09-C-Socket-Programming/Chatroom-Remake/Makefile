CC=gcc
CFLAGS=-O3 -Wall
LIBS=-pthread
SRC=src

all: server.out client.out
server.out: server.o tcpsock.o dplist.o
	$(CC) $(CFLAGS) $(LIBS) -o server.out server.o tcpsock.o dplist.o
client.out: client.o string.o
	$(CC) $(CFLAGS) $(LIBS) -o client.out client.o string.o
server.o: $(SRC)/server.c
	$(CC) $(CFLAGS) -c $(SRC)/server.c
tcpsock.o: lib/tcpsock.c
	$(CC) $(CFLAGS) -c lib/tcpsock.c
dplist.o: lib/dplist.c
	$(CC) $(CFLAGS) -c lib/dplist.c
string.o: $(SRC)/string.c
	$(CC) $(CFLAGS) -c $(SRC)/string.c
client.o: $(SRC)/client.c
	$(CC) $(CFLAGS) -c $(SRC)/client.c

.PHONY: clean
clean:
	rm -f *.o *.out