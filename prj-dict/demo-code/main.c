#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "linkedlist.h"
#include "btree.h"

#define BTREE_FILE  "btree.txt"

extern btree root;

int parse_dict(char * filename, void(*callback)(char *, char *));

void print_word(link p)
{
	static int counter = 0;

	counter++;
//	printf("%d [%s]: <%s>\n", counter, p->word.name, p->word.meaning);

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

void btree_loadfromfile(char * filename)
{
    FILE * fp;

    printf("load btree from file <%s>\n", filename);

    fp = fopen(filename, "r");

    while (!feof(fp))
    {
	char wordname[64];
	int counter;
	link p;
	btree tmp;
	int null;

	fscanf(fp, "%s %d\n", wordname, &counter);

	tmp = btree_make_node(wordname);
	tmp->counter = counter;

	p = search(wordname, &null);
	root = btree_insert(root, wordname, &p->word);
	printf("load from file [%s]: <%d>\n", wordname, counter);
    }

    btree_travel(root, 0);
    fclose(fp);
}

int main(int argc, char * argv[])
{
	char * dictfile;
	int cmp = 0;

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

	// set up btree with file record
	btree_loadfromfile(BTREE_FILE);

	while (1)
	{
		char input[32];
		link p;
		btree t;

		printf("\nplease input a word: ");
		scanf("%s", input);

		// type "bye!" to quit
		if (strcmp(input, "bye!") == 0)
			break;

		printf("input word: [%s]\n", input);

	    #if 1
		cmp = 0;
		t = btree_search(root, input, &cmp);
		if (t != NULL)
		{
		    printf("btree found! \n");

		    t->counter++;
		    if (t->pword)
			printf("(cmp%d) word [%s] meaning is: <%s> (search No.%d in btree)\n", cmp, input, t->pword->meaning, t->counter);

		    continue;
		}
		else
		    printf("btree not found! search linkedlist...\n");
	    #endif

		p = search(input, &cmp);
		if (p == NULL)
			printf("search word <%s> not found!\n", input);
		else
		{
			btree tmp;
			printf("(cmp%d) word [%s] meaning is: <%s> (search No.1 in list)\n", cmp, input, p->word.meaning);
			printf("insert <%s> to btree!\n", input);
			root = btree_insert(root, input, &p->word);
			btree_travel(root, 0);
		}
	}

	btree_savetofile(BTREE_FILE);
	printf("Thanks for using mydict program. \n");

	return 0;
}
