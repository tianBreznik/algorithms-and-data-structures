CC=gcc
CFLAGS=-Wall -g -std=c99 
LDFLAGS=-lm

part1: 
	$(CC) $(CFLAGS) graph_functions.c part1.c -o part1 

part2_depth: 
	$(CC) $(CFLAGS) -DDFS $(LDFLAGS) graph_functions.c part2.c -o part2_depth 

part2_breadth: 
	$(CC) $(CFLAGS) -DBFS $(LDFLAGS) graph_functions.c part2.c -o part2_breadth

clean:
	rm -f part1 part2 part1.o part2.o graph_functions.o 

.PHONY: part1 part2_depth part2_breadth
