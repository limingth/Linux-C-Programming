/*
 * five-chess.c  - five chess play demo program
 *
 * just for fun, take it easy!
 * 
 * author 0: Li Ming <limingth@akaedu.org>
 *
 *
 * 2010-3-31	version 0.1 released by limingth
 *
 */

#include <stdio.h>

/* define chessboard size */
#define ROW  8
#define COL  8

/* define how many chess win */
#define N  5

/* define chessboard using matrix */
int chessboard[ROW][COL];


/* display chessboard using printf */
void print_chessboard(void)
{
	int i, j;

	printf("\n");
	printf("  ");
	for (j = 0; j < COL; j++)
		printf(" %d", j);
	printf("\n");

	printf(" -");
	for (j = 0; j < COL; j++)
		printf(" -");
	printf("\n");

	for (i = 0; i < ROW; i++) 
	{
		printf("%d| ", i);
		for (j = 0; j < COL; j++) 
		{
			if (chessboard[i][j] == 0)
				printf("* ");
			else	
				printf("%d ", chessboard[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

/* get user input */
int get(int *x, int *y)
{
	scanf("%d %d", x, y);
	return 0;
}

/* put chess in chessboard(x, y) */
int put(int x, int y, int who)
{
	chessboard[x][y] = who;
	return 1;
}

/* check if (x, y) is empty */
int empty(int x, int y)
{
	if (chessboard[x][y] == 0)
		return 1;
	return 0;
}

/* test (x, y) is valid before put chess */
int test(int x, int y)
{
	if (x >= ROW || x < 0)
		return 0;
	if (y >= COL || y < 0)
		return 0;
	if (empty(x, y))
		return 1;
	return 0;
}

int check(int x, int y)
{
	int i = 0, j = 0;
	int counter = 1;
	int who;
	int nx, ny;		// next x y

	// right, down, right_down, left_down
	int dirx[4] = { 0, 1, 1, 1 };
	int diry[4] = { 1, 0, 1, -1 };

	// get the current person
	who = chessboard[x][y];
	if (who == 0)
		return 0;

	// 4 directions
	for (i = 0; i < 4; i++) 
	{
		nx = x;
		ny = y;
		counter = 1;
		for (j = 1; j < N; j++) 
		{
			nx += dirx[i];
			ny += diry[i];
			if (chessboard[nx][ny] == who)
				counter++;
		}
		if (counter == N) 
		{
			printf("check ok!  %d %d -> dir(%d) \n", x, y, i);
			return 1;
		}
	}
	return 0;
}

/* check if someone wins */
int find(void)
{
	int i, j;
	for (i = 0; i < ROW; i++) 
	{
		for (j = 0; j < COL; j++) 
		{
			if (check(i, j))
				return 1;
		}
	}
	return 0;
}


int main(int argc, char *argv[])
{
	int x, y;
	int step = 0;
	int who;
	printf("Hello, FIVE CHESS PLAYER!\nReady to go? GO!\n");

	print_chessboard();
	printf("you can input 4 4 to put a chess on board\n");

	while (1) 
	{
		who = step % 2 + 1;
		printf("player %d: ", who);
		get(&x, &y);

		if (test(x, y)) 
		{
			put(x, y, who);
			print_chessboard();
			step++;
			if (find()) 
			{
				printf("Congratulations, player %d win! \n", who);
				return 0;
			}
		}
		else
			printf("%d %d is not permitted! please reinput.\n\n", x, y);
	}
	return 0;
}
