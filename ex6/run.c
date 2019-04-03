#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "new_string_helper.h"
#include "search.h"


void mergeSort(char *array[], int left, int right);
void merge(char *array[], int left, int mid, int right);
int search(char *array[], char *search, int size);

int main(int argc, char **argv)
{
  //pointer to the beggining of the linkedList
  int stringSetSize;
  int stringSearchSize;


  scanf("%d",&stringSetSize);
  scanf("%d",&stringSearchSize);

  char *stringSet[stringSetSize];
  char *stringSearch[stringSearchSize];
  for(int index = 0; index < stringSetSize; index++)
  {
    stringSet[index] = (char*)malloc(BUFSIZE);
    getNextString(stringSet[index], BUFSIZE, stdin);
  }

  for(int index = 0; index < stringSearchSize; index++)
  {
    stringSearch[index] = (char*)malloc(BUFSIZE);
    getNextString(stringSearch[index], BUFSIZE, stdin);
  }

  mergeSort(stringSet, 0, stringSetSize -1);


  int binary[stringSearchSize];
  for(int i=0; i < stringSearchSize; i++)
  {
    binary[i] = search(stringSet, stringSearch[i], stringSetSize);
  }

  for (int index = 0; index < stringSearchSize; index++)
  {
    if(binary[index] == 0)
    {
      printf("no ");
      free(stringSearch[index]);
    }else if(binary[index] == 1)
    {
      printf("yes ");
      free(stringSearch[index]);
    }
  }
  for(int i=0; i < stringSetSize; i++)
  {
    free(stringSet[i]);
  }

  printf("\n");
}

void mergeSort(char *array[], int left, int right)
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

void merge(char *array[], int left, int mid, int right)
{
  int index1 = mid - left +1;
  int index2 = right - mid;
  int i, j, sortingIndex;

  char *leftArr[index1];
  char *rightArr[index2];
  for(i = 0; i < index1; i++)
  {
    leftArr[i] = (char*)malloc(BUFSIZE);
    if(leftArr[i] == NULL){exit(-1);}
    strcpy(leftArr[i], array[left+i]);
  }
  for(j = 0; j < index2; j++)
  {
    rightArr[j] = (char*)malloc(BUFSIZE);
    if(rightArr[j] == NULL){exit(-1);}
    strcpy(rightArr[j],array[mid+j+1]);
  }

  i = 0;
  j = 0;

  sortingIndex = left;

  while(i < index1 && j < index2)
  {
    if (strcmp(leftArr[i], rightArr[j]) > 0)
    {
      strcpy(array[sortingIndex++],rightArr[j++]);
    }
    else
    {
      strcpy(array[sortingIndex++], leftArr[i++]);
    }
  }

  for(;i < index1; i++)
  {
    strcpy(array[sortingIndex], leftArr[i]);
    sortingIndex++;
  }

  for(;j<index2; j++)
  {
    strcpy(array[sortingIndex], rightArr[j]);
    sortingIndex++;
  }
}
