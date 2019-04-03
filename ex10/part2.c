#include <limits.h>
#include <time.h>
#include <assert.h>
#include "graph.h"
#include <stdbool.h>

int breadth_first_search(Graph *mygraph, int v, int visited[], int dist[]);
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


int breadth_first_search(Graph *mygraph, int v, int visited[], int dist[])
{
  Queue* queue = makeQueue();
  enqueue(v,queue);
  visited[v] = 1;
  dist[v] = 0;

  while(!empty(queue))
  {
    List* newVertex = dequeue(queue);
    int newIndex = newVertex->index;
    //free(newVertex);

    //visits all the neighbour nodes
    for(List *child = mygraph->table[newIndex].outlist; child!=NULL; child = child->next)
    {
      int vertex_nr = child->index;
      if(!visited[vertex_nr])
      {
        visited[vertex_nr] = 1;
        dist[vertex_nr] = dist[newIndex] + 1;
        enqueue(vertex_nr, queue);
      }//if
    }//for
  }//while
  free(queue);
  return 0;
}//breadth_first_search


int outlist_lookup(List *start, int lookup)
{
  List* check = start;
  if(start == NULL)
  {
    return 1;
  }
  else
  {
    while(check->next != NULL)
    {
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
  int max_out = 0;
  int max_out_index = -1;
  int all_visited = 0;


  visited[source] = 1;
  while(outlist_lookup(current,target) != 1)//outlist_lookup checks if target is in outlist or empty
  {
    dist[target]++;
    List *child = current;
    //iterate over current outlist to find node with maximum outdegree
    while(child != NULL){
      if(!visited[child->index])
       {
        visited[child->index] = 1;
        if(mygraph->table[child->index].outdegree > max_out)
        {
          //node with max outdegree is found
          max_out = mygraph->table[child->index].outdegree;
          max_out_index = child->index;
        }
      }
      else
      {
        //count number of visited children
        all_visited++;
      }
      //move to next node in outlist
      child=child->next;
    }
    if(all_visited == mygraph->table[max_out_index].outdegree)
    {
      //all nodes from maximum node are explored - mark target as unreachable
      dist[target] = -1;
      return;
    }
    current = mygraph->table[max_out_index].outlist;
    max_out = 0;
    all_visited = 0;
  }
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
  int **distance_stat = (int **)malloc(MaxSize * sizeof(int *));
  for (int i=0; i<MaxSize; i++){
    distance_stat[i] = (int *)malloc(MaxSize * sizeof(int));
    distance_heuristic[i] = (int *)malloc(MaxSize * sizeof(int));
    visited[i] = (int *)malloc(MaxSize * sizeof(int));
    vis_heur[i] = (int *)malloc(MaxSize * sizeof(int));
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
    }
  }

  //for now pred isnt needed so it is being overwritten every time
  //check if you're passing the node index correctly with mygraph.table[index].tableIndex
  for (int index=0; index<MaxSize; index++)
    breadth_first_search(&mygraph, mygraph.table[index].tableIndex, visited[index], distance_stat[index]);


  for (int x_source=0; x_source<MaxSize; x_source++)
  {
    for (int x_target = 0; x_target<MaxSize; x_target++)
    {
      if(x_source == x_target)
        continue;
      else
        shortest_path_heuristic(&mygraph, mygraph.table[x_source].tableIndex, mygraph.table[x_target].tableIndex, vis_heur[x_source], distance_heuristic[x_source]);
    }
  }

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
    free(distance_heuristic[i]);
    free(vis_heur);
  }

  free(distance_stat);
  free(visited);
  free(vis_heur);
  free(distance_heuristic);
  freeGraph(&mygraph);


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
