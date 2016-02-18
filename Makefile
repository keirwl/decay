P=decay
OBJECTS=
CFLAGS=-I$(HOME)/root/include -g -Wall -O0
LDFLAGS=-L$(HOME)/root/lib -lgsl -lm
CC=clang

$(P): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(P).app $(P).c
