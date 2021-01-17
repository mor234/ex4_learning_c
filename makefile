all: frequency

frequency: main.o node.o trie.o
	gcc -Wall -g main.o node.o trie.o -o frequency
	
run:
	./frequency<input.txt>fre_output.txt	
	./frequency r<input.txt>fre_r_output.txt
	diff fre_output.txt frequency_expected.txt
	diff fre_r_output.txt frequency_r_expected.txt
trie.o: node.o trie.h  trie.c
	gcc -Wall -g -c trie.c

node.o:  node.h node.c 
	gcc -Wall -g -c node.c

main.o: main.c
	gcc -Wall -g -c main.c
	
clean:
	rm *.o frequency fre_output.txt	fre_r_output.txt