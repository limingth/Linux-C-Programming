#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "main.h"
#define SPEED 2
/* the data structure of the block */
typedef struct	animal 
{
	int x[M];			/* block position cx [ 0,BoardWidht -1] */
	int y[N];			/* block position cy [-4,BoardHeight-1] */
	int head_color;		/* block color */
	int body_color;
	int node;
} Animal;

Animal snake;
typedef struct tagboard
{
	int In_Color;
	int Wall_Color;
	int left;
	int top;
	int B[WIDTH][HIGH];
}BBoard;

BBoard Board;
typedef struct tagfood
{
	int color;
	int x;
	int y;
}Food;

Food food;

int Generate_snake(u32_t *p, Animal *s);
int Erase_snake(u32_t *p, Animal *s);
int MoveSnake(u32_t *p, Animal *s, int dx, int dy);
int PaintBoard(u32_t *p);
int draw_food(u32_t *p, int offset_x, int offset_y, int color);
int Move(Animal *s);
int PutFood(u32_t *p, BBoard *b, Food *f);
int BodyLong(Food *f, BBoard *b, Animal *s);
int Is_Over(BBoard *b, Animal *s, int x, int y);

int draw_food(u32_t *p, int offset_x, int offset_y, int color)
{
	int i,j;
	for(j = 0; j < BOX; j++)
	{
		for(i = 0; i < BOX; i++)
		{
			fb_pixel(p, i + offset_x, j + offset_y, color);	
		}
	}
	
	return 0;
}
int Generate_snake(u32_t *p, Animal *s)
{
	int i;
	int color;

	for(i = 0; i < s->node; i++)
	{
		if(i == 0){color = s->head_color;Board.B[s->x[i]][s->y[i]] = 1;}
		else{color = s->body_color;Board.B[s->x[i]][s->y[i]] = 2;}

		draw_node(p, Board.left + s->x[i] * BOX, Board.top + s->y[i] 
			   * BOX, color);
	}

	return 0;
}

int Erase_snake(u32_t *p, Animal *s)
{	
	int i;

	for(i = 0; i < s->node; i++)
	{
		draw_node(p, Board.left + s->x[i] * BOX, Board.top + s->y[i] 
			   * BOX, Board.In_Color);
		Board.B[s->x[i]][s->y[i]] = 0;
	}

	return 0;

}

int Move(Animal *s)
{
	int i;
	for(i = s->node - 1; i > 0; i--)
	{
		s->x[i] = s->x[i - 1];
		s->y[i] = s->y[i - 1];
	}

	return 0;
}

int MoveSnake(u32_t *p, Animal *s, int dx, int dy)
{

	if(!Is_Over(&Board, s, dx, dy))
	{
		if(dx == 0&&dy == 0)	
		{
			Generate_snake(p, s);
		}
		else
		{
			Erase_snake(p, s);

			if((s->x[0] + dx) != s->x[1] || (s->y[0] + dy) != s->y[1])
			{
				Move(s);
				s->x[0] += dx;
				s->y[0] += dy;
			}
			else
			{
				Move(s);
				s->x[0] -= dx;
				s->y[0] -= dy;
			}

			Generate_snake(p, s);
		}
	}
	else
	{
	printf("Game Over!\n");
	system("stty cooked echo");
	exit(0);}
	
	return 0;
}
int PaintBoard(u32_t *p)
{
	int i,j;
	for(i = 0; i < WIDTH; i++)
	{
		for(j = 0; j < HIGH; j++)
		{
			if(i > 0 && j > 0 && i < WIDTH - 1 && j < HIGH - 1)
			{
				if(Board.B[i][j] == 0){		
				draw_node(p, Board.left + i * BOX, Board.top + j * BOX, Board.In_Color);}
				if(Board.B[i][j] == 1){
				draw_node(p, Board.left + i * BOX, Board.top + j * BOX, snake.head_color);}
				if(Board.B[i][j] == 2){
				draw_node(p, Board.left + i * BOX, Board.top + j * BOX, snake.body_color);}
				if(Board.B[i][j] == 3){
				draw_node(p, Board.left + i * BOX, Board.top + j * BOX, food.color);}

			}
			else{
				draw_node(p, Board.left + i * BOX, Board.top + j * BOX, Board.Wall_Color);
				Board.B[i][j] = 1;
			}
		}
	}

	return 0;
}
int PutFood(u32_t *p, BBoard *b, Food *f)
{

	do{	
		f->x = my_rand();
		f->y = my_rand();

	  }while(b->B[f->x][f->y] != 0);

	 draw_food(p, b->left + f->x * BOX, b->top + f->y * BOX, f->color);
	b->B[f->x][f->y] = 3;

	 return 0;

}
#if 1
int BodyLong(Food *f, BBoard *b, Animal *s)
{
	int k,t;
	k = s->node - 1;
	t = s->node - 2;

	if(b->B[f->x][f->y] == 1)
	{
		if(s->y[k]== s->y[t])
			{
				if(b->B[s->x[k]+1][s->y[k]] == 0)
				{/*	draw_node(p, b->left + s->x[k] * BOX,
						  b->top + s->y[k] * BOX + BOX,
						  GREEN);*/
					s->x[k + 1] = s->x[k] + 1;}
				//	b->B[s->x[k] + 1][s->y[k]] = 2;}

				else
				{/*draw_node(p, b->left + s->x[k] * BOX,
						  b->top + s->y[k] * BOX - BOX,
						  GREEN);*/
					s->x[k + 1] = s->x[k] - 1;}
				//	b->B[s->x[k] - 1][s->y[k]] = 2;}
							
				s->node++;
			}
		if(s->x[k] == s->x[t]) 
		{
			if(b->B[s->x[k]][s->y[k] + 1] == 0)
			{/*draw_node(p, b->left + s->x[k] * BOX + BOX,
				  b->top + s->y[k] * BOX,
				  GREEN);*/
				s->y[k + 1] = s->y[k] + 1;}
			//	b->B[s->x[k]][s->y[k] + 1] = 2;}
			else
			{/*draw_node(p, b->left + s->x[k] * BOX - BOX,
				  b->top + s->y[k] * BOX,
				  GREEN);*/

				s->y[k + 1] = s->y[k] - 1;}
			//	b->B[s->x[k]][s->y[k] - 1] = 2;}	
			s->node++;
		}
			
	}

	return 0;
}
#endif
int Is_Over(BBoard *b, Animal *s, int x, int y)
{
	int q;
	q = b->B[s->x[0] + x][s->y[0] + y];

	if( q == 1 || q == 2)	
	{
		if((x == 0 && y != 0)||(x != 0 && y == 0))
		{
			return 1;
		}
		return 0;
	}

	return 0;
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
	int dic_x = 0;
	int dic_y = 0;
	int i;
	int j;
	int count = 0;
	u32_t *p;
	if ((p = init_fb (NULL)) == NULL)
	  {
		  printf ("Error init_fb\n");
		  return 0;
	  }

	Board.B[WIDTH][HIGH] = 0;
	Board.left = 55;
	Board.top = 55;
	Board.In_Color = BLACK;
	Board.Wall_Color = DARK; 
	food.color = YELLOW;
	food.x = 1;
	food.y = 1;
	snake.head_color = RED;
	snake.body_color = GREEN;
	PaintBoard(p);
#if 1
	snake.node = 3;
	for(i = 0; i < snake.node; i++)
	{
		snake.x[i] = (WIDTH/2 - 1)+ i;
		snake.y[i] = HIGH/2;
	}

	system("stty raw -echo");
	printf("enter 'q' to quit: \n\r");

	while (c != 'q')
	{		
		usleep(SPEED*100000);
		if (kbhit())
			c = getchar();

		switch(c)
		{
		case 'a':
			MoveSnake(p, &snake, -1, 0);
			dic_x = -1;
			dic_y = 0;
			break;
		case 's':
			MoveSnake(p, &snake,  0, 1);
			dic_x = 0;
			dic_y = 1;	 
			break;
		case 'd':
			MoveSnake(p, &snake, 1, 0);
			dic_x = 1;
			dic_y = 0;
			break;
		case 'w':
			MoveSnake(p, &snake, 0, -1);
			dic_x = 0;
			dic_y = -1;
			break;
		case 'q':
		//	system("stty cooked echo"); /* main function end  */
		//	return 0;
			goto end;
		default:
			MoveSnake(p, &snake, dic_x, dic_y);
			break;
		}
				
		c = ' ';
		if(Board.B[food.x][food.y] == 1 || count == 0){
			BodyLong(&food, &Board, &snake);
			PutFood(p, &Board, &food);}
		count = 1;
		PaintBoard(p);
	}
end:
	system("stty cooked echo"); /* main function end  */
#endif
	for(i = 0; i < WIDTH; i++)
	{
		for(j = 0; j < HIGH; j++)
		{
			printf("%d", Board.B[j][i]);
		}
		printf("\n");
	}

	return 0;
}
