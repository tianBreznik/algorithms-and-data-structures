#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <math.h>
#include <stdbool.h>

#define DOUB_MAX 10e30  // a large number, must be greater than max value of any solution
#define SIZE 100000 // an estimate of how large the priority queue could become
#define NITEMS 2000 // an upper limit of the number of items

FILE *fp;  // file pointer for reading the input files
int Capacity;  // capacity of the knapsack (total weight that can be stored)
int Nitems;    // number of items in the knapsack problem instance
int *item_weights;  // vector of item weights
int *item_values;   // vector of item profits or values
int *temp_indexes;  // temporary item indexes for sorting items by value/weight
int QueueSize=0; // the number of items currently stored in the priority queue
int QUIET=0;     // can be set to 1 to suppress output

// the structure for a solution. All of this will be stored in the priority queue
typedef struct solution_structure
{
  int solution_vec[NITEMS+1];  // binary solution vector;
  //e.g. solution_vec[1]=1 means first item is packed in knapsack.
  //     solution_vec[1]=0 means first item is NOT in knapsack.

  int val;               // its value
  int fixed;             // the number of items that are fixed to either 0 or 1, not '*'
  double bound;          // the upper bound value of the solution
} struc_sol;

struc_sol *pqueue;  // the knapsack solutions. To be stored in a priority queue

// function prototypes
extern void read_knapsack_instance(char *filename);
extern void sort_by_ratio();
extern int check_evaluate_and_print_sol(int *sol,  int *total_value, int *total_weight);
void branch_and_bound(int *final_sol);
void copy_array(int *from, int *to);
int check_feasibility(struc_sol *child);

// The following four functions implement a priority queue.
// They are based on the functions given in Robert Sedgwick's book, Algorithms in C.
void upheap(int qsize)
{
  // upheap reorders the elements in the heap (queue) after an insertion
  struc_sol temp_element;
  temp_element=pqueue[qsize]; pqueue[0].bound=DOUB_MAX;

  while (pqueue[qsize/2].bound<=temp_element.bound)
    {
      pqueue[qsize]=pqueue[qsize/2]; qsize=qsize/2;
    }
  pqueue[qsize]=temp_element;
}

void insert(struc_sol element)
{
  assert(QueueSize<SIZE-1);
  pqueue[++QueueSize]=element;
  upheap(QueueSize);
}

void downheap(int qindex)
{
  // down heap reorders the elements in the heap (queue) after a removal
  int j;
  struc_sol temp_element;
  temp_element = pqueue[qindex];
  while(qindex<= QueueSize/2)
    {
      j=qindex+qindex;
      if(j<QueueSize && pqueue[j].bound<pqueue[j+1].bound)
	j++;
      if(temp_element.bound>=pqueue[j].bound)
	break;
      pqueue[qindex]=pqueue[j]; qindex=j;
    }
  pqueue[qindex]=temp_element;
}

struc_sol removeMax()
{
  struc_sol head=pqueue[1];
  pqueue[1]=pqueue[QueueSize--];
  downheap(1);
  return head;
}
// End priority queue functions.


void print_sol(struc_sol *sol)
{
  // prints a solution in the form 000100xxxx etc
  // with x's denoting the part of the solution not yet fixed (determined)

  int i;
  printf("%d %g ", sol->val, sol->bound);
  for(i=1;i<=sol->fixed;i++)
    printf("%d", sol->solution_vec[i]);
  while(i<=Nitems)
    {
      printf("x");
      i++;
    }
  printf("\n");
}

void frac_bound(struc_sol *sol, int fix)
{
  // Updates the values sol->val and sol->bound

  // Computes the fractional knapsack upper bound
  // given a binary vector of items (sol->solution_vec),
  // where the first
  // "fix" of them are fixed. All that must be done
  // is compute the value of the fixed part; then
  // add to that the value obtained by adding in
  // items beyond the fixed part until the capacity
  // is exceeded. For the exceeded capacity, the fraction
  // of the last item added which would just fill the knapsack
  // is taken. This fraction of profit/value is added to the
  // total. This is the required upper bound.

  // Everything above assumes items are sorted in decreasing
  // profit/weight ratio

  int i; // index of current item
  double totalp=0; // profit total
  int totalw=0; // weight total
  sol->val=-1;

  // compute the current value and weight of the fixed part
  for(i=1;i<=fix;i++)
    {
      if(sol->solution_vec[i]==1)
        {
          totalw+=item_weights[temp_indexes[i]];
          totalp+=item_values[temp_indexes[i]];
        }
    }
  if(totalw>Capacity) // if fixed part infeasible, return
    {
      return;
    }

  //otherwise calculate the value of partial solution
  sol->val=totalp;
  i=fix+1;
  do
    {
      totalw+=item_weights[temp_indexes[i]];
      totalp+=item_values[temp_indexes[i]];
      i++;
    } while((i<=Nitems)&&(totalw<Capacity));

  /* if over-run the capacity, adjust profit total by subtracting
     that overrun fraction of the last item  */
  if(totalw>Capacity)
    {
      --i;
      totalp-=((double)(totalw-Capacity)/(double)(item_weights[temp_indexes[i]]\
						  ))*item_values[temp_indexes[i]];
    }
 sol->bound=totalp;
}


int main(int argc, char *argv[1])
{
  int *final_sol;    // binary solution vector indicating items to pack
  int total_value, total_weight;  // total value and total weight of items packed

  read_knapsack_instance(argv[1]);

  assert(NITEMS>=Nitems);

  if((final_sol = (int *)malloc((Nitems+1)*sizeof(int)))==NULL)
    {
      fprintf(stderr,"Problem allocating solution vector final_sol\n");
      exit(1);
    }

  //the algo in the printed instructions starts here
  sort_by_ratio();

  if((pqueue = (struc_sol *)malloc(sizeof(struc_sol)*SIZE))==NULL)
    {
      fprintf(stderr,"Problem allocating memory for priority queue. Reduce SIZE.\n");
      exit(1);
    }

  branch_and_bound(final_sol);
  printf("Branch and Bound Solution of Knapsack is:\n");
  check_evaluate_and_print_sol(final_sol,&total_value,&total_weight);
  free(final_sol);
  free(pqueue);
  return(0);
}

void branch_and_bound(int *final_sol)
{
  // branch and bound

  // start with the empty solution vector
  // compute its value and its bound
  // put current_best = to its value
  // store it in the priority queue
  struc_sol* solution = (struc_sol*)malloc(sizeof(struc_sol));
  copy_array(final_sol, solution->solution_vec);
  solution->val = 0;
  solution->bound = 0;
  solution->fixed = 0;
  frac_bound(solution, 0);
  double current_best = solution->val;
  insert(*solution);

  while(QueueSize != 0 || solution->bound <= current_best)
  {
    struc_sol head  = removeMax();
    struc_sol* child_0 = (struc_sol*)malloc(sizeof(struc_sol));
    struc_sol* child_1 = (struc_sol*)malloc(sizeof(struc_sol));
    copy_array(head.solution_vec, child_0->solution_vec);
    copy_array(head.solution_vec, child_1->solution_vec);
    child_0->solution_vec[head.fixed + 1] = 0;
    child_1->solution_vec[head.fixed + 1] = 1;
    child_1->fixed = head.fixed + 1;
    child_1->fixed = head.fixed + 1;
    for(int child = 0; child <= 1; child++)
    {
      if(child == 0)
      {
        if(!check_feasibility(child_0))
        {
          free(child_0);
        }
        else
        {
          if(child_0->val > current_best)
          {
            current_best = child_0->val;
            copy_array(child_0->solution_vec, final_sol);
            insert(*child_0);
          }
        }
      }
      else
      {
        if(!check_feasibility(child_1))
        {
          free(child_1);
        }
        else
        {
          if(child_1->val > current_best)
          {
            current_best = child_1->val;
            copy_array(child_0->solution_vec, final_sol);
            insert(*child_1);
          }
        }
      }
    }
  }
  return;
}


int check_feasibility(struc_sol *child)
{
  frac_bound(child, child->fixed);
  if(child->val == -1)
    return 0;
  else
    return 1;
}


void copy_array(int *from, int *to)
{
  // This copies Nitems elements of one integer array to another.
  int i;
  for(i=0;i<Nitems;i++)
    {
      to[i]=from[i];
    }
}
