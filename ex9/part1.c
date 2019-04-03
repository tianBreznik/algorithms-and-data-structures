#include <limits.h>
#include "graph.h"

void freeGraph(Graph *mygraph);
int main(int argc,char *argv[])
{
  Graph mygraph;

  read_graph(&mygraph,argv[1]);

  int maxOut = 0;
  int maxIn = 0;
  int minIn = INT_MAX;
  int maxOutIndex = 0;
  int maxInIndex = 0;
  int minInIndex = 0;
  for(int i = 0; i < mygraph.MaxSize; i++)
  {
    if(mygraph.table[i].outdegree > maxOut)
    {
      maxOut = mygraph.table[i].outdegree;
      maxOutIndex = i;
    }
    if(mygraph.table[i].indegree > maxIn)
    {
      maxIn = mygraph.table[i].indegree;
      maxInIndex = i;
    }
    if(mygraph.table[i].indegree < minIn && mygraph.table[i].indegree > 0)
    {
      minIn = mygraph.table[i].indegree;
      minInIndex = i;
    }
  }


  freeGraph(&mygraph);
  printf("Max out-degree is %d at %d\n", maxOut, maxOutIndex);
  printf("Max in-degree is %d at %d\n", maxIn, maxInIndex);
  printf("Min in-degree is %d at %d\n", minIn, minInIndex);
  return(0);
}
