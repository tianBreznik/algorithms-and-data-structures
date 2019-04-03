#include "graph.h"
#include "minisat.h"
#include <limits.h>
#include <time.h>
#include <math.h>

// Specify -DVERBOSE to get verbose printing, or define VERBOSE here
#ifdef VERBOSE
#define LOG(...) printf(__VA_ARGS__)
#else
#define LOG(...)
#endif

#define new_max(x,y) ((x) >= (y)) ? (x) : (y)

// Some Global variables for this file
// Not brilliant coding style, but avoids lots of extra parameters
Graph* graph;
int colours;
minisat_solver* solver;

// Get minisat_Var from node index and colour
// Make sure that getVar(graph->MaxSize,colours) is the biggest
minisat_Var getVar(int index, int colour)
{
  minisat_Var new_var = (double)(index*index + 3*index + 2*index*colour + colour + colour*colour);
  return new_var;
}


// Call after creating solver to make sure it allocates enough
// variables. Failing to call this will result in Segfault.
// Not making sure that max_var is really the maximum var will
// result in Segfault
void ensureVars()
{
  minisat_Var max_var = getVar(graph->MaxSize,colours);
  LOG("Setting number of variables to %d\n",max_var);
  for(int i=0;i<max_var;i++){ minisat_newVar(solver); }
}

// Adds the constraint that at least one of the variables
// in vars is true. This is logical or, not exclusive or.
void atLeastOneOfThese(minisat_Var* vars, int len)
{
 minisat_addClause_begin(solver);
 for(int i=0;i<len;i++){
   minisat_Lit l = minisat_mkLit_args(vars[i],1);
   minisat_addClause_addLit(solver,l);
   if(i==0){LOG("%d",vars[i]);}else{LOG("| %d",vars[i]);}
 }
 LOG("\n");
 minisat_addClause_commit(solver);
}

// Adds the constraint that both variables cannot be true
// at the same time. Does not require either to be true.
void notBothOfThese(minisat_Var v1, minisat_Var v2)
{
    minisat_Lit l1 = minisat_mkLit_args(v1,0);
    minisat_Lit l2 = minisat_mkLit_args(v2,0);
    minisat_addClause_begin(solver);
    minisat_addClause_addLit(solver,l1);
    minisat_addClause_addLit(solver,l2);
    minisat_addClause_commit(solver);
    LOG("-%d | -%d\n",v1,v2);
}

// Adds the constraint that two adjacent nodes n1 and n2
// cannot have the same colour
void addAdjacencyConstraints(int n1, int n2)
{
  // For each colour state that
  // ~(n1 is c and n2 is c) = ~(n1 is c) or ~(n2 is c)
  // Ignore any self-loops
  if(n1==n2)
    return;
  else
    for(int c=0;c<colours;c++)
      notBothOfThese(getVar(n1, c), getVar(n2, c));

}

// Adds the constraint(s) that each node must
// have exactly one colour
void addColouringConstraint(int n)
{
 // Should be at least one of the colours
 minisat_Var* minisat_table = (minisat_Var*)malloc(colours * sizeof(minisat_Var));
 for (int i = 0; i <colours;i++)
   minisat_table[i] = getVar(n, i);
 atLeastOneOfThese(minisat_table, colours);
 // Should not be two colours
 // Foreach pair of colours c1 and c2
 // ~(n is c1 and n is c2) = ~(n is c1) or ~(n is c2)
for(int first = 0; first < colours; first++)
  for(int second = 0; second < colours; second++)
    if(first!=second)
      notBothOfThese(getVar(n, first), getVar(n, second));
}

// Input colouring of an array of graph->MaxSize colours
// (in range of 0 to colours)
// Check whether this is a valid colouring for graph
// return 1 if okay and 0 otherwise
int checkColouring(int* colouring)
{
  for(int index = 0; index < graph->MaxSize;index++)
  {
    List *check = graph->table[index].outlist;
    if(check != NULL)
    {
      //outlist is not NULL
      //traverse outlist
      while(check->next != NULL)
      {
        //check colouring
        if(colouring[index] == colouring[check->index])
          return 0;
        check = check->next;
      }
    }
    else
    {
      return 1;
    }
  }
  return 1;
}


int main(int argc,char *argv[])
{

  if(argc !=3){
    printf("You should give 2 inputs, the graph and a k\n");
    return -1;
  }

  // Create graph
  graph = malloc(sizeof(Graph));
  read_graph(graph,argv[1]);

  // read in number of colours
  if (sscanf (argv[2], "%i", &colours) != 1) {
    fprintf(stderr, "error - not an integer");
    return -1;
  }

  printf("Creating solver and constraints...\n");
  // Create solver
  solver = minisat_new();
  ensureVars();

  //Create constraints for each node and edge
  for(int n=1; n < graph->MaxSize; n++){
    LOG("Add colouring constraints for %d\n",n);
    addColouringConstraint(n);
    List *outlist = graph->table[n].outlist;
    LOG("Add adjacency constraints for %d\n",n);
    while(outlist != NULL){
      addAdjacencyConstraints(n,outlist->index);
      outlist = outlist->next;
    }
  }

  printf("Attempting to solve constraints...\n");
  struct timespec solvingStart, solvingEnd;
  clock_gettime(CLOCK_REALTIME, &solvingStart);

  // Check satisfiability
  minisat_solve_begin(solver);
  if(minisat_solve_commit(solver)){

    clock_gettime(CLOCK_REALTIME, &solvingEnd);

    // If the constraints are solved then we can read off the colours
    printf("The graph is %d-colourable!\n",colours);
    int* colouring = malloc(sizeof(int)*graph->MaxSize);
    for(int n=1;n<graph->MaxSize;n++){
      for(int c=0;c<colours;c++){
        if(minisat_modelValue_Lit(solver,minisat_mkLit_args(getVar(n,c),1))){
          printf("Node %d is colour %d\n",n,c);
	  colouring[n]=c;
	}
      }
    }

    // We can check the colouring in polynomial time
    printf("Checking colouring...\n");
    struct timespec checkingStart, checkingEnd;
    clock_gettime(CLOCK_REALTIME, &checkingStart);
    if(checkColouring(colouring)){
      printf("Colouring is validated\n");
    }
    else{
      printf("Colouring is not validated\n");
    }
    clock_gettime(CLOCK_REALTIME, &checkingEnd);

    // Print out the running times of solving and checking
    #define BILLION 1000000000L
    double solvingTime = ( solvingEnd.tv_sec - solvingStart.tv_sec ) +
                         (( solvingEnd.tv_nsec - solvingStart.tv_nsec )/ BILLION);
    double checkingTime = ( checkingEnd.tv_sec - checkingStart.tv_sec ) +
                         (( checkingEnd.tv_nsec - checkingStart.tv_nsec )/ BILLION);
    printf( "solvingTime: %lf\n", solvingTime);
    printf( "checkingTime: %lf\n", checkingTime);
  }
  else{
    printf("The graph is not %d-colourable!\n",colours);
  }

  return(0);
}
