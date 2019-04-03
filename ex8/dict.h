/* original: Graham Nov 2000,
   modified: Pete Dec 2010,
   			 Aria Jul 2018
 */

typedef char* Key_Type;
typedef struct table* Table;    // allows different definitions of struct table

Table initialize_table ();      // allows different parameters
Table insert (Key_Type, Table);
Boolean find (Key_Type, Table);
void print_table (Table);
void print_stats (Table);
void tidy (Table); // tidy up the table data structure
