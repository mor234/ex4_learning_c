#include  <stdio.h>
#include  <stdlib.h>//malloc
#include  <string.h>//memset
#include <ctype.h>//tolower
#include "trie.h"

char * getWord(boolean * isEOF);

/*
 *The program will read words from the standard input and print
 * the list of words that were seen in the input with the number
 * of occurrences of each and every word. The list should be printed,
 * depending on the parameter from the command line, in one of the following ways:
  • List sorted in ascending lexicographic order (default)
  • List sorted in descending lexicographic order (by parameter).
 */
int main(int argc, char* argv[]) {

    boolean  isEOF=FALSE;
    trie * myTrie=newTrie();
    if (myTrie==NULL)
    {
        printf("failed to allocate memory\n");
        return 0;
    }

    while (!isEOF)
    {
        char * word=getWord(&isEOF);//get word from user
        if(word!=NULL)//if received a word.
        {
            addWord(myTrie,word);
            free(word);
        }
    }
    if(argc==2&&argv[argc-1][0]=='r'&&argv[argc-1][1]=='\0')
    {
        printOpLex(myTrie);//print List sorted in descending lexicographic order (by parameter).
    }
    else
        printLex(myTrie);//print List sorted in ascending lexicographic order

    delTrie(&myTrie);





}
/*
 * The function receives words from the user
 * and allocate memory according to what is given, dynamically.
 * Returns NULL if failed to allocate memory.
 * Ignores characters that are different from English letters,
 * and saves uppercase letters that are received as lowercase letters.
 * End word identified with the characters: ' ', '\ t', '\n'
*/
char * getWord(boolean * isEOF)
{
    char c;
    char *word = NULL;
    int size = 1;

    word = (char*)malloc((size+1)*sizeof(char));
    memset(word, 0,(size+1)*sizeof(char));//put Null in all the array

    word[size-1] = '\0';
    c = getchar();
    while(c !=' '&&c!='\n'&&c!='\t')
    {
        if(c==EOF)//if reached EOF, sign and return the word so far.
        {
            *isEOF=TRUE;
            return word;
        }
        if(c>='A'&&c<='Z')
            c=tolower(c);
        if(c>='a'&&c<='z')//else- it is not a legal chraracter and ignore it.
        {
            word[size-1] = c;
            char *tmp = (char*)realloc(word,sizeof(char)*(size+1));
            if (tmp !=NULL)
            {
                word=tmp;
                word[size] = '\0';
                size++;
            }
            else
            {
                printf("failed to allocate memory\n");
                //sign to end, continue with what it has so far,
                // continue the program so free all that need to be freed in the main program
                free(word);
                *isEOF=TRUE;
                return word;

            }
        }
        c = getchar();

    }
    return word;
}