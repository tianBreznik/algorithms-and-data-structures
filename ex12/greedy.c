#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE *fp;  // file pointer for reading the input files
int Capacity;     // capacity of the knapsack (total weight that can be stored)
int Nitems;    // number of items available
int *item_weights;  // vector of item weights
int *item_values;  // vector of item profits or values
int *temp_indexes;  // temporary item indexes for sorting items by value/weight
int QUIET=0; // this can be set to 1 to suppress output

extern void read_knapsack_instance(char *filename);
extern void print_instance();
extern void sort_by_ratio();
extern int check_evaluate_and_print_sol(int *sol,  int *total_value, int *total_weight);
void greedy();

int main(int argc, char *argv[])
{
  read_knapsack_instance(argv[1]);
  print_instance();
  greedy();
  return(0);
}

void greedy()
{
  int total_weight=0; // current total weight of the items in the knapsack
  int total_value=0; //  current total profit of the items in the knapsack
  int i=1;
  int j;
  int solution[Nitems+1];
  int available = Capacity;

  sort_by_ratio(); // sort items in descending profit-to-weight ratio order

     // set the knapsack initially empty
  for(j=1;j<=Nitems;j++)
    solution[j]=0;

  for (j = 1; j <= Nitems; j++) {
    if (item_weights[temp_indexes[j]] > available)
       break;
    else {
       solution[temp_indexes[j]] = 1;
       total_value = total_value + item_values[temp_indexes[j]];
       total_weight = total_weight - item_weights[temp_indexes[j]];
       available = available - item_weights[temp_indexes[j]];
      }
   }

   if (j < Nitems)
    solution[i] = available / item_weights[i];
  printf("The greedy solution - not necessarily optimal - is:\n");
  check_evaluate_and_print_sol(solution, &total_value, &total_weight);
}
