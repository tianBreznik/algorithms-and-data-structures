#include "new_string_helper.h"
#include "search.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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

  clock_t start = clock();
  int found = linearSearch(stringSet, stringSearch[0], stringSetSize);
  clock_t end = clock();
  clock_t resultLinear = end - start;

  clock_t before_search = clock();
  mergeSort(stringSet, 0, stringSetSize -1);
  search(stringSet, stringSearch[0], stringSetSize);
  clock_t after_search = clock();
  clock_t result_binary = after_search - before_search;

  if(result_binary > resultLinear)
    printf("linear");
  else
    printf("binary");

}

int linearSearch(char *array[], char *search, int size)
{
  int c;
  for (c = 0; c < size; c++)
  {
   if (array[c] == search)    /* If required element is found */
     return 1; //1 means found
  }
  if (c == size)
    return 0;//0 means not found
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
