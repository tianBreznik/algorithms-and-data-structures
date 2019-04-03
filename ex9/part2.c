#include <limits.h>
#include "graph.h"


//int dep_first_search(Graph *mygraph, int v, int visited[]);
int depth_first_search(Graph *mygraph, int v, int visited[]);
int breadth_first_search(Graph *mygraph, int v, int visited[]);
void freeGraph(Graph *mygraph);


typedef struct queue {
  // points to the first thing in the queue, next points back
  List* front;
  // points to the last thing in the queue, next will be NULL
  List* back;
} Queue;

Queue* makeQueue();
List* dequeue(Queue* queue);
int empty(Queue* q);
void enqueue(int n, Queue* queue);
void freeQueue(Queue* queue);

int largest = 0;
int outIndex;
int depth_first_search(Graph *mygraph, int v, int visited[])
{
  visited[v] = 1;
  if(mygraph->table[v].outdegree > largest)
  {
    largest =  mygraph->table[v].outdegree;
    outIndex = v;
  }
  for(List *child = mygraph->table[v].outlist; child!=NULL; child = child->next)
  {
    if(!visited[child->index])
      depth_first_search(mygraph, child->index, visited);
  }//for
  return largest;
}//dep_first_search

int breadth_first_search(Graph *mygraph, int v, int visited[])
{
  Queue* queue = makeQueue();
  enqueue(v,queue);
  visited[v] = 1;

  while(!empty(queue))
  {
    List* newVertex = dequeue(queue);
    int newIndex = newVertex->index;
    free(newVertex);

    //visits all the neighbour nodes
    for(List *child = mygraph->table[newIndex].outlist; child!=NULL; child = child->next)
    {
      int vertex_nr = child->index;
      if(mygraph->table[vertex_nr].outdegree > largest)
      {
        largest =  mygraph->table[vertex_nr].outdegree;
        outIndex = vertex_nr;
      }
      if(!visited[vertex_nr])
      {
        visited[vertex_nr] = 1;
        enqueue(vertex_nr, queue);
      }//if
    }//for
  }//while
  free(queue);
  return largest;
}//breadth_first_search

int main(int argc,char *argv[])
{
  Graph mygraph;

  read_graph(&mygraph,argv[1]);

  int minOut = INT_MAX;
  int MaxSize = (&mygraph)->MaxSize;
  int minOutIndex = 0;
  //find the node with the smallest out degree
  for(int i = 0; i < mygraph.MaxSize; i++)
  {
    if(mygraph.table[i].outdegree < minOut && mygraph.table[i].outdegree > 0)
    {
      minOut = mygraph.table[i].outdegree;
      minOutIndex = i;
    }//if
  }//for

  int *visited = (int*)malloc(MaxSize*sizeof(int));
  for(int i = 0; i< MaxSize; i++)
    visited[i] = 0;

  int largestOut = 0;
  #ifdef BFS
    largestOut = breadth_first_search(&mygraph,minOutIndex, visited);
  #endif
  #ifdef DFS
    largestOut =  depth_first_search(&mygraph,minOutIndex, visited);
  #endif

  int versum = 0;
  for(int i = 0; i<MaxSize;i++)
    if(visited[i])
      versum++;

  free(visited);
  freeGraph(&mygraph);
  printf("The node with the smallest (non-zero) out-degree is %d with out-degree %d\n", minOut, minOutIndex);
  printf("There are %d nodes reachable from the node with the \nsmallest (non-zero) out-degree and ", versum-1);
  printf("the node with the \nlargest out-degree is at %d with out-degree %d \n", outIndex,largestOut);

  return(0);
}

Queue* makeQueue()
{
  Queue* queue = malloc(sizeof(Queue));
  queue->front = NULL;
  queue->back = NULL;
  return queue;
}//makeQueue

void freeQueue(Queue* queue)
{
  List* front = queue->front;
  List* back = queue->back;
  List* temp;
  while(front != NULL)
  {
    printf("not here\n");
    temp = front;
    front = front->next;
    free(temp);
  }
  while(back != NULL)
  {
    printf("also not");
    temp = back;
    back = back->next;
    free(temp);
  }
  free(queue);
}//freeQueue

void enqueue(int n, Queue* queue)
{
  List* new = malloc(sizeof(List));
  check(new, "Cannot enqueue");
  new->index = n;
  new->next = NULL;

  if(queue->back == NULL){
    //queue is empty
    queue->front = new;
    queue->back = new;
  }
  else{
    //queue.back->next will be NULL
    queue->back->next = new;
    queue->back = new;
  }
}//enqueue

int empty(Queue* q)
{
    if(q->front == NULL)
        return 1;
    else
        return 0;
}//empty

List* dequeue(Queue* queue)
{
  // queue is empty
  if(queue->front == NULL) return NULL;

  // shift front back
  List* ret = queue->front;
  queue->front = queue->front->next;

  // if eaten last thing tell back
  if(queue->front == NULL) queue->back=NULL;

  return ret;
}//dequeue
