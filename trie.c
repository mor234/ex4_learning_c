#include <stdio.h>
#include <stdlib.h>//malloc
#include "trie.h"


struct trie {
    node *root ;
} ;

/*
 * constructor:
 * create new trie, by allocating memory for it and then creating the root by calling to newNode
 * the sign it's the root- the letter contains '\0'
 * if returns null, sign alloc was un successful
*/
trie* newTrie()
{
    trie* t= (trie*)malloc (sizeof (trie));
    if (t!=NULL)
    {
        t->root=newNode('\0'); //creat the root of the trie. the sign it's the root- the letter contains '\0'
        if (t->root==NULL)//alloc of root didn't succeed
        {
            free(t); //so will return NULL and sign it didn't succeed
            t=NULL;
        }

    }
    return t;//if returns null, sign alloc was un successful
}
/*
 * destructor:
 * delete a trie by calling to the function that recursively delete all the nodes of the trie and free the allocations,
 * and then delete the pointer to the trie itself.
*/
void delTrie (trie ** t)
{
    if(t!=NULL)
    {
        if(*t!=NULL)
        {
            if((*t)->root!=NULL)
            {
                delNode(&((*t)->root));
            }
            free(*t);
            *t=NULL;
        }
    }
}
/*
 * add a word to the trie, by calling the function addLetter on each letter of the word.
 * assumes word at least in the size of 1 letter and ends with '\0'
 * assumes t!=NULL
*/
boolean addWord (trie * t, char * word)
{
    boolean isLast=FALSE;
    node * currNode=t->root;
    int i=0;
    do{
        if(((int)word[i]>=FIRST_CHAR)&&word[i]<=LAST_CHAR)//if legal letter
        {
            if(word[i+1]=='\0')
                isLast=TRUE;

            node * tmp= addLetter (currNode,word[i], isLast);
            if(tmp==NULL)
                return FALSE;
            currNode=tmp;
        }
        i++;


    }while(word[i]!='\0');

    return TRUE;
}
/*
 * print all the words and the number they appeared in an upward lexicographic order
 */

void printLex (trie *t)
{
    setIsCountPrintedDoneFalse(t->root);
    printLexNode(t->root,t->root);
}
/*
 * print all the words and the number they appeared in a downward lexicographic order
 */
void printOpLex (trie *t)
{
    setIsCountPrintedDoneFalse(t->root);
    printOpLexNode(t->root,t->root);
}
