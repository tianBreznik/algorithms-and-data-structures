#include "graph.h"


// Important: you do not need to allocate memory for
// mygraph. Currently this is already allocated on
// the stack in the stub for part1 and read_graph
// passes a pointer to this stack-allocated graph
// into this function
void freeGraph(Graph *mygraph);
int initialize_graph (Graph *mygraph, int MaxSize)
{
  // your code goes here
  mygraph->table = (Node*)malloc(sizeof(Node) * MaxSize);
  mygraph->MaxSize = MaxSize;
  for(int index=0; index<MaxSize; index++)
  {
    mygraph->table[index].name = NULL;
    //mygraph->table[index].outlist = (List*)malloc(sizeof(List));
    mygraph->table[index].outlist = NULL;
    mygraph->table[index].outdegree = 0;
    mygraph->table[index].indegree = 0;
    //all the nodes are not visited
    mygraph->table[index].visited = 0;
    mygraph->table[index].tableIndex = 0;

  }
  return 0;
}
int insert_graph_node (Graph *mygraph, int n, char *name)
{
  // your code goes here
  mygraph->table[n].name = (char*)malloc(sizeof(name));
  if(mygraph->table[n].name == NULL)
  {
    return -1;
  }
  mygraph->table[n].name = strcpy(mygraph->table[n].name, name);
  mygraph->table[n].visited = 0;
  mygraph->table[n].tableIndex = n;
  return 0;
}//insert_graph_node

int insert_graph_link (Graph *mygraph, int source, int target)
{
  // your code goes here
  List *newLink = (List*)malloc(sizeof(List));
  newLink->index = target;
  newLink->next = NULL;

  List *currentList = mygraph->table[source].outlist;
  if(currentList == NULL)
  {
    currentList = newLink;
    mygraph->table[source].outlist = currentList;
    mygraph->table[source].outdegree++;
  }else
  {
    while(currentList->next != NULL)
      currentList = currentList->next;
    currentList->next = newLink;
    mygraph->table[source].outdegree++;
    mygraph->table[target].indegree++;
  }



  return 0;
}//insert_graph_link

// use to check result of strdup, malloc etc.
void check (void *memory, char *message)
{
  if (memory == NULL)
  {
    fprintf (stderr, "Can't allocate memory for %s\n", message);
    exit (3);
  }
}
int read_graph (Graph *mygraph, char *filename)
/*
 * Reads in graph from FILE *filename which is of .gx format.
 * Stores it as Graph in *mygraph.
 * Returns an error if file does not start with MAX command,
 * or if any subsequent line is not a NODE or EDGE command.
 * Does not check that node numbers do not exceed the maximum number
 * Defined by the MAX command.
 * 8/2/2010 - JLS
 */
{
  FILE *fp;
  char command[80], name[80];
  int i, s, t;
  fp= fopen (filename, "r");
  if (fp==NULL)
  {
    fprintf(stderr,"cannot open file %s\n", filename);
    return -1;
  }
  printf ("Reading graph from %s\n", filename);
  fscanf (fp,"%s", command);
  if (strcmp (command, "MAX")!=0)
  {
    fprintf (stderr, "Error in graphics file format\n");
    fclose (fp);
    return -1;
  }
  else
  {
    fscanf (fp, "%d", &i);
    initialize_graph (mygraph, i+1); // +1 so nodes can be numbered 1..MAX
    while (fscanf (fp, "%s", command)!=EOF)
    {
      if (strcmp (command, "NODE")==0)
      {
        fscanf (fp, "%d %s", &i, name);
        insert_graph_node (mygraph, i, name);
      }
      else
      {
        if (strcmp (command, "EDGE")==0)
        {
          fscanf (fp, "%d %d", &s, &t);
          insert_graph_link (mygraph, s, t);
        }
        else
        {
          fclose (fp);
          return -1;
        }
      }
    }
  }
  fclose (fp);
  return 0;
}
void print_graph (Graph *mygraph)
/*
 * Prints out Graph *mygraph to the stdout in .gx format - JLS
 */
{
  int i;
  List *current;
  printf ("MAX %d\n", mygraph->MaxSize);
  for (i=0; i<mygraph->MaxSize; i++)
    if (mygraph->table[i].name!=NULL)
    {
      printf ("NODE %d %s\n", i, mygraph->table[i].name);
      current= mygraph->table[i].outlist;
      while (current!=NULL)
      {
        printf ("EDGE %d %d\n", i, current->index);
        current= current->next;
      }
    }
}

void freeGraph(Graph *mygraph)
{
  int i;
  List *current;
  List *head;
  for (i=0; i<mygraph->MaxSize; i++)
  {
    free(mygraph->table[i].name);
    head = mygraph->table[i].outlist;
    while (head !=NULL)
    {
      current = head;
      head = head->next;
      free(current);
    }//while
  }//for
  free(mygraph->table);
  //free(mygraph);
}//freeGraph
