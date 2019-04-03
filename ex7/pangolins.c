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

int main(int argc, char **argv)
{
  //pointer to the beggining of the linkedList
  node *root = (node*)malloc(sizeof(node));
  root -> data.question = "a pangolin";
  root -> yes = NULL;
  root -> no = NULL;
  root -> tag = OBJECT;

  node* current = root;
  bool not_finished = true;
  char* yes_no = (char*)malloc(4);
  char* answer = (char*)malloc(MAX_INPUT);
  char* question = (char*)malloc(MAX_INPUT);

  while(not_finished)
  {
    if(current->tag == OBJECT)
    {
      printf("Is it a %s?\n", current->data.object);
      scanf("%s", answer);
      getchar();
      if(strcmp(answer, "Yes") == 0)
      {
        printf("Good, easy peasy lemon squeazy\n");
        not_finished = false;
      }else
      {
        node* new_temp = (node*)malloc(sizeof(node));
        node* old_temp = (node*)malloc(sizeof(node));
        node* new_question_root = (node*)malloc(sizeof(node));
        printf("Ugh ok you win, now tell me the answer\n");
        fgets(answer,MAX_INPUT, stdin);
        new_temp->data.object = answer;
        new_temp->tag = OBJECT;
        new_temp->yes = NULL;
        new_temp->no = NULL;
        //insert into tree
        old_temp = current;
        printf("Please give me a question, so I can tell the difference between %s and %s\n",new_temp->data.object, current->data.object);
        fgets(question, MAX_INPUT, stdin);
        new_question_root->data.object = question;
        new_question_root->tag = QUESTION;
        new_question_root->yes = NULL;
        new_question_root->no = NULL;
        printf("What is the answer for %s",new_temp->data.object);
        //danger of overwriting by using yes_no!
        scanf("%s",yes_no);
        getchar();
        current = new_question_root;
        if(strcmp(yes_no, "Yes") ==0)
        {
          printf("entry created");
          current->yes = new_temp;
          current->no = old_temp;
        }else if(strcmp(yes_no, "No") ==0)
        {
          current->no = new_temp;
          current->yes = old_temp;
        }
        printf("Thanks");
        not_finished = false;


      }

    }else if(current->tag == QUESTION)
    {
      printf("%s\n", current->data.question);
      scanf("%s",yes_no);
      if(strcmp(yes_no, "Yes") == 0)
        current = current->yes;
      else if(strcmp(yes_no, "No") == 0)
        current = current->no;
    }
  }




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


  node* print = root;
  //treePrint(print);

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
