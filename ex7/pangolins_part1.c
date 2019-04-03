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

static node* insert_node(node* currentNode, obj_or_ques type, char *answer_question);
void nodePrint(node* node_diagnose);
void treePrint(node* temp);
void freeNode(node* node_ref);

int main(int argc, char **argv)
{
  //pointer to the beggining of the linkedList
  node *root = (node*)malloc(sizeof(node));


  node *root_yes = (node*)malloc(sizeof(node));
  node *root_no = (node*)malloc(sizeof(node));
  node *root_no_yes = (node*)malloc(sizeof(node));
  node *root_no_no = (node*)malloc(sizeof(node));
  node *root_yes_no = (node*)malloc(sizeof(node));
  node *root_yes_yes = (node*)malloc(sizeof(node));

  root_yes_yes -> data.object = "tian";
  root_yes_yes -> yes = NULL;
  root_yes_yes -> no = NULL;
  root_yes_yes -> tag = OBJECT;

  root_yes_no -> data.object = "breznik";
  root_yes_no -> yes = NULL;
  root_yes_no -> no = NULL;
  root_yes_no -> tag = OBJECT;

  root_yes -> data.question = "Je slovenac al lenartcan?";
  root_yes -> yes = root_yes_yes;
  root_yes -> no = root_yes_no;
  root_yes -> tag = QUESTION;

  root_no_no -> data.object = "alja";
  root_no_no -> yes = NULL;
  root_no_no -> no = NULL;
  root_no_no -> tag = OBJECT;

  root_no_yes -> data.object = "breznik/grlica";
  root_no_yes -> yes = NULL;
  root_no_yes -> no = NULL;
  root_no_yes -> tag = OBJECT;

  root_no -> data.question = "je slovenka al ciganka/lenartcanka?";
  root_no -> yes = root_no_yes;
  root_no -> no = root_no_no;
  root_no -> tag = QUESTION;

  root -> data.question = "SLovenc?!";
  root -> yes = root_yes;
  root -> no = root_no;
  root -> tag = QUESTION;


  node* print = root;
  treePrint(print);
  //freeNode frees 4 nodes when it should free 5
  freeNode(root);


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
  /*
  while(temp != NULL)
  {
    nodePrint(temp);
    printf("\n");
    temp = temp -> yes;
  }*/
}

/*
const char * readInput(char* input,int size)
{
  fgets(input, size, stdin);
}
*/


static node* insert_node(node* currentNode, obj_or_ques type, char *answer_question)
{
  /* put name and age into the next free place in the array parameter here */
  node* newNode = (node*)malloc(sizeof(node));
  if(newNode == NULL)
  {
    exit(-1);
  }
  if(type == OBJECT)
  {
    newNode -> data.object = answer_question;
    newNode -> yes = NULL;
    newNode -> no = NULL;
    newNode -> tag = type;
  }
  else if(type == QUESTION)
  {
    newNode -> data.question = answer_question;
    //this yes and no setting is wrong
    newNode -> yes = currentNode -> yes;
    newNode -> no = currentNode -> no;
    newNode -> tag = type;
  }


  /*peopleList -> next = (person*)malloc(sizeof(person));
  if((peopleList -> next = (person*)malloc(sizeof(person))) == NULL)
  {
    exit(-1);
  }*/
  return newNode;

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
    //printf("freed\n");
  }
}

// struct node -> [xxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx]

void nodePrint(node* node_diagnose)
{
  if(node_diagnose -> tag == OBJECT)
  {
    printf("Object: %s\n", node_diagnose->data.object);
    printf("Question: [NOTHING]\n");
  }
  else if(node_diagnose -> tag == QUESTION)
  {
    printf("Object: [NOTHING]\n");
    printf("Question: %s\n", node_diagnose->data.question);
    printf("Yes: %s\n", node_diagnose->yes->data.object);
    //printf("%s\n", node_diagnose->no->data.object);
  }
}
