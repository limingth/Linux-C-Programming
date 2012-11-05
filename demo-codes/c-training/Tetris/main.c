#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "main.h"

#define true         1
#define false         0
#define BoardWidth    15
#define BoardHeight     25

#define RED	0x00FF0000
#define GREEN	0x0000FF00
#define BLUE	0x000000FF
#define YELLOW	0x0000FFFF
#define LIGHTGRAY	0x00FF00FF
#define LIGHTBLUE	0x00FFFF00
#define CYAN	0x00FFFFFF
#define BOARD_COLOR	0x00000000

/* the data structure of the block */
typedef struct tagBlock
{
	int c[4][4];		/* cell fill info array, 0-empty, 1-filled */
	int x;			/* block position cx [ 0,BoardWidht -1] */
	int y;			/* block position cy [-4,BoardHeight-1] */
	int color;		/* block color */
	int size;		/* block max size in width or height */
	char name;		/* block name (the block's shape) */
} Block;

/* our board, Board[x][y][0]-isFilled, Board[x][y][1]-fillColor */
unsigned int Board[BoardWidth][BoardHeight][2];
int BufferCells[4][4];		/* used to judge if can rotate block */
Block curBlock;			/* current moving block */

int BoardLeft = 0;
int BoardTop = 0;

int zero[4][4];

void GenerateBlock(Block * block);
int RotateCells (int c[4][4], int blockSize);
int CanRotate();
int CanMove(int dx, int dy);
void DrawBlock(u32_t * p, Block * block, int bdLeft, int bdTop);
int RotateBlock(u32_t * p, Block * block);
void EraseBlock(u32_t * p, Block * block, int bdLeft, int bdTop);
int MoveBlock(u32_t *p, Block *block, int dx, int dy);
void CheckBoard();

/*
void print(unsigned int b[10][20][2])
{
	int i, j;
	for (j = 0; j < 20; j++)
	{
		for (i = 0; i < 10; i++)
		{
			printf("%2d", b[i][j][0]);
		}
		printf("\n");
	}
}
*/

void my_copy(int dest[4][4], int src[4][4])
{
	int i,j;
	for( i = 0; i < 4; i++)
	{
		for( j = 0; j < 4; j++)
		{
			dest[i][j] = src[i][j];	
		}
	}
}

/* create a new block by key number,
* the block anchor to the top-left corner of 4*4 cells
*/
void GenerateBlock(Block * block)
{
	int key = my_rand(7);
	block -> size = 3;	/* because most blocks' size=3 */
	//memset(block -> c, 0, 16);
	switch (key)
	  {
	  case 0:
		  block -> name = 'T';
		  block -> color = RED;
		  block -> c[1][0] = 1;
		  block -> c[1][1] = 1;
		  block -> c[2][1] = 1;
		  block -> c[1][2] = 1;
		  break;
	  case 1:
		  block -> name = 'L';
		  block -> color = YELLOW;
		  block -> c[1][0] = 1;
		  block -> c[1][1] = 1;
		  block -> c[1][2] = 1;
		  block -> c[2][2] = 1;
		  break;
	  case 2:
		  block -> name = 'J';
		  block -> color = LIGHTGRAY;
		  block -> c[1][0] = 1;
		  block -> c[1][1] = 1;
		  block -> c[1][2] = 1;
		  block -> c[0][2] = 1;
		  break;
	  case 3:
		  block -> name = 'z';
		  block -> color = CYAN;
		  block -> c[0][0] = 1;
		  block -> c[1][0] = 1;
		  block -> c[1][1] = 1;
		  block -> c[2][1] = 1;
		  break;
	  case 4:
		  block -> name = '5';
		  block -> color = LIGHTBLUE;
		  block -> c[1][0] = 1;
		  block -> c[2][0] = 1;
		  block -> c[0][1] = 1;
		  block -> c[1][1] = 1;
		  break;
	  case 5:
		  block -> name = 'o';
		  block -> color = BLUE;
		  block -> size = 2;
		  block -> c[0][0] = 1;
		  block -> c[1][0] = 1;
		  block -> c[0][1] = 1;
		  block -> c[1][1] = 1;
		  break;
	  case 6:
		  block -> name = 'I';
		  block -> color = GREEN;
		  block -> size = 4;
		  block -> c[0][1] = 1;
		  block -> c[1][1] = 1;
		  block -> c[2][1] = 1;
		  block -> c[3][1] = 1;
		  break;
	  }
}

/* rotate the block, update the block struct data */
int RotateCells(int c[4][4], int blockSize)
{
	int temp;
	switch (blockSize)
	{
	  case 3:
		  temp = c[0][0];
		  c[0][0] = c[2][0];
		  c[2][0] = c[2][2];
		  c[2][2] = c[0][2];
		  c[0][2] = temp;
		  temp = c[0][1];
		  c[0][1] = c[1][0];
		  c[1][0] = c[2][1];
		  c[2][1] = c[1][2];
		  c[1][2] = temp;
		  break;
	  case 4:		/* only 'I' block arived here! */
		  c[1][0] = 1 - c[1][0];
		  c[1][2] = 1 - c[1][2];
		  c[1][3] = 1 - c[1][3];
		  c[0][1] = 1 - c[0][1];
		  c[2][1] = 1 - c[2][1];
		  c[3][1] = 1 - c[3][1];
		  break;
	}

	return 1;
}

/* judge if the block can rotate */
int CanRotate()
{
	int i, j, tempX, tempY;
	/* update buffer */
	//memcpy(BufferCells, curBlock.c, 16);
	my_copy(BufferCells, curBlock.c);
	RotateCells(BufferCells, curBlock.size);
	for (i = 0; i < curBlock.size; i++)
	{
		  for (j = 0; j < curBlock.size; j++)
		    {
			    if (BufferCells[i][j])
			      {
				      tempX = curBlock.x + j;
				      tempY = curBlock.y + i;
				      if (tempX < 0 || tempX > (BoardWidth - 1))
					      return false;
				      if (tempY > (BoardHeight - 1))
					      return false;
				      if (tempY >= 0 && Board[tempX][tempY][0])
					      return false;
			      }
		    }
	}

	return true;
}

/* draw the block */
void DrawBlock(u32_t * p, Block * block, int bdLeft, int bdTop)
{
	int i, j;
	for (i = 0; i < block->size; i++)
	  {
		  for (j = 0; j < block->size; j++)
		    {
			    if (block->c[i][j] && (block->y + j) >= 0)
			      {
				      draw_block(p, bdLeft + (block->x + j) * WIDTH, bdTop + (block->y + i) * HIGH, block->color);
			      }
		    }
	  }
}

/* Rotate the block, if success, return true */
int RotateBlock(u32_t * p, Block * block)
{
	int b_success = 1;
	if (curBlock.size == 2)
		return b_success;
	if ((b_success = CanRotate()))
	{
		  EraseBlock(p, block, BoardLeft, BoardTop);
		  //memcpy(curBlock.c, BufferCells, 16);
		  my_copy(curBlock.c, BufferCells);
		  DrawBlock(p, block, BoardLeft, BoardTop);
	}
	return b_success;
}

/* erase a block, only fill the filled cell with background color */
void EraseBlock(u32_t * p, Block * block, int bdLeft, int bdTop)
{
	int i, j;
	for (i = 0; i < block->size; i++)
	  {
		  for (j = 0; j < block->size; j++)
		    {
			    if (block->c[i][j] && (block->y + j >= 0))
			      {
				      draw_block(p, bdLeft + (block->x + j) * WIDTH, bdTop + (block->y + i) * HIGH, BOARD_COLOR);
			      }
		    }
	  }
}

/* judge if the block can move toward the direction */
int CanMove(int dx, int dy)
{
	int i, j, tempX, tempY;
	for (i = 0; i < curBlock.size; i++)
	  {
		  for (j = 0; j < curBlock.size; j++)
		    {
			    if (curBlock.c[i][j])
			      {
				      /* cannot move leftward or rightward */
				      tempX = curBlock.x + j + dx;
				      if (tempX < 0 || tempX > (BoardWidth - 1))
					      return false;	/* make sure x is valid! */
				      /* cannot move downward */
				      tempY = curBlock.y + i + dy;
				      if (tempY > (BoardHeight - 1))
					      return false;	/* y is only checked lower bound, maybe negative!!!! */
				      /* the cell already filled, we must check Y's upper bound before check cell ! */
				      if (tempY >= 0 && Board[tempX][tempY][0])
					      return false;
			      }
		    }
	  }
	return true;
}

/* move by the direction if can, donothing if cannot
* return value: true - success, false - cannot move toward this direction
*/
int MoveBlock(u32_t *p, Block *block, int dx, int dy)
{
    int b_canmove = CanMove(dx,dy);
    if (b_canmove)
    {
        EraseBlock(p, block, BoardLeft, BoardTop);
        curBlock.x += dx;
        curBlock.y += dy;
        DrawBlock(p, block, BoardLeft, BoardTop);
    }
    return b_canmove;
}

/* set the isFilled and fillcolor data to the board */
void FillBoardData()
{
    int i, j;
    for (i = 0; i < curBlock.size; i++)
    {
        for (j = 0; j < curBlock.size; j++)
        {
            if (curBlock.c[i][j] && (curBlock.y+j) >= 0)
            {
                Board[curBlock.x+j][curBlock.y+i][0] = 1;
                Board[curBlock.x+j][curBlock.y+i][1] = curBlock.color;
            }
        }
    }
}

/* check if one line if filled full and increase the totalScore! */
void CheckBoard()
{
    int i, j, k, sum = 0, topy, lines=0;

    /* we find the top empty line! */
    j = topy = BoardHeight - 1;
    do
    {
        sum = 0;
        for (i = 0; i < BoardWidth; i++)
        {
            sum += Board[i][topy][0];
        }
        topy--;
    } while(sum > 0 && topy > 0);


    /* remove the full filled line (max remove lines count = 4) */
    do
    {
        sum = 0;
        for (i = 0; i < BoardWidth; i++)
            sum += Board[i][j][0];

        if(sum == BoardWidth)/* we find this line is full filled, remove it! */
        {
            /* move the cells data down one line */
            for (k = j; k > topy; k--)
            {
                for (i = 0; i < BoardWidth; i++)
                {
                    Board[i][k][0] = Board[i][k-1][0];
                    Board[i][k][1] = Board[i][k-1][1];
                }
            }
            /*make the top line empty! */
            for (i = 0; i < BoardWidth; i++)
            {
                Board[i][topy][0] = 0;
                Board[i][topy][1] = BOARD_COLOR;
            }
            topy++;        /* move the topline downward one line! */
				lines++;    /* lines <= 4 */
				usleep(200000);
        }
        else
            j--;
    } while (sum > 0 && j > topy && lines < 4);
}

/* draw the board */
void PaintBoard(u32_t *p)
{
    int i, j, fillcolor;
    for (i = 0; i < BoardWidth; i++)
    {
        for(j = 0; j < BoardHeight; j++)
        {
            fillcolor = Board[i][j][0] ? Board[i][j][1] : BOARD_COLOR;
            draw_block(p, i * WIDTH + BoardLeft, j * HIGH + BoardTop, fillcolor);
        }
    }
}


int kbhit(void)
{
	int i;
	ioctl(0, FIONREAD, &i);
	return i;
}

int main(int argc, char *argv[])
{
	int c = ' ';

	u32_t *p;
	if ((p = init_fb (NULL)) == NULL)
	  {
		  printf ("Error init_fb\n");
		  return 0;
	  }

	GenerateBlock(&curBlock);

	curBlock.x = 0;
	curBlock.y = 0;

	PaintBoard(p);

	system("stty raw -echo");  /* main function start */
	printf("enter 'q' to quit: \n\r");

	while (c != 'q')
	{		
		usleep(300000);

		if (kbhit())
			c = getchar();

		switch(c)
		{
		case 'a':
			MoveBlock(p, &curBlock, -1, 0);
			break;
		case 's':
			MoveBlock(p, &curBlock, 0, 2);
			break;
		case 'd':
			MoveBlock(p, &curBlock, 1, 0);
			break;
		case 'w':
			RotateBlock(p, &curBlock);
			break;
		case 'q':
			system("stty cooked echo"); /* main function end  */
			return 0;
		default:
			MoveBlock(p, &curBlock, 0, 1);
			break;
		}

		c = ' ';		

		if (!CanMove(0, 1))
		{
			FillBoardData();
			CheckBoard();
			PaintBoard(p);

			my_copy(curBlock.c, zero);
			GenerateBlock(&curBlock);
			curBlock.x = 0;
			curBlock.y = 0;
		}		
	}

	system("stty cooked echo"); /* main function end  */

	return 0;
}
