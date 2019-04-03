#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>



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
  mergeSort(array, 0, arraySize -1);

  for (int index = 0; index < arraySize; index++)
  {
    printf("%d ", array[index]);
  }
  printf("\n");
}

//size_t guarantees the integer will be an array index - 16 bit unsigned int
void mergeSort(int array[], int left, int right)
{
  //if right = left do nothing - base case
  if(left < right)
  {
    //rounds to floor by default
    int mid = (left+right)/2;

    //sort first half
    mergeSort(array, left, mid);
    //sort second half
    mergeSort(array, mid + 1, right);
    merge(array, left, mid, right);
  }
}

void merge(int array[], int left, int mid, int right)
{
  int index1 = mid - left +1;
  int index2 = right - mid;
  int i, j, sortingIndex;

  int leftArr[index1];
  int rightArr[index2];
  for(i = 0; i < index1; i++)
  {
    leftArr[i] = array[left+i];
  }
  for(j = 0; j < index2; j++)
  {
    rightArr[j] = array[mid + j +1];
  }

  i = 0;
  j = 0;

  sortingIndex = left;

  while(i < index1 && j < index2)
  {
    if (leftArr[i] <= rightArr[j])
    {
      array[sortingIndex++] = leftArr[i++];
    }
    else
    {
      array[sortingIndex++] = rightArr[j++];
    }
  }

  for(;i < index1; i++)
  {
    array[sortingIndex] = leftArr[i];
    sortingIndex++;
  }

  for(;j<index2; j++)
  {
    array[sortingIndex] = rightArr[j];
    sortingIndex++;
  }
}
