
#include <stdio.h>

struct point {
	int row;
	int col;
};

/* define point stack */
struct point stack[512];

/* define stack pointer */
int top = 0;

/* define push() */
void push(struct point node)
{
	stack[top++] = node;
	return;
}

/* define pop() */
struct point pop(void)
{
	return stack[--top]; 
}

/* define isempty() */
int isempty(void)
{
	return (top == 0);
}

int maze[5][5] =
{
	{ 0, 0, 0, 0, 0 },
	{ 1, 1, 1, 1, 0 },
	{ 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 1, 0 }
};

struct point father[5][5] =
{
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} }, 
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} }, 
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} }, 
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} }, 
	{{-1,-1}, {-1,-1}, {-1,-1}, {-1,-1}, {-1,-1} }, 
};

void print_stack(void)
{
	int i;

	for (i = top-1; i >= 0; i--)
		printf("(%d, %d) \n", stack[i].row, stack[i].col);

	printf("------------------------\n");

	return;
}

void print_maze(void)
{
	int i, j;

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}

	printf("------------------------\n");
	return;
}

void print_father(void)
{
	int i, j;
	struct point node;

	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			node = father[i][j];
			printf("(%2d,%2d) ", node.row, node.col);
		}
		printf("\n");
	}

	printf("------------------------\n");
	return;
}

struct point entry = {0, 0};
struct point out = {4, 4};

void backtrack(struct point p)
{
	/* define tmp node = curr point */
	struct point node = p;
	struct point null = {-1, -1};
	struct point top, topfather;
	int row, col;

#ifdef DEBUG
	printf("backtrack is begin \n");
	print_stack();
	getchar();
#endif

	/* peak stack top */
	top = pop();
	push(top);

	/* get top father */
	topfather = father[top.row][top.col];

	while(1)
	{
		/* get curr node's row & col */
		row = node.row;
		col = node.col;

		/* clear maze[][] = 0 */
		maze[row][col] = 0;

		/* get current node's father */
		node = father[row][col];

		/* clear father[][] = (-1,-1) */
		father[row][col] = null;
#ifdef DEBUG
		print_maze();
		print_father();
		getchar();
#endif

		/* end condition */
		/* peak stack top point -> topfather */
		/* if node == topfather, break */
		if (node.row == topfather.row && node.col == topfather.col)
			break;
	}

//	printf("backtrack is over \n");
}

void print_solution(void)
{
	/* define tmp node = exit point */
	struct point node = out;
	int row, col;
	static int counter = 0;

	while(1)
	{
		/* print curr node */
		printf("(%d, %d) <- ", node.row, node.col);
		row = node.row;
		col = node.col;

		/* get current node's father */
		node = father[row][col];

		/* if current node is (-1,-1), then break */
		if (node.row == -1)
			break;
	}

	printf("\n");	
	printf("%d solution is over \n", ++counter);	

	return;
}

int main(void)
{
	//struct point entry = {2, 2};
	struct point curr;
	struct point node;
	int flag = 0;

	printf("hello, mazer!\n");

	/* init stack, push entry point */
	push(entry);

#ifdef DEBUG
	print_stack();
	print_maze();	
	print_father();	
#endif

	while (!isempty())
	{
		/* get the stack top */
		curr = pop();
		
		/* flag curr point */
		maze[curr.row][curr.col] = 2;

		/* check it */
	//	print_stack();
	//	print_maze();

		/* judgement if curr is exit point */
		if (curr.row == out.row && curr.col == out.col)
		{
			printf("one solution found! \n");
			print_solution();

			/* begin to backtrack */
			backtrack(curr);
		//	break;
			continue;
		}

		/* expand from curr */
		flag = 0;

		/* look left */
		if (curr.col-1 >= 0 && maze[curr.row][curr.col-1] == 0)
		{
			/* push left point */
			node.row = curr.row;
			node.col = curr.col - 1;
			/* node 's father is null */
			if (father[node.row][node.col].row == -1)
			{	
				push(node);
				/* remember father */
				father[node.row][node.col] = curr;
				flag++;
			}
		}

		/* look up */
		if (curr.row-1 >= 0 && maze[curr.row-1][curr.col] == 0)
		{
			/* push up point */
			node.row = curr.row - 1;
			node.col = curr.col;
			if (father[node.row][node.col].row == -1)
			{	
				push(node);
				/* remember father */
				father[node.row][node.col] = curr;
				flag++;
			}
		}

		/* look right */
		if (curr.col+1 < 5 && maze[curr.row][curr.col+1] == 0)
		{
			/* push right point */
			node.row = curr.row;
			node.col = curr.col + 1;
			if (father[node.row][node.col].row == -1)
			{	
				push(node);
				/* remember father */
				father[node.row][node.col] = curr;
				flag++;
			}
		}

		/* look down */
		if (curr.row+1 < 5 && maze[curr.row+1][curr.col] == 0)
		{
			/* push down point */
			node.row = curr.row + 1;
			node.col = curr.col;
			if (father[node.row][node.col].row == -1)
			{	
				push(node);
				/* remember father */
				father[node.row][node.col] = curr;
				flag++;
			}
		}
#ifdef DEBUG
		print_stack();
		print_father();
		getchar();
#endif

		/* if no way out (curr node has no expand node) */
		if (flag == 0)
			backtrack(curr);
	}

	printf("maze is over \n");
//	print_stack();
	
	return 0;
}
