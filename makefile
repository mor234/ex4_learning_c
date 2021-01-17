all: frequency

frequency: main.o node.o trie.o
	gcc -Wall -g main.o node.o trie.o -o frequency
	
trie.o: node.o trie.h  trie.c
	gcc -Wall -g -c trie.c

node.o:  node.h node.c 
	gcc -Wall -g -c node.c

main.o: main.c
	gcc -Wall -g -c main.c
	
clean:
	rm *.o frequency