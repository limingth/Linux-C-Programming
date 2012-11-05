#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node * link;

struct node 
{
    char item[32];
    int counter;

    link l, r;
};

link make_node(char * key)
{
    link p = malloc(sizeof(struct node));

    strcpy(p->item, key);
    p->counter = 1;

    p->l = NULL;
    p->r = NULL;

    return p;
}

void travel(link p, int depth)
{
    if (!p)
	    return;

    // in_order  Left->Self->Right
    travel(p->l, depth+1);
    //printf("node depth is <%d>\n", depth);
    //printf("node item is <%s>\n", p->item);
    //printf("node counter: %d\n", p->counter);
    printf("node (l=%d): c=%d\t<%s>\n", depth, p->counter, p->item);
    travel(p->r, depth+1);

    return;
}

link search_node(link p, char * key)
{
    if (!p)
	    return NULL;
    
    if (strcmp(key, p->item) == 0)
	    return p;

    if (strcmp(key, p->item) < 0)
	return search_node(p->l, key);
    else
	return search_node(p->r, key);

    return NULL;
}

link insert_node(link p, char * key)
{
    if (!p)
	    return make_node(key);
    
    // compare key, p->item
    if (strcmp(key, p->item) < 0)
	    p->l = insert_node(p->l, key);
    else
	    if(strcmp(key, p->item) > 0)
		    p->r = insert_node(p->r, key);
	    else
		    p->counter++;
    return p;
}

char buf[1024] = 
{
    "This is a       book.\n"
    "That is a bag.\n"
    "This is a pencil.\n"
    "That is a ship.\n"
};

int main(void)
{
    printf("hello, my word! \n");

    printf("%s", buf);

    int i = 0;
    int state = 0;
    char word[32];
    int j = 0;
    char c;

#if 0
    link root = NULL;
    root = insert_node(root, "This");
    root = insert_node(root, "is");
    root = insert_node(root, "a");
    root = insert_node(root, "book");

    root = insert_node(root, "This");
    // print all nodes
    travel(root, 1);
    return 0;

#endif

    link root = NULL;
    while ((c = buf[i++]) != '\0')
    {
	if (isalpha(c))
	{
	    word[j++] = c;
	    state = 1;
	}
	else
	if ((c == ' ' || c == '\n') && state == 1)
	{
	    word[j] = '\0';
	    //printf("find a word: <%s>\n", word);

	    root = insert_node(root, word);
	    travel(root, 1);
	    printf("------------------\n");

	    // begin to find next word
	    j = 0;
	    state = 0;
	}
    }

    // print all nodes
    travel(root, 1);

    // search user word
    char input[32];

again:
    printf("please input your search word: ");
    //scanf("%s", input);
    strcpy(input, "is");

    link tmp = search_node(root, input);
    if (tmp)
	    printf("found %s: c=%d\n", tmp->item, tmp->counter);
    else
	    printf("not found %s\n", input);

    //goto again;

    return 0;
}
