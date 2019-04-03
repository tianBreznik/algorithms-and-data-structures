#include <limits.h>
#include <time.h>
#include <math.h>
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


int breadth_first_search(Graph *mygraph, int v, int visited[], int dist[], int pred[])
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

  int MaxSize = (&mygraph)->MaxSize;
  //find the node with the smallest out degree

  int **visited = (int **)malloc(MaxSize*sizeof(int *));
  //one dimensional distances array replaced with matrix - to record all distances
  //int *distances = (int*)malloc(MaxSize*sizeof(int));
  int **predecesors = (int **)malloc(MaxSize*sizeof(int *));
  int **distance_stat = (int **)malloc(MaxSize * sizeof(int *));
  for (int i=0; i<MaxSize; i++){
    distance_stat[i] = (int *)malloc(MaxSize * sizeof(int));
    visited[i] = (int *)malloc(MaxSize * sizeof(int));
    predecesors[i] = (int *)malloc(MaxSize * sizeof(int));
  }

  int edges = 0;
  for(int i = 0; i< MaxSize; i++)
  {
    edges += mygraph.table[i].outdegree;
    for(int j = 0; j< MaxSize; j++)
    {
      distance_stat[i][j] = -1;
      visited[i][j] = 0;
      predecesors[i][j] = -1;
    }
  }

  //for now pred isnt needed so it is being overwritten every time
  //check if you're passing the node index correctly with mygraph.table[index].tableIndex
  clock_t begin = clock();
  for (int index=0; index<MaxSize; index++)
    breadth_first_search(&mygraph, mygraph.table[index].tableIndex, visited[index], distance_stat[index], predecesors[index]);
  clock_t end = clock();
  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  int path_sum = 0;
  int connection_index = 0;
  for(int first = 0; first<MaxSize; first++)
  {
    for(int second = 0; second<MaxSize;second++)
    {
      if(distance_stat[first][second]>6)
        printf("|%d|| Overrun @ %d in searching for %d\n",distance_stat[first][second], first, second);
      if(distance_stat[first][second] != -1)
        connection_index++;
      path_sum += distance_stat[first][second];
    }
  }

  double path_avg = path_sum/((double)connection_index);
  double var_sum = 0;

  for(int first = 0; first<MaxSize; first++)
  {
    for(int second = 0; second<MaxSize;second++)
    {
      if(distance_stat[first][second] != -1)
        var_sum = var_sum + pow((distance_stat[first][second] - path_avg), 2);
    }
  }

  var_sum = var_sum/((double)connection_index);
  printf("Exectuon time with %d nodes and %d edges is: %f\n", MaxSize - 1, edges, time_spent);
  printf("Average distance between friends in the network is: %f |", path_avg);
  printf("and with variance %f\n", var_sum);

  for (int i=0; i<MaxSize; i++)
  {
    free(distance_stat[i]);
    free(visited[i]);
    free(predecesors[i]);
  }

  free(distance_stat);
  free(visited);
  free(predecesors);
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
