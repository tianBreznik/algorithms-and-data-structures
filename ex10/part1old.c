#include <limits.h>
#include "graph.h"


//int dep_first_search(Graph *mygraph, int v, int visited[]);
int depth_first_search(Graph *mygraph, int v, int visited[]);
int breadth_first_search(Graph *mygraph, int v, int visited[], int dist[], int pred[]);
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

//int reachableNodes = 0;

int breadth_first_search(Graph *mygraph, int v, /*int d*/ int visited[], int dist[], int pred[])
{
  Queue* queue = makeQueue();
  enqueue(v,queue);
  visited[v] = 1;
  dist[v] = 0;

  while(!empty(queue))
  {
    List* newVertex = dequeue(queue);
    int newIndex = newVertex->index;
    free(newVertex);

    //visits all the neighbour nodes
    for(List *child = mygraph->table[newIndex].outlist; child!=NULL; child = child->next)
    {
      int vertex_nr = child->index;
      if(!visited[vertex_nr])
      {
        visited[vertex_nr] = 1;
        dist[vertex_nr] = dist[newIndex] + 1;
        pred[vertex_nr] = newIndex;
        enqueue(vertex_nr, queue);

        //if(vertex_nr == d)
        //  return 1;
      }//if
    }//for
  }//while
  free(queue);
  return 0;
}//breadth_first_search

void shortestDist(Graph *mygraph, int source, int d, int visited[], int dist[], int pred[])
{
  //if(breadth_first_search(mygraph, source, d, visited, dist, pred))
  //{
    //printf("Nodes %d and %d are not connected\n", source, d);
    //return;
  //}

  breadth_first_search(mygraph, source, visited, dist, pred);
  //initialize new path array to 0 same size as the nr all the nodes - the indexes
  //that aren't 0 are the visited nodes on the path
  int MaxSize = mygraph->MaxSize;
  int *path = (int*)malloc(MaxSize*sizeof(int));
  for(int i = 0; i< MaxSize; i++)
    path[i] = 0;

  int pathcount = MaxSize-1;
  int traverse = d;
  path[pathcount] = traverse;
  pathcount--;
  while(pred[traverse] != -1)
  {
    path[pathcount] = pred[traverse];
    traverse = pred[traverse];
  }

  printf("Shortest path between the two nodes is %d\n", dist[d]);

  printf("The path is:\n");
  for(int i =0; i< MaxSize; i++)
    if(path[i]!= 0)
      printf("%d ",path[i]);
  printf("\n");
}

int main(int argc,char *argv[])
{
  Graph mygraph;

  read_graph(&mygraph,argv[1]);

  int minOut = INT_MAX;
  int MaxSize = (&mygraph)->MaxSize;
  int minOutIndex = 0;
  //find the node with the smallest out degree
  for(int i = 0; i < MaxSize; i++)
  {
    if(mygraph.table[i].outdegree < minOut && mygraph.table[i].outdegree > 0)
    {
      minOut = mygraph.table[i].outdegree;
      minOutIndex = i;
    }//if
  }//for

  int *visited = (int*)malloc(MaxSize*sizeof(int));
  //one dimensional distances array replaced with matrix - to record all distances
  //int *distances = (int*)malloc(MaxSize*sizeof(int));
  int *predecesors = (int*)malloc(MaxSize*sizeof(int));
  //int *distance_stat[MaxSize] = {-1};
  int **distance_stat = (int **)malloc(MaxSize * sizeof(int *));
  for (int i=0; i<MaxSize; i++)
    distance_stat[i] = (int *)malloc(MaxSize * sizeof(int));

  for(int i = 0; i< MaxSize; i++)
  {
    visited[i] = 0;
    //distances[i] = INT_MAX;
    predecesors[i] = -1;
    for(int j = 0; j< MaxSize; j++)
      distance_stat[i][j] = INT_MAX;
  }

  //for now pred isnt needed so it is being overwritten every time
  for (int index=0; index<MaxSize; index++)
  {
    breadth_first_search((&mygraph, mygraph.table[index],visited,)
  }
  free(predecesors);
  free(distances);
  free(visited);
  for (int i=0; i<MaxSize; i++)
    free(distance_stat[i]);
  free(distance_stat);
  freeGraph(&mygraph);
  //printf("Number of nodes in whole is %d\n", MaxSize);


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
