#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define __USE_BSD
#include <string.h>

#include "speller.h"
#include "dict.h"

typedef struct
{ // hash-table entry
  Key_Type element; // only data is the key itself
  //enum to denote state of a cell - makes linear probing more efficient
  enum {empty, in_use, deleted} state;
} cell;

typedef unsigned int Table_size; // type for size-of or index-into hash table

struct table
{
  cell *cells;
  Table_size table_size; // cell cells [table_size];
  Table_size num_entries; // number of cells in_use
  Table_size nr_collisions;
  // add anything else that you need
};

Table linear_probing(Table table, int start_index, Key_Type key);
int hash_func(Key_Type element);
Table quadratic_probing(Table table, int start_index, Key_Type key);
int second_hash(Key_Type key);
Boolean find (Key_Type key, Table table);
Table double_hash_resolve(Table table, int start_index, Key_Type key);
void tidy(Table table);

Table initialize_table (Table_size size)
{
  Table table = (struct table*)malloc(sizeof(struct table));
  //initializing cells
  int count = 0;
  table->cells = malloc(size);
  while(count<size)
    table->cells[count].state = 1; //in use
  table->num_entries =0;
  table->nr_collisions = 0;
  return table;
}

Table insert (Key_Type new_key, Table table)
{
  int hash_index;
  if(mode == 1)
    hash_index = hash_func(new_key);
  else if(mode==2)
    hash_index = second_hash(new_key);
  if(table->cells[hash_index].state == 1)
  {
    if(table->num_entries == table->table_size)//full
      exit(0);//EXITCODE 0
    //if not full insert new key at hash index
    table->cells[hash_index].element = new_key;
    table->num_entries = table->num_entries +1;
    return table;
  }
  else //there has been a collision
  {
    table->nr_collisions = table->nr_collisions+1;
    table=linear_probing(table, hash_index, new_key);
    return table;
  }

}

Table linear_probing(Table table, int start_index, Key_Type key)
{
  int index = start_index+1;//start probing at provided table location

  while(index < table->table_size)
  {
    //probably never happens
    if(index  == start_index)
    {
      printf("hash table is full, resize\n");
      break;
    }//if
    else if(index == (table->table_size-1)&&table->cells[index].state !=1)
    {
      index = 0;
    }//elseif
    else
    {
      if(table->cells[index].state ==1)
      {
        table->cells[index].element = key;
        table->num_entries = table->num_entries +1;
        break;
      }//if
      else
        index=index+1;
    }//else
  }//while
  return table;
}//linear_probing

int hash_func(Key_Type element)
{
  int sum = 1;
  int i, j = 0;

  char upper_case[26];
  char lower_case[26];

  while(i<26)
  {
    upper_case[i] = (char)(i+65);
    lower_case[i] = (char)(i+97);
    i=i+1;
  }

  i=0;
  while(i<strlen(element))
  {
    for(j=0;j<26;j++)
    {
      //upper and lower cases of the same character have the same hash value
      if(element[i] == upper_case[j] || element[i] == lower_case[j])
      {
        sum = sum +j;//count identical characters
        break;
      }//if
    }//for
  }//for
  return sum;
}

Table quadratic_probing(Table table, int start_index, Key_Type key)
{
  int index = start_index+1;
  //initialize probing factor/coefficient to 1
  int factor = 1;
  while(index <table->table_size)
  {
    if(index == start_index)
    {
      printf("hash table is full, resize\n");
      break;
    }//if
    else if(index == table->table_size - 1 && table-> cells[index].state!= 1)
    {
      index = 0;
    }//else if
    else
    {
      if(table->cells[index].state ==1)
      {
        table->cells[index].element = key;
        table->num_entries = table->num_entries + 1;
        break;
      }//if
      else
      {
        index = index + factor*factor;
        factor++;
      }//else
    }//else
  }//while
  return table;
}//quadratic_probing

int second_hash(Key_Type key)
{
  int partial_sum = 1;
  int i, j = 0;

  char upper_case[26];
  char lower_case[26];

  while(i<26)
  {
    upper_case[i] = (char)(i+65);
    lower_case[i] = (char)(i+97);
    i=i+1;
  }

  for(i = 0; i<strlen(key); i++)
  {
    for(j=0;j<26;j++)
    {
      //upper and lower cases of the same character have the same hash value
      if(key[i] == upper_case[j] || key[i] == lower_case[j])
      {
        partial_sum = partial_sum +j;//count identical characters
        break;
      }//if
    }//for
  }//for
  return partial_sum/13;
}

Boolean find (Key_Type key, Table table)
{
  int search_index = 0;
  //look through all the elements
  while(search_index <table->table_size)
    if(strcmp(key,table->cells[search_index].element)==0)
      return TRUE;

  //No cell with key is found
  return FALSE;
}//find

Table double_hash_resolve(Table table, int start_index, Key_Type key)
{
  int index = second_hash(key);
  if(index == start_index)
  {
    printf("Insertion failed\n");
    return table;
  }
  table->cells[index].element = key;
  table->num_entries = table->num_entries +1;
  return table;
}//double_hash_resolve

void print_table (Table table)
{
  int print_index = 0;
  while(print_index < table->table_size)
  {
    printf("%d: %s\n",print_index,table->cells[print_index].element);
    print_index++;
  }
}//print_table

void print_stats (Table table)
{
  printf("The number of collisions occured is: %d\n", table->nr_collisions );
}//print_stats

void tidy(Table table)
{
  free(table);
}//tidy
