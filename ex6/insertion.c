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
  /*
        else
          if(scanned >= inserted)
          {
          numberArray[scanned] = candidate;
          scanned++;
          inserted++;
        }
        if(candidate >= numberArray[scanned])
          {
            scanned++;
          }
          else
          {
            printf("Swapped");
            temp = numberArray[scanned];
            numberArray[scanned] = candidate;
            candidate = temp;
            scanned++;
            swapping = 1;
          }
        }
      }
    }
  }
}



      for(int index = 0; index < arraySize; index++)
      {
        if(numberArray[index] = NULL)
        {

        }
        printf("comparing\n");
        if(temp < numberArray[index])
        {
          printf("swapping\n");
          newTemp = numberArray[index];
          numberArray[index] = temp;
          temp = newTemp;
        }else
        {

        }
      }
      inserted++;
      */


  for (int index = 0; index < arraySize; index++)
  {
    printf("%d ", numberArray[index]);
  }
  printf("\n");
}
