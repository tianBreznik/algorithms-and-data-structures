#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main(int argc, char **argv)
{
  //pointer to the beggining of the linkedList
  int arraySize;
  scanf("%d\n",&arraySize);
  int numberArray[arraySize];
  int inserted = 0;
  int candidate;
  int temp;


  while(inserted < arraySize)
  {
    if(inserted == 0)
    {
      scanf("%d",&candidate);
      numberArray[0] = candidate;
      inserted++;
    }
    else
    {
      scanf("%d",&candidate);
      for(int index = 0; index < inserted; index++)
      {
        if(candidate < numberArray[index])
        {
            temp = numberArray[index];
            numberArray[index] = candidate;
            candidate = temp;
        }
      }
      numberArray[inserted] = candidate;
      //printf("%d set\n", candidate);
      inserted++;
      //break;
      }
  }


  for (int index = 0; index < arraySize; index++)
  {
    printf("%d ", numberArray[index]);
  }
  printf("\n");
}
