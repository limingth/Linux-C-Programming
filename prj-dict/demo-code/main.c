#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "linkedlist.h"

int parse_dict(char * filename, void(*callback)(char *, char *));

void print_word(link p)
{
	static int counter = 0;

	counter++;
	printf("%d [%s]: <%s>\n", counter, p->word.name, p->word.meaning);

	return;
}

void insert_word(char * name, char * meaning)
{
	link p;
	word_t item;

	// copy the content to a tmp item;
	strcpy(item.name, name);
	strcpy(item.meaning, meaning);

	p = make_node(item);
	insert(p);

	return;
}

int main(int argc, char * argv[])
{
	char * dictfile;

	if (argc <= 1)
		dictfile = "test_dict.txt";
	else
	{
		if (argc >= 3 && strcmp(argv[1], "-f") == 0)
			dictfile = argv[2];
	}
	printf("using dict file <%s>\n", dictfile);

	// get word name and meaning from filename
	// insert word to linked list
	parse_dict(dictfile, insert_word);

	// travel the list to print every word
	printf("\ntraverse word list ...\n");
	traverse(print_word);

	while (1)
	{
		char input[32];
		link p;

		printf("\nplease input a word: ");
		scanf("%s", input);

		// type "bye!" to quit
		if (strcmp(input, "bye!") == 0)
			break;

		printf("input word: [%s]\n", input);
		p = search(input);
		if (p == NULL)
			printf("search word <%s> not found!\n", input);
		else
			printf("word [%s] meaning is: <%s> \n", input, p->word.meaning);
	}

	printf("Thanks for using mydict program. \n");

	return 0;
}
