#pragma once
#include "node.h"
typedef struct trie trie;
trie* newTrie();
void delTrie (trie ** t);
boolean addWord (trie * t, char * word);
void printLex (trie *t);
void printOpLex (trie *t);
