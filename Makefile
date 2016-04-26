CFLAGS=-I$(HOME)/root/include
LDFLAGS=-L$(HOME)/root/lib -lgsl -lm
CC=clang

all: CFLAGS += -O3
all: sim_decay bin_decay

debug: CFLAGS += -g -Wall -O0
debug: sim_decay bin_decay

sim_decay: sim_decay.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o sim_decay.app sim_decay.c

bin_decay: bin_decay.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o bin_decay.app bin_decay.c

clean:
	rm *.app*