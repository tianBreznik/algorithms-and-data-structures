#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

//a tree pointer that points to a node
typedef struct node *tree_ptr;

typedef struct node
{
  Key_Type element; // only data is the key itself
  tree_ptr left;
  tree_ptr right;
  int height;
} node;

struct table
{
  tree_ptr head; // points to the head of the tree
};

void treePrint(tree_ptr temp);
tree_ptr makeNode(char* new_key);
int getHeight(tree_ptr node);
int getMax(int stringA, int stringB);
int getBalanceCf(tree_ptr node);








Boolean find(char* key_find, Table data_tree);
void free_tree(tree_ptr node_ref);
tree_ptr InsertNodeBin(char* key_insert, tree_ptr root);
tree_ptr InsertNodeAVL(char* key_insert, tree_ptr subroot);
int getTreeHeight(tree_ptr analyzeNode);
tree_ptr search(char* key, tree_ptr head);



//function evaluates two strings and returns the alphabetically larger one of
//the two
int getMax(int first, int second)
{
  return (first > second) ? first : second;
}//getMax

//helper function to extract height property from a node
int getHeight(tree_ptr node)
{
  if(node == NULL)
    return 0;
  else
    return node->height;
}//getHeight

//helper function to get the balance coefficient at a node
int getBalanceCf(tree_ptr node)
{
  if(node == NULL)
    return 0;
  else
    return getHeight(node->left)-getHeight(node->right);
}//getBalanceCf

tree_ptr right_rotation(tree_ptr node)
{
  //node is y following search and repair convention
  tree_ptr x = node->left;
  tree_ptr subtree_2 = x->right;

  //actual rotation
  x->right = node;
  node->left = subtree_2;

  //update heights - O(1)
  node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
  x->height = getMax(getHeight(x->left), getHeight(x->right)) + 1;

  return x;
}//right_rotation

tree_ptr left_rotation(tree_ptr node)
{
  //node is x following search and repair convention
  tree_ptr y = node->left;
  tree_ptr subtree_2 = y->right;

  //actual rotation
  y->left = node;
  node->right = subtree_2;

  //update heights - O(1)
  node->height = getMax(getHeight(node->left), getHeight(node->right)) + 1;
  y->height = getMax(getHeight(y->left), getHeight(y->right)) + 1;

  return y;
}//left_rotation



Table initialize_table(/*ignore parameter*/)
{

   Table initialized = (Table)malloc(sizeof(Table));
   initialized ->head = NULL;
   return initialized;
}//initialize_table


tree_ptr TreeSearch(char* key_search, tree_ptr subtree)
{
  if (subtree == NULL || (strcmp(subtree->element, key_search) == 0))
    return subtree;
  else if (strcmp(key_search, subtree->element) < 0)//search key is less than key
    return TreeSearch(key_search, subtree->left);
  else
    return TreeSearch(key_search, subtree->right);
}//TreeSearch

tree_ptr search(char* key, tree_ptr head)
{
    if ( head != NULL)
    {
        //note change to strcmp
        int res = strcmp(key, head->element);
        if (!res)
            return head;
        else if(res < 0)
            return search( key, head->left );
        else
            return search(key, head->right);
    }
    else
        return FALSE;
}//search

tree_ptr InsertNodeBin(char* key_insert, tree_ptr root)
{
  //printf("------\n");
  //if(root != NULL) printf("parent being %s\n", root -> element);
  //printf("inserting %s\n", key_insert);
  if(root == NULL)
  {
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
        root -> right = InsertNodeBin(key_insert, root->right);
        //printf("right");
      }
      else
      {
        root -> left = InsertNodeBin(key_insert, root->left);
        //printf("left");
      }
    }
    return root;
  }
}//InsertNodeBin

tree_ptr InsertNodeAVL(char* key_insert, tree_ptr subroot)
{
  //printf("------\n");
  //if(root != NULL) printf("parent being %s\n", root -> element);
  //subroot because root is a subroot of itself
  if(subroot == NULL)
  {
    return makeNode(key_insert);
  }
  else
  {
    int key_comparator = strcmp(key_insert, subroot->element);
    //fprintf(stderr, "inserting %s\n", root->element);
    if(key_comparator != 0)
    {
      if(strcmp(key_insert, subroot->element) > 0)
      {
        //printf("%s\n",subroot->element);
        //in recursive cases nothing is returned so the function isn't broken
        subroot -> right = InsertNodeAVL(key_insert, subroot->right);
        //printf("right");
      }
      else
      {
        //printf("%s\n", subroot->element);
        subroot -> left = InsertNodeAVL(key_insert, subroot->left);
        //printf("left");
      }
    }
    return subroot;
  }

  //update height
  subroot->height = 1 + getMax(getHeight(subroot->left), getHeight(subroot->right));

  //calculate balance at node
  int balance = getBalanceCf(subroot);

  int key_comparator_left = strcmp(key_insert, subroot->left->element);
  int key_comparator_right = strcmp(key_insert, subroot->right->element);
  //left single rotation
  if (balance > 1 && key_comparator_left < 0)
    return right_rotation(subroot);
  //right single rotation
  if (balance < -1 && key_comparator_right > 0)
    return left_rotation(subroot);

  //left double rotation
  if (balance > 1 && key_comparator_left > 0)
  {
    subroot->left = left_rotation(subroot->left);
    return right_rotation(subroot);
  }

  if (balance > 1 && key_comparator_right < 0)
  {
    subroot->right = right_rotation(subroot->right);
    return left_rotation(subroot);
  }

  //if tree was already balanced after insertion (recursive cases) return
  //root of updated tree
  return subroot;
}//InsertNodeAVL

tree_ptr makeNode(char* new_key)
{
  tree_ptr new_node = (tree_ptr)malloc(sizeof(node));
  new_node -> left = NULL;
  new_node -> right = NULL;
  new_node -> element = (char*)malloc(sizeof(new_key));
  new_node -> element = strcpy(new_node->element, new_key);
  new_node -> height = 1;
  return new_node;
}//makeNode

//ignores duplicates -- implies before every insert check if the word is
//already in the tree
Table insert(char* key_insert,Table table)
{
  //a pointer that points to the pointer which points to the head of the tree
  //initially! - Might/will cause problems by passing to TreeSearch
  if(mode == 1)
    table->head = InsertNodeBin(key_insert, table->head);
  else if(mode == 2)
    table->head = InsertNodeAVL(key_insert, table->head);
  // printf("updated head is:%s\n", table->head->element);
  return table;
}//insert

Boolean find(char* key_find, Table data_tree)
{
   tree_ptr head_ptr = data_tree->head;
   tree_ptr found_ptr = search(key_find, head_ptr);
   if (found_ptr == FALSE)
     return FALSE;
   else
     return TRUE;
}//find

void print_table(Table data_visualize)
{
   tree_ptr head_print =  data_visualize->head;
   treePrint(head_print);
}//print_table

void tidy(Table table)
{
  tree_ptr head_ptr = table->head;
  free_tree(head_ptr);
  free(table);
}//tidy

void free_tree(tree_ptr node_ref)
{
  if(node_ref == NULL)
  {
    return;
  }else
  {
    //free children if children are NULL then recurse back
    free_tree(node_ref->left);
    free_tree(node_ref->right);
    free(node_ref->element);
    free(node_ref);
  }
}//free_tree

void treePrint(tree_ptr temp)
{
  if(temp == NULL)
  {
    return;
  }else
  {
    //print node
    fprintf(stdout, "%s\n", temp->element);
    treePrint(temp->left);
    treePrint(temp->right);
  }
}//treePrint

int getTreeHeight(tree_ptr analyzeNode)
{
  if(analyzeNode == NULL)
    return 0;
  int leftH = getMax(0, getTreeHeight(analyzeNode->left));
  int h = getMax(leftH, getTreeHeight(analyzeNode->right));
  return h + 1;
}//getTreeHeight

void print_stats (Table data_analyze)
{
  tree_ptr head_print =  data_analyze->head;
  int height = getTreeHeight(head_print);
  printf("Tree height: %d\n", height);
}//print_stats
