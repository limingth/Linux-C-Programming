#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 1, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 1, 0, 1, 0 },
	{ 0, 0, 0, 0, 0 },
};

void print_maze(void)
{
	int i, j;

	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
			printf( "%2d-%2d\t", i*MAX_COL+j, maze[i][j] );

		printf( "\n" );
	}

	printf( "******************\n" );
	return;
}

struct point {
	int row;
	int col;
} stack[512]; 

int top = 0;

void push( struct point p )
{
	stack[top++] = p;
}

struct point pop(void)
{
	return stack[--top];
}

struct point get_top(void)
{
	return stack[top-1];
}

int is_empty(void)
{
	return (top==0);
}

void print_stack(void)
{
	int i;

	printf( "stack info : \n" );
	for(i = top-1; i >= 0; i--)
	{
		printf( "(%d, %d) %d\n", 
				stack[i].row, stack[i].col, 
				stack[i].row*MAX_COL+stack[i].col );
	}
	return;
}

struct point start = {0, 0};
//struct point target = {0, 0};
struct point target = {4, 4};

struct point predecessor[MAX_ROW][MAX_COL];

int visit( int newrow, int newcol, struct point pre )
{
	struct point tmp;

	/* set as recorded */
	maze[newrow][newcol] = 2;

	predecessor[newrow][newcol] = pre;

	/* push this point to record */
	tmp.row = newrow;
	tmp.col = newcol;
	push(tmp);

	return 1;
}

void print_predecessor(void)
{
	int i, j;
	int pre;


	printf( "pre info : \n" );
	for(i = 0; i < 5; i++)
	{
		for(j = 0; j < 5; j++)
		{
			pre = predecessor[i][j].row*MAX_COL+predecessor[i][j].col; 
			printf( "%2d->%2d\t", i*MAX_COL+j, (pre==0)? -1: pre );
		}

		printf( "\n" );
	}

	printf( "******************\n" );
	return;
}

void backtrack( struct point p )
{
	struct point tmp;
	struct point pre;
	struct point zero={0,0};

	tmp = get_top();
	pre = predecessor[tmp.row][tmp.col];

	while( !(p.row==pre.row && p.col==pre.col) )
	{
		tmp = predecessor[p.row][p.col];
		maze[p.row][p.col] = 0;
		predecessor[p.row][p.col] = zero;

		p = tmp;
		print_predecessor();
		print_maze();
	}
}

int main(void)
{
	struct point p;
	struct point pre;
	struct point tmp;
	int ret = 0;
	int ways = 0;

	printf( "hello, maze! \n" );
	print_maze();

	/* init start situation */ 
	p = start;
	maze[p.row][p.col] = 2;
	push(p);

	while( !is_empty() )
	{
		/* get the saved point from stack */
		p = pop();

		/* judge if p is target point */
		if( p.row == target.row && p.col == target.col )
		{
			printf( "target %d is found! \n", ++ways );
			print_stack();
			print_maze();
			getchar();
			do{
				printf("(%d,%d)%d \t", p.row, p.col, p.row*5+p.col );
				p = predecessor[p.row][p.col];
			}while( p.row != start.row || p.col != start.col );
			printf("(%d,%d)%d \t", p.row, p.col, p.row*5+p.col );
			backtrack( target );
//			break;
			continue;
		}

		ret = 0;
		/* expend p to UP, LEFT, DOWN, RIGHT */
		// look UP
		if( p.row-1 >= 0 && maze[p.row-1][p.col] == 0 )
			ret = visit( p.row-1, p.col, p );	

		// look LEFT 
		if( p.col-1 >= 0 && maze[p.row][p.col-1] == 0 )
			ret = visit( p.row, p.col-1, p );

		// look DOWN 
		if( p.row+1 < MAX_ROW && maze[p.row+1][p.col] == 0 )
			ret = visit( p.row+1, p.col, p );

		// look RIGHT 
		if( p.col+1 < MAX_COL && maze[p.row][p.col+1] == 0 )
			ret = visit( p.row, p.col+1, p );

		if( ret == 0 )
		{
			printf( "no visit \n" );
			print_stack();
			//getchar();
			backtrack( p );
		}

		print_maze();
		print_stack();
		print_predecessor();
	//	getchar();
	}

	printf( "there is %d ways out! \n", ways );

	return 0;
}
