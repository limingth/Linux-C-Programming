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
#define ROW 10 
#define COL 10 

/* define how many chess win */
#define N  5

/* define chessboard using matrix */
int chessboard[ROW][COL];
int thinkboard[ROW][COL];
int peopleboard[ROW][COL];


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

	for (i = 0; i < ROW; i++) {
		printf("%d| ", i);
		for (j = 0; j < COL; j++) {
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


void readboard_c(void)
{
	int i;
	int j;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
		{
			if (chessboard[i][j] == 1)
				thinkboard[i][j] = -1;
			if (chessboard[i][j] == 2)
				thinkboard[i][j] = 1;
			if (chessboard[i][j] == 0)
				thinkboard[i][j] = 0;
		}
#if 0
	printf("computer readboard:\n");
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
			printf("%2d", thinkboard[i][j]);
		printf("\n");
	}
#endif
}

void readboard_p(void)
{
	int i;
	int j;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
		{
			if (chessboard[i][j] == 2)
				peopleboard[i][j] = -1;
			if (chessboard[i][j] == 1)
				peopleboard[i][j] = 1;
			if (chessboard[i][j] == 0)
				peopleboard[i][j] = 0;
		}
	
#if 0
	printf("people readboard:\n");
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
			printf("%2d", peopleboard[i][j]);
		printf("\n");
	}
#endif
}


int max_count(int count[])
{
	int i;
	int maxi = 0; 
	for (i = 0; i < 8; i++)
		if (count[i] > count[maxi])
			maxi = i;

	return count[maxi];
}

int cal(int i, int j, int a[ROW][COL])
{
	int count[8];
	a[i][j] = 1;
	for (count[0] = 1; ((a[i][j] == a[i][j+1]) && (i>=0) && (i<ROW) && (j>=0) && (j<COL)); count[0]++, j++) ;
	for (count[1] = 1; ((a[i][j] == a[i][j-1]) && (i>=0) && (i<ROW) && (j>=0) && (j<COL)); count[1]++, j--) ;
	for (count[2] = 1; ((a[i][j] == a[i+1][j]) && (i>=0) && (i<ROW) && (j>=0) && (j<COL)); count[2]++, i++) ;
	for (count[3] = 1; ((a[i][j] == a[i-1][j]) && (i>=1) && (i<ROW) && (j>=0) && (j<COL)); count[3]++, i--) ;
	for (count[4] = 1; ((a[i][j] == a[i+1][j+1]) && (i>=0) && (i<ROW) && (j>=0) && (j<COL)); count[4]++, i++, j++) ;
	for (count[5] = 1; ((a[i][j] == a[i+1][j-1]) && (i>=0) && (i<ROW) && (j>=1) && (j<COL)); count[5]++, i++, j--) ;
	for (count[6] = 1; ((a[i][j] == a[i-1][j+1]) && (i>=1) && (i<ROW) && (j>=0) && (j<COL)); count[6]++, i--, j++) ;
	for (count[7] = 1; ((a[i][j] == a[i-1][j-1]) && (i>=1) && (i<ROW) && (j>=1) && (j<COL)); count[7]++, i--, j--) ;
//	a[i][j] = 0;

	return max_count(count);
}

void count_think_board(void)
{
	int i; 
	int j;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			if (thinkboard[i][j] == 0)
				thinkboard[i][j] = cal(i, j, thinkboard);
#if 0
	printf("compute board:\n");
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
			printf("%2d", thinkboard[i][j]);
		printf("\n");
	}
#endif
}

void count_people_board(void)
{
	int i;
	int j;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			if (peopleboard[i][j] == 0)
				peopleboard[i][j] = cal(i, j, peopleboard);

#if 0
	printf("people board:\n");
	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
			printf("%2d", peopleboard[i][j]);
		printf("\n");
	}
#endif
}

void max_board(int *max, int *x, int *y, int a[ROW][COL])
{
	int i, j;
	int maxi = 0;
	int maxj = 0;
	for (i = 0; i < ROW; i++)
		for(j = 0; j < COL; j++)
			if (a[maxi][maxj] < a[i][j])
			{
				maxi = i;
				maxj = j;
			}
	*x = maxi;
	*y = maxj;
	*max = a[maxi][maxj];
}

void think(int *x, int *y)
{
	int cx, cy;
	int px, py;
	int maxc, maxp;

	readboard_c();
	readboard_p();

	count_think_board();
	count_people_board();

	max_board(&maxc, &cx, &cy, thinkboard);
	max_board(&maxp, &px, &py, peopleboard);


	if (maxc >= maxp)
	{
		*x = cx;
		*y = cy;
	}
	else
	{
		*x = px;
		*y = py;
	}
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
		if (who == 1)
			get(&x, &y);
		else
			think(&x, &y);

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
