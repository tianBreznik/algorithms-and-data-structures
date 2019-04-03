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

  for(int index = 0; index < arraySize; index++)
  {
    scanf("%d",&temp);
    numberArray[index] = temp;
  }
  int buckets[32768] = {0};

  for(int index = 0; index < arraySize; index++)
  {
    buckets[numberArray[index]]++;
  }

  int arrayIndex = 0;
  for(int bucketIndex = 0; bucketIndex <= 32767; bucketIndex++)
  {
    if(buckets[bucketIndex] != 0)
    {
      for(int sortedIndex = 0; sortedIndex < buckets[bucketIndex]; sortedIndex++)
      {
        numberArray[arrayIndex] = bucketIndex;
        arrayIndex++;
      }
    }
  }

  for (int index = 0; index < arraySize; index++)
  {
    printf("%d ", numberArray[index]);
  }
  printf("\n");

}
