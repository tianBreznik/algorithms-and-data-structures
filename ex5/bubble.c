#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char **argv)
{
  //pointer to the beggining of the linkedList
  int arraySize;
  scanf("%d\n",&arraySize);
  int numberArray[arraySize];
  int temp;
  for (int index = 0; index < arraySize; index++)
  {
    scanf("%d", &temp);
    //printf("%d ", temp);
    numberArray[index] = temp;
  }

  int decrement = arraySize;
  int swapped;

  do {
    swapped = 0;
    for(int comparator = 0; comparator < decrement - 1; comparator++)
    {
      if(numberArray[comparator] > numberArray[comparator+1])
      {
        int swapit = numberArray[comparator+1];
        numberArray[comparator+1] = numberArray[comparator];
        numberArray[comparator] = swapit;
        swapped = 1;
      }
    }
    decrement--;
  } while(swapped);

  for (int index = 0; index < arraySize; index++)
  {
    printf("%d ", numberArray[index]);
  }
  printf("\n");





#if 0
  //int ages[] = {20, 52, 56, 27, 27};
  if(!strcmp(argv[1], "insert_start") && argc == 2)

  }
  else
  {
    exit(-1);
  }
  #endif
}
