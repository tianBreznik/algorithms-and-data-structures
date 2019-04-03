#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/* Link list node */
struct bucketList
{
    int value;
    struct bucketList* next;
};

// Function to insert a given node in a sorted linked list
struct bucketList sortInsert(struct bucketList**, struct bucketList*);

// function to sort a singly linked list using insertion sort

struct bucketElement sortInsert(struct Node** headRef, struct Node* new)
{
    struct Node* current;
    /* Special case for the head end */
    if (*headRef == NULL || (*headRef)->data >= new->data)
    {
        new->next = *head_ref;
        *headRef = new;
    }
    else
    {
        /* Locate the node before the point of insertion */
        current = *headRef;
        while (current->next!=NULL &&
               current->next->data < new->data)
        {
            current = current->next;
        }
        new->next = current->next;
        current->next = new;
    }
}
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
  //there will be 101 buckets each with a bucket linked list - how to create a
  //separate linked lists that each have their own heads
  struct *bucketElement buckets[101] = {NULL};
  int candidateBucketMapping;
  for(int candidateNr = 0; candidateNr < arraySize; candidateNr++)
  {
    candidateBucketMapping = numberArray[candidateNr] % 101;
    //preveri ce pravilno assigne-as memory glede na to da ne uporabljas typedef
    struct bucketElement* newElement = (bucketElement*)malloc(sizeof(bucketElement));
    if(newElement == NULL)
    {
      exit(-1);
    }
    newElement -> value = numberArray[candidateNr];
    newElement -> data = NULL;
    buckets[candidateBucketMapping] = sortInsert(&buckets[candidateBucketMapping], newElement);
  }
  //now concatenate buckets

}
