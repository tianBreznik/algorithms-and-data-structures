#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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
  struct node *parent;
} node;

static node* insert_node(node** currentNode);
void nodePrint(node* node_diagnose);
void treePrint(node* temp);
void freeNode(node* node_ref);
void traverse_and_insert(node* current);


int main(int argc, char **argv)
{
  //pointer to the beggining of the linkedList
  node *root = (node*)malloc(sizeof(node));
  root -> data.question = "a pangolin";
  root -> yes = NULL;
  root -> no = NULL;
  root -> parent = NULL;
  root -> tag = OBJECT;

  node* current = root;
  char* play_again = (char*)malloc(4);

  do {
    current = insert_node(&current);
    printf("Play again?\n");
    scanf("%s",play_again);
  } while(strcmp(play_again, "Yes") == 0);
  treePrint(current);
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

/*
const char * readInput(char* input,int size)
{
  fgets(input, size, stdin);
}
*/


static node* insert_node(node** current_root)
{
  /* put name and age into the next free place in the array parameter here */

  char* yes_no = (char*)malloc(4);
  char* answer = (char*)malloc(MAX_INPUT);
  char* question = (char*)malloc(MAX_INPUT);
  node* root_temp = *current_root;

    bool not_finished = true;
    while(not_finished)
    {
      if((*current_root)->tag == OBJECT)
      {
        printf("Is it a %s?", (*current_root)->data.object);
        printf("\n");
        scanf("%s", answer);
        getchar();
        if(strcmp(answer, "Yes") == 0)
        {
          printf("Good, easy peasy lemon squeazy\n");
          not_finished = false;
        }else
        {
          node* new_answer = (node*)malloc(sizeof(node));
          node* new_question = (node*)malloc(sizeof(node));
          //check if memory was allocated ok
          if(new_question == NULL || new_answer == NULL){exit(-1);}
          printf("Ugh ok you win, now tell me the answer\n");
          fgets(answer,MAX_INPUT, stdin);
          new_answer->data.object = answer;
          new_answer->tag = OBJECT;
          new_answer->yes = NULL;
          new_answer->no = NULL;
          //new_answer->parent = NULL;
          node* old_temp = *current_root;
          printf("Please give me a question, so I can tell the difference between %s and %s\n",new_answer->data.object, old_temp->data.object);
          fgets(question, MAX_INPUT, stdin);
          new_question->data.question = question;
          new_question->tag = QUESTION;
          new_question->yes = NULL;
          new_question->no = NULL;
          /*
          if(current_root->parent != NULL)
            new_question->parent = current_root->parent;
          else
            new_question->parent = NULL;
          new_answer->parent = new_question;
          */
          printf("What is the answer for %s",new_question->data.question);
          scanf("%s",yes_no);
          getchar();
          //save current root in temporary ref
          if((*current_root)->tag == OBJECT && (*current_root) -> parent == NULL)
          {
            new_question->parent = NULL;
            *current_root = new_question;
            old_temp->parent = *current_root;
            new_answer->parent = *current_root;
            if(strcmp(yes_no, "Yes") ==0)
            {
              (*current_root)->yes = new_answer;
              (*current_root)->no = old_temp;
            }else if(strcmp(yes_no, "No") ==0)
            {
              (*current_root)->no = new_answer;
              (*current_root)->yes = old_temp;
            }
            return *current_root;
          }
          else if((*current_root)->tag == OBJECT && (*current_root)-> parent != NULL)
          {
            printf("in here");
            new_question->parent = (*current_root)->parent;
            printf("parent is: %s\n",(*current_root)->data.object);
            *current_root = new_question;
            old_temp->parent = *current_root;
            new_answer->parent = *current_root;
            printf("current root q: %s\n",(*current_root)->data.question);
            if(strcmp(yes_no, "Yes") ==0)
            {
              (*current_root)->yes = new_answer;
              (*current_root)->no = old_temp;
            }else if(strcmp(yes_no, "No") ==0)
            {
              (*current_root)->no = new_answer;
              (*current_root)->yes = old_temp;
            }
            //root_temp ->no = (*current_root);
          }
          printf("Thanks\n");
          treePrint(*current_root);
          not_finished = false;
          //treePrint(root_temp);
          //freeNode(current);
        }
      }
    else if((*current_root)->tag == QUESTION)
    {
      printf("%s\n", (*current_root)->data.question);
      scanf("%s",yes_no);
      if(strcmp(yes_no, "Yes") == 0)
        *current_root = (*current_root)->yes;
      else if(strcmp(yes_no, "No") == 0)
        *current_root = (*current_root)->no;
    }
  }
  return root_temp;
}

// struct node -> [xxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx]

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
