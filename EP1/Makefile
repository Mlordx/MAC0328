CC=gcc
CFLAGS=-Wall -pedantic -std=c99 -g
RM=rm -f


blocks: blocks.o graph.o
	$(CC) $(CFLAGS) $^ -o $@

blocks.o: blocks.c
	$(CC) $(CFLAGS) -c $^

graph.o: graph.h graph.c
	$(CC) $(CFLAGS) -c $^

clean:
	$(RM) *.o *.gch