CC=gcc
CFLAGS=-Wall -g -std=gnu99
LDFLAGS=-Iinclude -Llib -lminisat -lminisat-c -lrt -lm

part1:
	@echo "You need to run \"export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:lib\""
	$(CC) $(CFLAGS) graph_functions.c graph_colouring.c -o graph_colouring $(LDFLAGS)


clean:
	rm -f graph_colouring graph_colouring.o graph_functions.o

.PHONY: part1
