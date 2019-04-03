#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

//a tree pointer that points to a node
//ONLY A POINTER - SO WE DON'T HAVE TO DEREFERENCE EVERY TIME

typedef struct node *tree_ptr;

typedef struct node
{
  Key_Type element; // only data is the key itself
  tree_ptr left;
  tree_ptr right;
  int depth;
  // add anything else that you need
} node;

struct table
{
  tree_ptr head; // points to the head of the tree
  // add anything else that you need
};

void treePrint(tree_ptr temp);
tree_ptr makeNode(char* new_key);
int getHeight(tree_ptr node);
char* getMax(char* stringA, char* stringB);



int getHeight(tree_ptr node)
{
  if(tree_ptr == NULL)
    return 0;
  else
    return node->height;
}

Table initialize_table(/*ignore parameter*/)
{
   //tree_ptr root = (tree_ptr)malloc(sizeof(node));
   //root -> left = NULL;
   //root -> right = NULL;
   //root -> element = NULL;

   Table initialized = (Table)malloc(sizeof(Table));
   initialized ->head = NULL;
   return initialized;
}


tree_ptr TreeSearch(char* key_search, tree_ptr subtree)
{
  if (subtree == NULL || (strcmp(subtree->element, key_search) == 0))
    return subtree;
  else if (strcmp(key_search, subtree->element))//search key is less than key
    return TreeSearch(key_search, subtree->left);
  else
    return TreeSearch(key_search, subtree->right);
}

tree_ptr InsertNode(char* key_insert, tree_ptr root)
{
  //printf("------\n");
  //if(root != NULL) printf("parent being %s\n", root -> element);
  //printf("inserting %s\n", key_insert);
  if(root == NULL)
  {
    //tree_ptr new_node = (tree_ptr)malloc(sizeof(node));
    //new_node -> left = NULL;
    //new_node -> right = NULL;
    //new_node -> element = (char*)malloc(sizeof(key_insert));
    //new_node -> element = strcpy(new_node->element, key_insert);
    //new_node -> depth = 0;
    //printf("inserted %s\n",key_insert);
    //return new_node;
    return makeNode(key_insert);
  }
  else
  {
    int key_comparator = strcmp(key_insert, root->element);
    //fprintf(stderr, "inserting %s\n", root->element);
    if(key_comparator != 0)
    {
      if(strcmp(key_insert, root->element) > 0)
      {
        printf("%s\n",root->element);
        root -> right = InsertNode(key_insert, root->right);
        //printf("right");
      }
      else
      {
        printf("%s\n", root->element);
        root -> left = InsertNode(key_insert, root->left);
        //printf("left");
      }
    }
    return root;
  }
}

tree_ptr makeNode(char* new_key)
{
  tree_ptr new_node = (tree_ptr)malloc(sizeof(node));
  new_node -> left = NULL;
  new_node -> right = NULL;
  //new_node -> element =new_key;
  new_node -> element = (char*)malloc(sizeof(new_key));
  new_node -> element = strcpy(new_node->element, new_key);
  new_node -> depth = 0;
  return new_node;
}
//ignores duplicates -- implies before every insert you check if the word is
//already in the tree
Table insert(char* key_insert,Table table)
{
  //a pointer that points to the pointer which points to the head of the tree
  //initially! - Might/will cause problems by passing to TreeSearch
  //tree_ptr *search_ptr = &(table->head);
  //tree_ptr *head_ptr =  &(table->head);
  tree_ptr head_ptr = table->head;
  // if(head_ptr!= NULL) fprintf(stderr, "head is: %s\n",table->head->element);
  table->head = InsertNode(key_insert, table->head);
  // printf("updated head is:%s\n", table->head->element);
  return table;

}

Boolean find(char* key_find, Table data_tree)
{
	/* you can define and call another function
	 that passes the head of the tree*/
   return 1;
}

void print_table(Table data_visualize)
{
	/* you can define and call another function
	 that passes the head of the tree*/
   tree_ptr head_print =  data_visualize->head;
   treePrint(head_print);
}

int count = 0;
void treePrint(tree_ptr temp)
{
  if(temp == NULL)
  {
    return;
  }else
  {
    //print node
    count++;
    fprintf(stdout, "%d%s\n", count, temp->element);
    treePrint(temp->left);
    treePrint(temp->right);
  }
}

void print_stats (Table data_analyze)
{
}
