#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int search(char *array[], char *search, int size)
{

  int currentIndex;
  int start = 0;
  int endIndex = size - 1;
  int condCheck = 0;
  //pointer to the beggining of the linkedList

  while(start<=endIndex)
  {
    currentIndex = (start+endIndex)/2;
    if((condCheck = strcmp(array[currentIndex], search)) == 0)
    {
      return 1;
    }else if(condCheck < 0)
    {
      start = currentIndex + 1;
    }else
    {
      endIndex = currentIndex -1;
    }
  }
  return 0;
}
