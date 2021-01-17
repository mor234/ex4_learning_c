#pragma once

#define NUM_LETTERS ((int)26)
#define FIRST_CHAR ((int)'a') //define start of char range
#define LAST_CHAR ((int)'z') //define end of char range
typedef enum {FALSE=0, TRUE=1} boolean;
typedef struct node node;
node* newNode(char l);
void delNode(node ** nodeToDel);
node* addLetter (node * n, char l,boolean isLast);
void setIsCountPrintedDoneFalse(node * nodeToSet);
void printLexNode (node *n,node *root);
void printOpLexNode(node *n,node *root) ;





