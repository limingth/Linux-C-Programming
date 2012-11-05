/*
 * five-chess.c  - five chess play demo program
 *
 * just for fun, take it easy!
 * 
 * author 0: Li Ming <limingth@akaedu.org>
 *
 *
 * 2010-4-21	version 0.1 released by Liming/Linan
 *
 */

#include <stdio.h>

/* define chessboard size */
#define ROW 10 
#define COL 10 

/* define how many chess win */
#define N  5

/* define chessboard using matrix */
int chessboard[ROW][COL] = {{0}, {0}};

/*define think using matrix*/
int score[ROW][COL] = {{0}, {0}};

/*fefine max point*/
struct max{
	int row;
	int col;
}maxpoint[ROW*COL] = {{0,0}};

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
		printf(" --");
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

/*think the score board*/
void print_score(void)
{
	printf("Player 2 thinking .... \n");
	int i, j;

	printf("\n");
	printf("  ");
	for (j = 0; j < COL; j++)
		printf(" %d", j);
	printf("\n");

	printf(" -");
	for (j = 0; j < COL; j++)
		printf(" --");
	printf("\n");

	for (i = 0; i < ROW; i++) {
		printf("%d| ", i);
		for (j = 0; j < COL; j++) {
			printf("%d ", score[i][j]);
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

int maxab(int a, int b)
{
	return a > b ? a : b;
}

void think_a_point(int x, int y, int who)
{
	int i = 0, j = 0;
	int counter[4] = {0};
	int flagdir[8] = {0};
	int dirok = 0, maxtmp;
	int max = 0;
	int nx, ny;		

	int dirx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
	int diry[8] = {1, 1, 0, -1, -1, -1, 0, 1};

	// 8 directions
	for (i = 0; i < 8; i++) 
	{
		nx = x;
		ny = y;
		for (j = 1; j < N; j++) 
		{
			nx += dirx[i];
			ny += diry[i];
			if (nx>=0 && nx<ROW && ny>=0 && ny<COL && 
				(chessboard[nx][ny] == who)) 

				counter[i%4]++;
			else if (nx>=0 && nx<ROW && ny>=0 && ny<COL && 
					 (chessboard[nx][ny]) == 0 )
			{
				flagdir[i] = 1;
				break;
			}
			else
				break;
		}
	}	

	for (i=0; i<4; i++)
	{
		if (max < counter[i])
			max = counter[i];
	}

	if (who == 1)
			score[x][y] = maxab(2 * max -1, score[x][y]);

	if (who == 2)
			score[x][y] = maxab(2 * max, score[x][y]);

	maxtmp = score[x][y];

	for(i=0; i<4; i++)
	{
		if (counter[i]==max && (flagdir[i]==1 || flagdir[i+4]==1))
			break;

		if (i==3)
			dirok = 1;

		if (counter[i]==max && flagdir[i]==0 && flagdir[i+4] ==0 && max<4)
			maxtmp = 0;
	}

	if (dirok==1 && maxtmp==0)
		score[x][y] = 0;

	
	if (chessboard[x][y] != 0)
		score[x][y] = 0;
}

void think(void)
{
	int i, j;
	for (i = 0; i < ROW; i++) 
	{
		for (j = 0; j < COL; j++) 
		{
			think_a_point(i, j, 1);
			think_a_point(i, j, 2);
		}
	}
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

int getmax(void)
{
	int i, j, k = 0;
	int a = 0;
	for (i=0; i<ROW*COL; i++)
	{
		maxpoint[i].row = 0;
		maxpoint[i].col = 0;
	}
	for (i=0; i<ROW; i++)
	{
		for (j=0; j<COL; j++)
		{
			if(score[i][j] >= a)
			{
				if (chessboard[i][j] == 0)
				{
					a = score[i][j];
					maxpoint[k].row = i;
					maxpoint[k].col = j;
					k++;
				}
			}
		}
	}
	return k/2;
}

void autoget(int *x, int *y)
{
	think();
	print_score();
	*x = maxpoint[getmax()].row;
	*y = maxpoint[getmax()].col;
	printf("Player 2 : %d %d\n", *x, *y);
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
	int iffirst;
	int step = 0;
	int who;
	printf("Hello, FIVE CHESS PLAYER!\nReady to go? GO!\n");
	printf("Input 1 to go first, other to go second:\n");
	scanf("%d", &iffirst);

	if (iffirst!=1)
		chessboard[ROW/2 -1][ROW/2 -1] = 2;

	print_chessboard();
	printf("you can input n n to put a chess on board\n");

	while (1) 
	{
		who = step % 2 + 1;
		printf("player %d: ", who);
		if (who == 1)
			get(&x, &y);
		else
			autoget(&x, &y);
		

		if (test(x, y)) 
		{
			put(x, y, who);
			print_chessboard();
			step++;
			if (find()) 
			{
				if (who == 1)
					printf("Congratulations, You win! \n");
				else
					printf("You lose!...\n");
				return 0;
			}
		}
		else
			printf("%d %d is not permitted! please reinput.\n\n", x, y);
	}
	return 0;
}
