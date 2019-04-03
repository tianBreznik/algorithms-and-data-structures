#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

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

  //int sortedArr[arraySize] = mergeSort(leftArr, left, rightArr, right);
  mergeSort(numberArray, arraySize);

  for (int index = 0; index < arraySize; index++)
  {
    printf("%d ", sortedArr[index]);
  }
  printf("\n");
}

void mergeLists(int leftArr[], int rightArr[])
{
  size_t left = sizeof(leftArr)/sizeof(leftArr[0]);
  size_t right = sizeof(rightArr)/sizeof(rightArr[0]);
  if(left == 0)
  {
    return rightArr;
  }
  else if(right == 0)
  {
    return leftArr;
  }
  else
  {
    int merged[left+right];
    int tempLeft, tempRight, tempMerge = 0;
    while(tempLeft < left && tempRight < right)
    {
      if(leftArr[tempLeft] > rightArr[tempRight])
      {
        merged[m_index++] = leftArr[tempLeft++];
      }
      else
      {
        merged[m_index++] = rightArr[tempRight++];
      }

    }
    if((tempRight - right) > 0)
    {
      while(tempRight < right)
      {
        merged[m_index++] = rightArr[tempRight++];
      }
    }
    else if((tempLeft - left) > 0)
    {
      while(tempLeft < left)
      {
        merged[m_index++] = rightArr[tempLeft++];
      }
    }
  }
}

//size_t guarantees the integer will be an array index - 16 bit unsigned int
void mergeSort(int numbers[],  size_t size)
{
  if(size > 1)
  {
  int left, right;
  left = floor(size/2);
  right = size - left;
  int leftArr[]
  for (int i = 0; i < left; i++)
    leftArr[i] = numbers[i];
  for (j = 0; j < left + right; j++)
    rightArr[j] = numbers[left + 1 + j];

  mergeSort(internalLeft, left);
  mergeSort(internalRight, right);
  mergeLists(numbers,leftArr,rightArr, left, right);
}

}
