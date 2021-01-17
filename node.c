#include <stdio.h>
#include  <stdlib.h>//malloc
#include <string.h>//memset

#include "node.h"

struct node {
    char letter;
    boolean hasChildren;
    boolean isCountPrinted;
    boolean done;//used when print- this way knows not to return to this node because it was printed and all it's children printed.
    long unsigned int count; //if count =0 means no word ends in this node
    struct node *children[NUM_LETTERS];
};

/*
    constructor for node- allocate memory for node and init the variables
*/
node *newNode(char l) {
//    printf(" newNode ");
    node *n = (node *) malloc(sizeof(node));
    if (n != NULL) {
        n->letter = l;
        n->hasChildren = FALSE;
        n->isCountPrinted = FALSE;//
        n->count = 0;
        n->done = FALSE;

        memset(n->children, 0, NUM_LETTERS * sizeof(node *));//put Null in all the array
    }
    return n;//if returns null, sign alloc was un sucssesful
}

/*
    destructor for node- receive pointer to pointer to node,
    if not null, free the children recursively and then free this node memory.
    change the pointer to Null after free.
*/
void delNode(node **nodeToDel) {
    if (nodeToDel != NULL) {
        if (*nodeToDel != NULL) {
            //if has children-delete the children
            if ((*nodeToDel)->hasChildren) {
                for (int i = 0; i < NUM_LETTERS; i++) {
                    if ((*nodeToDel)->children[i] != NULL)
                        delNode(&(*nodeToDel)->children[i]);
                }
            }
            //delete this node
            free(*nodeToDel);
            *nodeToDel = NULL;
        }
    }
}

/*
set the flags: isCountPrinted and done
to False for the all the tree that start in his node.
(for this node add all the children and so on.) recursive.
*/
void setIsCountPrintedDoneFalse(node *nodeToSet) {
    if (nodeToSet != NULL) {

        //if has children-set the children
        if (nodeToSet->hasChildren) {
            for (int i = 0; i < NUM_LETTERS; i++) {
                if (nodeToSet->children[i] != NULL)
                    setIsCountPrintedDoneFalse(nodeToSet->children[i]);
            }
        }
        //set itself
        nodeToSet->isCountPrinted = FALSE;
        nodeToSet->done = FALSE;

    }
}


/*
A function receives a pointer to a node, a character and a flag that says whether this is the last letter in the word.
The function adds the letter to the node  so that if there is no indication in the children's array to the next letter,
assigns a memory to a new node and make it oin to it.
If not and this is the last letter adds to the counter in the cell of the last letter one,
otherwise does nothing.
Returns pointer to the node of the new letter dded.
*/
node *addLetter(node *n, char l, boolean isLast) {
    int letterIndex = l - FIRST_CHAR;
    if (letterIndex < 0 || letterIndex > NUM_LETTERS - 1) {
        printf("Error. illegal letter/n");

        return NULL; //l is not a legal letter. suppose to be checked before, but check again to prevant acsses to out of bounday of the array.
    }
    n->hasChildren = TRUE;
    if (n->children[letterIndex] == NULL) {
        n->children[letterIndex] = newNode(l);
        if (n->children[letterIndex] == NULL) {
            printf("Error. failed to allocate memory/n");
            return NULL;
        }
    }
    if (isLast) {
        //add to count of letters that end at the node childPointer points to.
        (n->children[letterIndex]->count)++;
    }
    return n->children[letterIndex];
}
/*
 *A recursive function that prints the words in upward lexicographic order.
 * works as follows:
 * Prints the current character, the current counter if greater than zero and not printed.
 * Calls itself with the current vertex to print the continuation of the word -
 * goes first to the smallest letter, etc. to maintain upward lexicographic order.
 * A letter that has been printed and all its children have been printed / has no children -
 * the flag done is marked as true and in repeated passages on the tree will not be printed again.
 * If any continuation of a word has already been printed, - for the continuation of another word - another "child" in the array,
 * call the function with the initial vertex.
 *
 */

void printLexNode(node *n, node *root) {   
    if((n->letter)!='\0')//if it's not the root
        printf("%c", n->letter);//print this letter
    if (n->count > 0 && !(n->isCountPrinted)) {//if a word ends here and the counter wasn't printed already- print the counter
        printf(" %ld\n", n->count);
        n->isCountPrinted = TRUE;
    }
    /*
     * A flag indicating whether this is the first time the children of the letter have been printed -
     * if so, continue to print and thus print an entire word.
     * If not, you need to print the word from the beginning,
     * but now we have marked the previous vertex - as done , so that it will not be reprinted.
     */
    boolean alreadyEntered = FALSE;
    for (int i = 0; i < NUM_LETTERS; i++) //goes from the smallest letter to the largest- upward lexicographic order
    {
        if (n->children[i] != NULL && !(n->children[i]->done)) {
            if (alreadyEntered) {
                printLexNode(root, root);//print the word from the start
            } else {
                alreadyEntered = TRUE;
                printLexNode(n->children[i], root);//print the rest of the word
            }
        }
    }
    n->done = TRUE;//finish printing all the children, no more words


}
/*
 *A recursive function that prints the words in downward lexicographic order.
 * works as follows:
 * Prints the current character, the current counter if greater than zero and not printed.
 * Calls itself with the current vertex to print the continuation of the word -
 * goes first to the largest letter, etc, to maintain downward lexicographic order.
 * A letter that has been printed and all its children have been printed / has no children -
 * the flag done is marked as true and in repeated passages on the tree will not be printed again.
 * If any continuation of a word has already been printed, - for the continuation of another word - another "child" in the array,
 * call the function with the initial vertex.
 *
 */

void printOpLexNode(node *n, node *root) {
    if((n->letter)!='\0')//if it's not the root
        printf("%c", n->letter);
    if (n->count > 0 && !(n->isCountPrinted)) {
        printf(" %ld\n", n->count);
        n->isCountPrinted = TRUE;
    }
    boolean alreadyEntered = FALSE;
    for (int i = NUM_LETTERS - 1; i >= 0; i--) {
        if (n->children[i] != NULL && !(n->children[i]->done)) //goes from the smallest letter to the largest- downward lexicographic order
        {
            if (alreadyEntered) {
                printOpLexNode(root, root);//print the word from the start
            } else {
                alreadyEntered = TRUE;
                printOpLexNode(n->children[i], root);
            }
        }
    }
    n->done = TRUE;

}