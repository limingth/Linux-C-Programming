#include <stdio.h>

int maze[5][5] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

void print_maze(void)
{
	int i, j;

	for( i = 0; i < 5; i++ )
	{
		for( j = 0; j < 5; j++ )
			printf( "%d ", maze[i][j] );
		printf("\n");
	}

	printf("--------------------\n");
	return;
}

struct point
{
	int row;
	int col;
};

typedef struct point Point;

struct footprint
{
	Point pos;
	int direction;
} stack[512];

static int top = 0;
void push(struct point p, int direction)
{
	stack[top].pos = p;
	stack[top].direction = direction;
	top++;
}

struct footprint pop(void)
{
	top--;
	return stack[top];
}

void print_stack(void)
{
	int i;
	for( i = 0; i < top; i++ )
	{
		printf( "(%d, %d)_%d \n", stack[i].pos.row, stack[i].pos.col, stack[i].direction );
	}
	printf( "************\n" );
}

Point start = { 0, 0 };
Point target = { 4, 4 };

#define MAX_COL  5
#define MAX_ROW  5

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

int check( Point pos, int direction )
{
	switch( direction )
	{
		case UP:
			if( pos.row == 0 )
				return 0;
			if( maze[pos.row-1][pos.col] > 0 )
				return 0;
			return UP;
		case DOWN:
			if( pos.row == MAX_ROW-1 )
				return 0;
			if( maze[pos.row+1][pos.col] > 0 )
				return 0;
			return DOWN;
		case LEFT:
			if( pos.col == 0 )
				return 0;
			if( maze[pos.row][pos.col-1] > 0 )
				return 0;
			return LEFT;
		case RIGHT:
			if( pos.col == MAX_COL-1 )
				return 0;
			if( maze[pos.row][pos.col+1] > 0 )
				return 0;
			return RIGHT; 
	}

	return;
}

Point get_point( Point pos, int direction )
{
	Point ret;

	ret = pos;

	switch( direction )
	{
		case UP:
			ret.row = ret.row - 1;
			break;
		case DOWN:
			ret.row = ret.row + 1;
			break;
		case LEFT:
			ret.col = ret.col - 1;
			break;
		case RIGHT:
			ret.col = ret.col + 1;
			break;
	}

	return ret;
}

int is_target( Point pos)
{
	if( pos.row == target.row )
		if( pos.col == target.col )
			return 1;

	return 0;
}

int main(void)
{
	// define fist start point position
	struct footprint current;

	print_maze();

	current.pos = start;
	current.direction = 0;

	while(1)
	{
		/* judge if it is target */
		if( is_target(current.pos) )
		{	
			printf("find a way !\n");
			print_maze();
			print_stack();
			getchar();

			current = pop();
			continue;
		}

		// set as visited: 2 
		maze[current.pos.row][current.pos.col] = 2;

		// get next mothed
		current.direction++;
		
		// back trace
		if( current.direction > RIGHT )
		{
			// set as not visited: 0 
			maze[current.pos.row][current.pos.col] = 0;
			current = pop();
			continue;
		}

		if( check(current.pos, current.direction) )
		{
			push( current.pos, current.direction );
			current.pos = get_point( current.pos, current.direction );
			current.direction = 0;
		}
	}

	print_maze();
	print_stack();
	return 0;
}
