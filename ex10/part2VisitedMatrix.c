#include <limits.h>
#include <time.h>
#include "graph.h"

int breadth_first_search(Graph *mygraph, int v, int visited[], int dist[], int pred[]);
int outlist_lookup(List *start, int lookup);
void freeGraph(Graph *mygraph);
void shortest_path_heuristic(Graph *mygraph, int source, int target, int visited[], int dist[]);


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
        enqueue(vertex_nr, queue);

        //if(vertex_nr == d)
        //  return 1;
      }//if
    }//for
  }//while
  free(queue);
  return 0;
}//breadth_first_search


int outlist_lookup(List *start, int lookup)
{
  //remember to pass reference but not actual reference refering to node
  List* check = start;
  if(start == NULL)
  {
    //printf("bla\n");
    return 1;
  }
  else
  {
    while(check->next != NULL)
    {
      //printf("blabla\n");
      if(check->index == lookup)
        return 1;
      check = check->next;
    }
    return 0;
  }
}
void shortest_path_heuristic(Graph *mygraph, int source, int target, int visited[], int dist[])
{
  List* current = mygraph->table[source].outlist;
  //int MaxSize = mygraph->MaxSize;
  //dont need to record path yet
  //int *path = (int*)malloc(MaxSize*sizeof(int));
  //int path_index = 0;
  int max_out = 0;
  int max_out_index = -1;
  //for(int i = 0; i< MaxSize; i++)
  //  path[i] = 0;
  while(outlist_lookup(current,target) != 1)//outlist_lookup checks if target is in outlist or empty
  {
    //path[path_index] = current->index;
    //path_index++;
    visited[current->index] = 1;
    dist[target]++;//ker gres step by step po grafu in
    //distance_heuretic[source][target] hrani razdaljo od source->target
    for(List *child = current; child!=NULL; child = child->next)
    {
      if(!visited[child->index])
       {
        //printf("Out degree is %d and max_out is %d\n", mygraph->table[child->index].outdegree, max_out);
        if(mygraph->table[child->index].outdegree > max_out)
        {
          printf("Out degree %d is greater than max_out %d\n", mygraph->table[child->index].outdegree, max_out);
          max_out = mygraph->table[child->index].outdegree;
          max_out_index = child->index;
        }
        printf("data: %d\n", current->index);
      }
    }
    printf("SWAPPED!!! %d\n", max_out_index);
    current = mygraph->table[max_out_index].outlist;
    max_out = 0;
  }
  //what to do with path?? return it or print it our or WHAT??!
  //path[path_index] = current->index;
}//shortest_dist_heuristic

int main(int argc,char *argv[])
{
  Graph mygraph;

  read_graph(&mygraph,argv[1]);

  int MaxSize = (&mygraph)->MaxSize;
  //find the node with the smallest out degree

  int **visited = (int **)malloc(MaxSize*sizeof(int *));
  int **vis_heur = (int **)malloc(MaxSize*sizeof(int *));
  int **distance_heuristic = (int **)malloc(MaxSize*sizeof(int *));
  //one dimensional distances array replaced with matrix - to record all distances
  //int *distances = (int*)malloc(MaxSize*sizeof(int));
  int **predecesors = (int **)malloc(MaxSize*sizeof(int *));
  //int *distance_stat[MaxSize] = {-1};
  int **distance_stat = (int **)malloc(MaxSize * sizeof(int *));
  for (int i=0; i<MaxSize; i++){
    distance_stat[i] = (int *)malloc(MaxSize * sizeof(int));
    distance_heuristic[i] = (int *)malloc(MaxSize * sizeof(int));
    visited[i] = (int *)malloc(MaxSize * sizeof(int));
    vis_heur[i] = (int *)malloc(MaxSize * sizeof(int));
    predecesors[i] = (int *)malloc(MaxSize * sizeof(int));
  }

  int edges = 0;
  for(int i = 0; i< MaxSize; i++)
  {
    edges += mygraph.table[i].outdegree;
    for(int j = 0; j< MaxSize; j++)
    {
      distance_stat[i][j] = -1;
      distance_heuristic[i][j] = -2;
      visited[i][j] = 0;
      vis_heur[i][j] = 0;
      predecesors[i][j] = -1;
    }
  }

  //for now pred isnt needed so it is being overwritten every time
  //check if you're passing the node index correctly with mygraph.table[index].tableIndex
  for (int index=0; index<MaxSize; index++)
    breadth_first_search(&mygraph, mygraph.table[index].tableIndex, visited[index], distance_stat[index], predecesors[index]);
  printf("Did BFS\n");
  for (int x_source=0; x_source<MaxSize; x_source++)
  {
    for (int x_target = 0; x_target<MaxSize; x_target++)
    {
      printf("Calling heuristic with source %d and target %d\n",x_source, x_target);
      if(x_source == x_target)
        continue;
      else
        shortest_path_heuristic(&mygraph, mygraph.table[x_source].tableIndex, mygraph.table[x_target].tableIndex, vis_heur[x_source], distance_heuristic[x_source]);
    }
  }
  printf("Did heuristic");

  int acc_sum = 0;
  for(int first = 0; first<MaxSize; first++)
  {
    for(int second = 0; second<MaxSize;second++)
    {
      if(distance_stat[first][second] == distance_heuristic[first][second])
        acc_sum++;
    }
  }

  double accuracy = acc_sum/(double)(MaxSize*MaxSize);
  printf("Accuracy is: %f\n", accuracy);

  for (int i=0; i<MaxSize; i++)
  {
    free(distance_stat[i]);
    free(visited[i]);
    free(vis_heur[i]);
    free(distance_heuristic[i]);
  }

  free(distance_stat);
  free(visited);
  free(vis_heur);
  free(distance_heuristic);
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
