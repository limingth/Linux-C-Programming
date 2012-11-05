#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main( int argc, char * argv[])
{
	lnode * pnode;
	FILE * fp;
	char * line = NULL;
    	size_t len = 0;
    	ssize_t read;

#if 0
		pnode = (lnode *) malloc (sizeof(lnode));	
		if( pnode )
		{
			pnode->pline = "aabb";
			pnode->next = NULL;
		}

		list_insert( pnode );
		list_print();
	
	
		pnode = (lnode *) malloc (sizeof(lnode));	
		if( pnode )
		{
			pnode->pline = "ccdd";
			pnode->next = NULL;
		}

		list_insert( pnode );
		list_print();

		return 0;
#endif
	fp = fopen(argv[1], "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) 
	{
		printf("Retrieved line of length %zu :\n", read);
		printf("%s", line);

		pnode = (lnode *) malloc (sizeof(lnode));	
		if( pnode )
		{
			pnode->pline = (char *) malloc ( strlen(line) );
			strcpy( pnode->pline, line );
//			pnode->pline = line;
			pnode->next = NULL;
		}

		list_insert( pnode );
		list_print();
	}

	return 0;
}
