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
#include <stdlib.h>

/* define chessboard size */
#define ROW  10
#define COL  10

/* define how many chess win */
#define N  5

/* define chessboard using matrix */
int chessboard[ROW][COL] = { {0} };

/*define tow table: computer table, person table*/
int comboard[ROW][COL] = { {0} };
int perboard[ROW][COL] = { {0} };

/*consider @***@*/
int keyc = 0;
int keyp = 0;

int check(int x, int y, int board[ROW][COL], int who);
int update(int x, int y);
int surch(int x, int y);

/* clear board */
void clear(int board[ROW][COL])
{
	int i, j;
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			board[i][j] = 0;
}

/* display chessboard using printf */
void print(int board[ROW][COL])
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
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int get_max(int *x, int *y, int board[ROW][COL], int *max, int who)
{
	int i, j, k = 0;
	int cur;
	int t = 0;
	int key = 1;
	int counter = 0;
	int a[ROW][COL] = { {0} };
#define	X 0
#define	Y 1
	int MAX[ROW * COL][2] = { {0} };

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			cur = board[i][j];

			if (cur > *max) {
				*max = cur;
				*x = i;
				*y = j;
			}
			if (cur == *max)
				a[i][j] = *max;
		}
	}
	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++)
			if (a[i][j] == *max) {
				MAX[k][X] = i;
				MAX[k][Y] = j;
				counter++;
				k++;
			}
	if (counter >= 2) {
		for (i = 1; i < k; i++)
			if (MAX[t][X] == MAX[i][X]) {
				*x = MAX[t][X];
				*y = MAX[t][Y];
				key = 0;
				break;
			} else
				t = i;
		if (key) {
			for (i = 1; i < k; i++)
				if (MAX[t][Y] == MAX[i][Y]) {
					*x = MAX[t][X];
					*y = MAX[t][Y];
					key = 0;
					break;
				} else
					t = i;
		}
		if (key) {
			for (i = 1; i < k; i++)
				if (abs(MAX[i][X] - MAX[i][X]) ==
				    abs(MAX[i][Y] - MAX[i][Y])) {
					*x = MAX[t][X];
					*y = MAX[t][Y];
					if (who == 1)
						keyp = 1;
					if (who == 2)
						keyc = 1;
					key = 0;
					break;
				} else
					t = i;
		}
	}

	return 0;
}

/* get the max valuable position */
int get_max_think(int *x, int *y)
{
	int cx;
	int cy;
	int px;
	int py;
	int maxc = 0, maxp = 0;
	get_max(&px, &py, perboard, &maxp, 1);
	get_max(&cx, &cy, comboard, &maxc, 2);
	if (maxc == 0) {
		*x = px;
		*y = py;
	} else {
		if ((maxp == 3 && maxc == 3) && !keyc && keyp) {
			*x = px;
			*y = py;
			keyp = 0;
		}
		keyc = 0;
		keyp = 0;
		if (maxp >= 2 && maxc < maxp) {
			*x = px;
			*y = py;
		} else {
			*x = cx;
			*y = cy;
		}
	}

	return 0;
}

/* get user input */
int get(int *x, int *y)
{
	scanf("%d %d", x, y);
	return 0;
}

/* machine think a good place */
int think(int *x, int *y)
{
	int i, j;

//      clear(comboard);

	for (i = 0; i < ROW; i++)
		for (j = 0; j < COL; j++) {
			check(i, j, comboard, 2);
			check(i, j, perboard, 1);
		}

	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++)
			/* if this pos is not empty */
			if (chessboard[i][j] != 0) {
				comboard[i][j] = 0;
				perboard[i][j] = 0;
			}
	}
	printf("Computer's think board: \n");
	print(comboard);
	printf("Person's think board: \n");
	print(perboard);

	/* get the max value position (x,y) */
	get_max_think(x, y);

	printf("Computer's think pos is (%d, %d): ", *x, *y);

	getchar();

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

int check(int x, int y, int board[ROW][COL], int who)
{
	int i = 0, j = 0;
	int counter = 1;
	int nx, ny;		// next x y
	int nxb, nyb;		//back x y

	// right, down, right_down, left_down
	int dirx[4] = { 0, 1, 1, 1 };
	int diry[4] = { 1, 0, 1, -1 };

	// get the current person
	if (chessboard[x][y] != who)
		return 0;

	// 4 directions
	for (i = 0; i < 4; i++) {
		nx = x;
		ny = y;
		nxb = x;
		nyb = y;
		counter = 1;
		for (j = 1; j < N; j++) {
			nx += dirx[i];
			ny += diry[i];
			if (chessboard[nx][ny] == who)
				counter++;
			else
				break;

		}
		if (chessboard[nx][ny] == 0)
			if (board[nx][ny] < counter)
				board[nx][ny] = counter;
		if (nxb && nyb) {
			nxb -= dirx[i];
			nyb -= diry[i];
		}
		if ((nxb >= 0) && (nyb >= 0))
			if (chessboard[nxb][nyb] == 0)
				if (board[nxb][nyb] < counter)
					board[nxb][nyb] = counter;
	}

	return 0;
}

/* check if someone wins */
int find(void)
{
	int i, j;
	for (i = 0; i < ROW; i++) {
		for (j = 0; j < COL; j++) {
			if (surch(i, j))
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

	print(chessboard);
	printf("you can input 3 5 put a chess on board\n");
	int flag = 1;

	while (1) {
		who = step % 2 + 1;
		printf("player %d: ", who);
		if (who == 2) {
			get(&x, &y);
		} else {
			if (flag == 1) {
				x = 4;
				y = 4;
				flag = 0;
			} else
				think(&x, &y);
		}

		if (test(x, y)) {
			put(x, y, who);
			print(chessboard);
			step++;
			if (find()) {
				printf("Congratulations, player %d win! \n",
				       who);
				return 0;
			}
		} else
			printf("%d %d is not permitted! please reinput.\n\n", x,
			       y);
	}
	return 0;
}
int surch(int x, int y)
{
	int i = 0, j = 0;
	int counter = 1;
	int nx, ny;		// next x y
	int who;

	// right, down, right_down, left_down
	int dirx[4] = { 0, 1, 1, 1 };
	int diry[4] = { 1, 0, 1, -1 };
	who = chessboard[x][y];
	// get the current person
	if (who == 0)
		return 0;

	// 4 directions
	for (i = 0; i < 4; i++) {
		nx = x;
		ny = y;
		counter = 1;
		for (j = 1; j < N; j++) {
			nx += dirx[i];
			ny += diry[i];
			if (nx < ROW && ny < COL && ny >= 0) {
				if (chessboard[nx][ny] == who)
					counter++;
				else
					break;
			}
		}
		if (counter == N) {
			printf("surch ok!  %d %d -> dir(%d) \n", x, y, i);
			return 1;
		}
	}

	return 0;
}
