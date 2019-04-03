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
typedef enum {YES = 0, NO = 1} yes_no_type;

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

static node* play_game(node* currentNode);
void nodePrint(node* node_diagnose);
void treePrint(node* temp);
void freeNode(node* node_ref);
void traverse_and_insert(node* current);
int check_yes_no(char* yes_no, yes_no_type y_n_tag);


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
    current = play_game(current);
    printf("Play again?\n");
    scanf("%s",play_again);
  } while(strcmp(play_again, "Yes") == 0);
  treePrint(current);
  freeNode(current);
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


static node* play_game(node* current_root)
{
  //allocate memory for user answers - yes/no's, actual answers and questions
  char* yes_no_inner = (char*)malloc(4);
  char* yes_no_outer = (char*)malloc(4);
  char* answer = (char*)malloc(MAX_INPUT);
  char* question = (char*)malloc(MAX_INPUT);
  //create temporary root pointer - used to keep tree root fixed while we traverse the tree
  node* root_temp = current_root;

  //a variable to determine when the user has won/lost - loop stops then
  bool not_finished = true;
  while(not_finished)
  {
    //First computer guess - prompts the user for equality and determined whether
    //the tree traversal will continue - not_finished set to false ie finished
    if(current_root->tag == OBJECT)
    {
      printf("Is it a %s?", current_root->data.object);
      printf("\n");
      scanf("%s", yes_no_inner);
      getchar();
      //check answer - obvious
      if(strcmp(yes_no_inner, "Yes") == 0)
      {
        printf("Good, easy peasy lemon squeazy\n");
        not_finished = false;
      }else
      {
        //computer guess was not correct
        //allocate memory for new node data - answers/questions to be added to tree
        node* new_answer = (node*)malloc(sizeof(node));
        node* new_question = (node*)malloc(sizeof(node));
        //check if memory was allocated ok
        if(new_question == NULL || new_answer == NULL){exit(-1);}
        printf("Ugh ok you win, now tell me the answer\n");
        fgets(answer,MAX_INPUT, stdin);
        size_t ln = strlen(answer)-1;
        if (answer[ln] == '\n')
          answer[ln] = '\0';
        //set new_answer node data
        new_answer->data.object = answer;
        new_answer->tag = OBJECT;
        new_answer->yes = NULL;
        new_answer->no = NULL;
        //save current_root - node used for traversal and to be swapped - in a
        //temporary variable so that we can replace current_root and put its
        //previous value in one of its children
        node* old_temp = current_root;
        //Prompt the  user for a question to the answer new_answer
        printf("Please give me a question about %s, so I can tell the difference between %s and %s\n",new_answer->data.object, new_answer->data.object, old_temp->data.object);
        fgets(question, MAX_INPUT, stdin);
        size_t qln = strlen(question)-1;
        if (question[qln] == '\n')
          question[qln] = '\0';
        //set new_question node data
        new_question->data.question = question;
        new_question->tag = QUESTION;
        new_question->yes = NULL;
        new_question->no = NULL;
        //ask for the answer - to know where to put it
        printf("What is the answer for %s\n",new_answer->data.object);
        scanf("%s",yes_no_inner);
        //prevent buffer input line failure
        getchar();
        //if current_root is the top root - its parent is null then set children
        //according to answer in yes_no_inner
        if(current_root->tag == OBJECT && current_root -> parent == NULL)
          {
            //new_question replaces current_root thereby becoming new root
            //so its parent is set to NULL
            new_question->parent = NULL;
            current_root = new_question;
            //old temp becomes answer node so its parent is current_root
            old_temp->parent = current_root;
            new_answer->parent = current_root;
            if(strcmp(yes_no_inner, "Yes") ==0)
            {
              current_root->yes = new_answer;
              current_root->no = old_temp;
            }else if(strcmp(yes_no_inner, "No") ==0)
            {
              current_root->no = new_answer;
              current_root->yes = old_temp;
            }
            //return root of the tree to allow traversal
            return current_root;
          }
        //if current_root is not root of tree
        else if(current_root->tag == OBJECT && current_root -> parent != NULL)
        {
          //link current_root's parent to new_question
          new_question->parent = current_root->parent;
          //set new_question to current_root
          current_root = new_question;
          //link updated currentNode to be at yes/no positions depending on the
          //previous yes/no answer
          if(strcmp(yes_no_outer, "No") == 0)
            current_root->parent->no = current_root;
          else if(strcmp(yes_no_outer, "Yes") == 0)
            current_root->parent->yes = current_root;

          //link the answers to the new_question node
          old_temp->parent = current_root;
          new_answer->parent = current_root;
          //set the answers of the question node
          if(strcmp(yes_no_inner, "Yes") ==0)
          {
            current_root->yes = new_answer;
            current_root->no = old_temp;
          }else if(strcmp(yes_no_inner, "No") ==0)
          {
            current_root->no = new_answer;
            current_root->yes = old_temp;
          }
          printf("Thanks\n");
          while(current_root->parent != NULL)
            current_root = current_root->parent;
          return current_root;
        }
        not_finished = false;
        //treePrint(root_temp);
        //freeNode(current);
      }
    }
    else if(current_root->tag == QUESTION)
    {
      printf("%s\n", current_root->data.question);
      scanf("%s",yes_no_outer);
      if(strcmp(yes_no_outer, "Yes") == 0)
        current_root = current_root->yes;
      else if(strcmp(yes_no_outer, "No") == 0)
        current_root = current_root->no;
    }
  }
  return root_temp;
}

// struct node -> [xxxx|xxxxxxxx|xxxxxxxx|xxxxxxxx]

int check_yes_no(char* yes_no, yes_no_type y_n_tag)
{
  int found = 0;
  //can be changed if possible answers should be expanded by increasing above constants
  //after compiling it became evident that C does not treat constants as constant expressions
  //so the arrays need to be declared with 15 and 10 instead of constants in those places
  char yes_answers[15][20] = {'yes','y','Yes','Y','yYes', 'YES','Yyes', 'yess', 'yees','absolutely','yyes','ye','omg yes!','Y es', 'yES'};
  char no_answers[10][20] = {'No', 'no', 'Nno', 'NO', 'n','N','nNo','non', 'noo', 'Noo'};

  if(y_n_tag == YES)
  {
    for(int i = 0; i < 15; i++)
    {
      if(strcmp(yes_no, yes_answers[i]) == 0)
        found = 1;
    }
    return found;
  }
  else if(y_n_tag == NO)
  {
    for(int i = 0; i < 10; i++)
    {
      if(strcmp(yes_no, no_answers[i]) == 0)
        found = 1;
    }
    return found;
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
