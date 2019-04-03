#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
//#define __USE_BSD // make prototype for strdup visible
#include <string.h>

typedef struct linkedlist { // linked list of ints (for use in Node)
  int index;
  struct linkedlist *next;
} List;

typedef struct { // a Node of a Graph
  char *name;
  List *outlist; // adjacency list
  int outdegree; // length of outlist
  int indegree;
  int visited; // 0 if not visited, 1 if visited
  int tableIndex;
  int colour;
  //double pagerank_score; //not needed for this exercise
} Node;

typedef struct {
  // your code goes here
  //number of vertices
  int MaxSize;
  Node* table;

} Graph;

// use to check result of strdup, malloc etc.
extern void check (void *memory, char *message);

// These functions have an int return type so that you can return
// a status indicating the success or otherwise of the function
// as is done in read_graph. You may change the functions to
// void if you wish to do so.

extern int initialize_graph (Graph *mygraph, int MaxSize);
extern int insert_graph_node (Graph *mygraph, int n, char *name);
extern int insert_graph_link (Graph *mygraph, int source, int target);
extern int read_graph (Graph *mygraph, char *filename);
extern void print_graph (Graph *mygraph);

/*
 Here is an implementation of a Queue that you may wish to use in
 part 2. You do not need to use it but if you do use it you will
 need to be able to explain how it works and the complexity of
 enqueue and dequeue
 */
