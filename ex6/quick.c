#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void quickSort(int array[], int left, int right);
int findPivot(int i, int j);
void swapItems(int *x,int *y);

int main(int argc, char **argv)
{
  //pointer to the beggining of the linkedList
  int arraySize;
  scanf("%d\n",&arraySize);
  int array[arraySize];
  int temp;

  for(int index = 0; index < arraySize; index++)
  {
    scanf("%d",&temp);
    array[index] = temp;
  }

  //int sortedArr[arraySize] = mergeSort(leftArr, left, rightArr, right);
  quickSort(array, 0, arraySize -1);

  for (int index = 0; index < arraySize; index++)
  {
    printf("%d ", array[index]);
  }
  printf("\n");
}

/*
void quickSort(int array[], int left, int right)
{
  if(left < right)
  {

    int pivot = findPivot(array, left, right);

    quickSort(array, left, pivot-1);
    quickSort(array, pivot + 1, right);
  }
  //pick number in middle of array

}
*/

void quickSort(int array[],int left,int right)
{
    if(left < right)
    {
        int pivot = findPivot(left,right);
        swapItems(&array[left],&array[pivot]);
        int compareVal = array[left];
        int i = left+1;
        int j = right;
        int temp;
        //go through list from i to j - smallest to biggest
        while(i <= j)
        {
            //find indexes of items to swap
            while((i <= right) && (array[i] <= compareVal))
                i++;
            while((j >= left) && (array[j] > compareVal))
                j--;
            if( i < j)
            {
              temp = array[i];
              array[i] = array[j];
              array[j] = temp;
              //swapItems(&array[i],&array[j]);
            }
        }
        temp = array[left];
        array[left] = array[j];
        array[j] = temp;
        //swapItems(&array[left],&array[j]);

        /* recursively sort the lesser list */
        quickSort(array,left,j-1);
        quickSort(array,j+1,right);
    }
}

int findPivot(int i,int j )
{
  srand(time(0));
  int random = i + rand() % (j - i);
  //return((i+j) /2);
  return random;
}

void swapItems(int *x,int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

/*
int findPivot(int array[], int left, int right)
{
  //pick first pivot candidate
  int pivot = array[right];
  int low = left -1;
  int temp;

  for(int j = low; j <= right; j++)
  {
    if(array[j] <= pivot)
    {
      low++;
      if(low!=j)
      {
        temp = array[low];
        array[low] = array[j];
        array[j] = temp;
      }
    }
  }
  temp = array[low + 1];
  array[low+1] = array[right];
  array[right] = temp;

  return (low+1);
}
*/
