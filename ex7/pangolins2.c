#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/*
struct {
  int a;
  char b;
} var;
*/

int MAX_INPUT = 80;
typedef enum {OBJECT = 0,QUESTION = 1} obj_or_ques;

typedef struct node {
  obj_or_ques tag;
  union {
    //allocate memory when adding - the size of the string which you are adding
      char *object;
      char *question;
  } data;

  struct node *yes;
  struct node *no;
} node;

void nodePrint(node* node_diagnose);
void treePrint(node* temp);
void freeNode(node* node_ref);

static node* newNode(char* content, obj_or_ques type)
{
  node* new = (node*)malloc(sizeof(node));
  if(type == OBJECT)
  {
    new->data.object = content;
    new->tag = OBJECT;
  }
  else if(type == QUESTION)
  {
    new->data.question = content;
    new->tag = QUESTION;
  }
  new->yes = NULL;
  new->no = NULL;

  return new;
}

static node* insertYes(node* parent, char* content, obj_or_ques type)
{
  parent->yes = newNode(content, type);
  return parent->yes;
}

static node* insertLeft(node* parent, char* content obj_or_ques type)
{
  parent->no = newNode(content, type);
  return parent->no;
}

static node* insert_sorted(node* root, char* content)
{
  //how would I avoid allocating memory for these every function call??
  char* yes_no = (char*)malloc(4);
  char* answer = (char*)malloc(MAX_INPUT);
  char* question = (char*)malloc(MAX_INPUT);

  if(root == NULL) return makeNode(content, OBJECT);
  /*instead of a loop I use recursion with two base cases
  either the user wins or the computer - either way recursion
  stops*/
  if(root->tag == OBJECT)
  {
    printf("Is it a %s?", root)->data.object);
    printf("\n");
    scanf("%s", answer);
    getchar();
    if(strcmp(answer, "Yes") == 0)
    {
      printf("Good, easy peasy lemon squeazy\n");
      not_finished = false;
      return root;
    }else
    {
      node* new_answer = (node*)malloc(sizeof(node));
      node* new_question = (node*)malloc(sizeof(node));
      //check if memory was allocated ok
      if(new_question == NULL || new_answer == NULL){exit(-1);}
      
  newPerson -> name = name;
  newPerson -> age = age;
  (*newPerson).next = NULL;

  //check if list is empty
  if(head == NULL)
  {
    //if list is empty set head to be the new element
    head = newPerson;
  }
  else
  {
    //if list is not empty traverse the list starting with head
    person* current = head;

    //while end is not reached
    while(current  != NULL)
    {
      //while the next element to be compared is not empty
      if(current -> next != NULL)
      {
        //if new person is alphabetically less than head update head with it
        if(compare_people(newPerson, head) < 0)
        {
          newPerson -> next = head;
          head = newPerson;
          break;
        }
        //if new person is alphabetically less than the element on the right of
        //the next one link new person to it
        else if(compare_people(newPerson,current -> next) < 0)
        {
          newPerson -> next = current -> next;
          current -> next = newPerson;
          break;
        }
        //go to next element
        current = current -> next;
      }
      //otherwise just add new person at the end of the list
      else
      {
        current -> next = newPerson;
        break;
      }

    }

  }
  return head;
}


void treePrint(node* temp)
{
  if(temp == NULL)
  {
    return;
  }else
  {
    nodePrint(temp);
    treePrint(temp->yes);
    treePrint(temp->no);
  }
}

void freeNode(node* node_ref)
{
  if(node_ref == NULL)
  {
    return;
  }else
  {
    freeNode(node_ref->yes);
    freeNode(node_ref->no);
    free(node_ref);
    printf("freed\n");
  }
}

void nodePrint(node* node_diagnose)
{
  if(node_diagnose -> tag == OBJECT)
  {
    printf("Object: %s", node_diagnose->data.object);
    printf("Question: [NOTHING]\n\n");
  }
  else if(node_diagnose -> tag == QUESTION)
  {
    printf("Object: [NOTHING]\n");
    printf("Question: %s", node_diagnose->data.question);
    printf("Yes: %s", node_diagnose->yes->data.object);
    printf("No: %s\n\n",node_diagnose->no->data.object);
    //printf("%s\n", node_diagnose->no->data.object);
  }
}

static node* makeNode(char* content, obj_or_ques type)
{
  if(type == OBJECT)
  {
    node *new_nod = (node*)malloc(sizeof(node));
    new_nod->data.object = content;
    new_nod->yes = NULL;
    new_nod->no = NULL;
    new_nod->tag = OBJECT;
  }
  else if(type == QUESTION)
  {
    node *new_nod = (node*)malloc(sizeof(node));
    new_nod->data.question = content;
    new_nod->yes = NULL;
    new_nod->no = NULL;
    new_nod->tag = OBJECT;
  }
  return new_nod;
}
