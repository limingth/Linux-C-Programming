
#include <stdio.h>

#define ROW 10
#define COL 10
#define WINPLATENUM 5 //连子个数


#define PLATE '*'
#define STEP 2
//#define FILLED 1  // 已下子
#define KILLED 'x' // 不能下子

#define PLAYERA 'A' // A玩家棋子flag
#define PLAYERB 'B' // B玩家棋子flag
#define EXITGAME 8


char playerA[ROW][COL]; // player a's chess plate
char playerB[ROW][COL]; // player b's chess plate

typedef struct
{
	int row;
	int col;
} POINT;
POINT stack[COL];
int g_top = 0;

int chess_authority[ROW][COL]; // every chess's authority

// direction:down,right,crossr,crossl
int direct[4][2] = 
{
	{0,1},{1,0},{1,1},{1,-1}
};

int IsWin( char chGamerFlag ); // 赢了吗？
int Start(void); // 游戏开始

int main(int argc, char *argv[])
{
	Start();
	return 0;
}

void Init( void )
{
	int i,j;
	for( i=0; i<ROW; i++ )
	{	for( j=0;j<COL;j++ )
		{
			playerA[i][j] = PLATE;
			playerB[i][j] = PLATE;
		}
	}	
}

void Draw( void )
{
	int i,j;
	for( i=0; i<ROW; i++ )
	{
		if( i==0 )
		{
			for( j=0; j<COL; j++ )
			{
				int iStep;
				for( iStep=0; iStep<STEP; iStep++ )
					printf( " ");
				printf( "%c", j+'0' );
			}
			printf( "\n");
		}
		printf( "%c ", i+'0' );

		for( j=0;j<COL;j++ )
		{
			int iStep;
			if( playerA[i][j] == KILLED )
				printf( "%c", playerB[i][j] );
			else if( playerB[i][j] == KILLED )
				printf( "%c", playerA[i][j] );
			else
				printf( "%c", PLATE );
			for( iStep=0; iStep<STEP; iStep++ )
				printf( " ");
		}
		printf( "\n" );
	}

}

int IsArrayFull(void)
{
	int i,j;

	for( i=0; i<ROW; i++ )
		for( j=0; j<COL; j++ )
			if( PLATE == playerA[i][j] ||  PLATE == playerB[i][j])
				return 0;
	return 1;
		
}

void clear_authority( void )
{
	int i,j;

	for( i=0; i<ROW; i++ )
		for( j=0; j>COL; j++ )
		{
			chess_authority[i][j] = 0;
		}
}

void put_authority(void) 
{
	int i,j;
	int nx,ny;
	int m,n;

	for( i=0; i<ROW; i++ )
		for( j=0; j<COL; j++ )
		{
			if( KILLED == playerB[i][j] )
			{
				nx = i - 1;
				ny = j - 1;
				if( nx>=0 && ny>=0 )
					if( PLATE == playerB[nx][ny] )
						chess_authority[nx][ny] += 1;

				nx = i + 1;
				ny = j;
				if( nx<ROW )
					if( PLATE == playerB[nx][ny] )
						chess_authority[nx][ny] += 1;
						
				nx = i - 1;
				ny = j;
				if( nx>=0 )
					if( PLATE == playerB[nx][ny] )
						chess_authority[nx][ny] += 1;

				nx = i;
				ny = j - 1;
				if( ny>=0 )
					if( PLATE == playerB[nx][ny] )
						chess_authority[nx][ny] += 1;

				nx = i + 1;
				ny = j + 1;
				if( ny<COL && nx<ROW )
					if( PLATE == playerB[nx][ny] )
						chess_authority[nx][ny] += 1;
						
				nx = i + 1;
				ny = j - 1;
				if( ny>=0 && nx<ROW )
					if( PLATE == playerB[nx][ny] )
						chess_authority[nx][ny] += 1;
				nx = i - 1;
				ny = j + 1;
				if( nx>=0 && ny <COL )
					if( PLATE == playerB[nx][ny] )
						chess_authority[nx][ny] += 1;
				nx = i;
				ny = j + 1;
				if( ny<COL )
					if( PLATE == playerB[nx][ny] )
						chess_authority[nx][ny] += 1;

			}
			
		}

}

int get_maxauth_chess( int *row, int *col )
{
	int i,j;
	int tmp = 0;

	for( i=0; i<ROW; i++ )
		for( j=0; j<COL; j++ )
		{
			if( tmp < chess_authority[i][j] )
			{
				tmp = chess_authority[i][j];
				*row = i;
				*col = j;
			}
		}

	return 0;
}


int push_endian( char chGamerFlag )
{
	int i,j;
	int m,n;
	int directx,directy;
	int chesscnt = 1;
	int chesscntb = 1;
	char (*parrayA)[COL] = NULL;
	char (*parrayB)[COL] = NULL;
	int nflag = 0;

	parrayA = playerA;
	parrayB = playerB;

	for( i=0; i<ROW; i++ )
		for( j=0; j<COL; j++ )
		{
			if(chGamerFlag != parrayA[i][j] )
				continue;

			// check five chess along four direction
			for( m=0; m<4; m++ )
			{
				directx = direct[m][0];
				directy = direct[m][1];
				for( n=0; n<WINPLATENUM; n++ )
				{
					if( i+directx<ROW && j+directy<COL )
					{
						if( PLAYERA == parrayA[i+directx][j+directy] )	
							chesscnt++;
					}
					// check playerb for win

					// win
					if( chesscnt >= (WINPLATENUM - 2) )
					{
						POINT point;
						point.row = i+chesscnt*direct[m][0];
						point.col = j+chesscnt*direct[m][1];
						if( point.row < ROW 
							&& point.col < COL 
							&& (PLATE == parrayA[point.row][point.col])
						  )
						{
							nflag = 0;
							stack[g_top++] = point;

							if( chesscnt == WINPLATENUM-1 )
								return 0;
							// test
							// printf( "push point(%d,%d)\n",point.row,point.col );
						}
						else
							nflag = -1;
						point.row = i - direct[m][0];
						point.col = j - direct[m][1];
						if( point.row >= 0 
							&& point.col >= 0 
							&& (PLATE == parrayA[point.row][point.col])
						  )
						{	stack[g_top++] = point;

							if( chesscnt == WINPLATENUM-1 )
								return 0;

							if( nflag == 0 && chesscnt == WINPLATENUM-2 )
								return 0;
							// test
							// printf( "push point(%d,%d)\n",point.row,point.col );
						}

					}

					directx += direct[m][0];
					directy += direct[m][1];
				}

				chesscnt = 1;
				chesscntb = 1;


			}
		}

	//not win
	return 0;
}

POINT pop_endian( void )
{
	POINT point = stack[--g_top];
	g_top = 0;
	return point; 
}

int IsWin( char chGamerFlag )
{
	int i,j;
	int m,n;
	int directx,directy;
	int chesscnt = 1;

	char (*parray)[COL] = NULL;

	if( PLAYERA == chGamerFlag )
		parray = playerA;
	else
		parray = playerB;

	for( i=0; i<ROW; i++ )
		for( j=0; j<COL; j++ )
		{
			if(chGamerFlag != parray[i][j] )
				continue;

			// check five chess along four direction
			for( m=0; m<4; m++ )
			{
				directx = direct[m][0];
				directy = direct[m][1];
				for( n=0; n<WINPLATENUM; n++ )
				{
					if( i+directx<ROW && j+directy<COL )
						if( chGamerFlag == parray[i+directx][j+directy] )	
							chesscnt++;
						else
							break; // go to next direction

					// win
					if( WINPLATENUM == chesscnt )
						return 1;

					directx += direct[m][0];
					directy += direct[m][1];
				}

				chesscnt = 1;

			}
		}

	//not win
	return 0;
}

void machine_chess( int *row, int *col )
{
	POINT point;

	push_endian( PLAYERA );
	if( 0 <= g_top-1 )
	{
		point = pop_endian();	
		printf( "pop point(%d,%d)\n",point.row,point.col );
		*row = point.row;
		*col = point.col;
		return;
	}
		
	clear_authority();
	put_authority();
	get_maxauth_chess( row,col );
}
void Play( void )
{
	int x,y; 
//	int i,j;
	char chGamerFlag;
	char (*pgamer)[COL] = NULL;
       
	printf( "Please select first player(A or B):\n");
	chGamerFlag = getchar();
	if( PLAYERA == chGamerFlag )
		chGamerFlag = PLAYERA;
	else
	{
		int randnum;
		srand(time(0));
		randnum = rand()%9;
		x = 3+randnum/3;
		y = 3+randnum/3;

		chGamerFlag = PLAYERB;
		
	}
	
	while( 1 )
	{

		if( PLAYERA == chGamerFlag )
		{
			printf( "\nPlease %c input (x,y):", chGamerFlag );
			scanf( "%d%d",&x,&y );
			if( x == EXITGAME )
				break;	
			if( x<0 || x>ROW)
				continue;   
			if( y<0 || y>COL)
				continue; 
		}
		else
		{
			machine_chess( &x,&y );
		}
		if( PLAYERA == chGamerFlag )
			pgamer = playerA;
		else
			pgamer = playerB;

		if( chGamerFlag == pgamer[x][y] || KILLED == pgamer[x][y] )
		{
			printf( "\nCan not place here!\n" );
			continue;
		}
		else
		{
			pgamer[x][y] = chGamerFlag;
			if( PLAYERA == chGamerFlag )
				playerB[x][y] = KILLED;
			else
				playerA[x][y] = KILLED;
			
			Draw();

			if( IsWin(chGamerFlag) )
			{	printf( "%c WIN!\n Game over!\n", chGamerFlag );
				return;
			}

			if( IsArrayFull() )
			{	printf( "Equal!\n Game over!\n" );
				return;
			}

			if( PLAYERA == chGamerFlag )
				chGamerFlag = PLAYERB;
			else
				chGamerFlag = PLAYERA;
		} // end else

	}// end while

}

int Start(void)
{
	Init();
	Draw();
	Play();		
}


