#ifndef	_MAIN_H_
#define _MAIN_H_

typedef unsigned int u32_t;
typedef unsigned char u8_t;

#define SCREEN_W 1024
#define SCREEN_H 768
#define SCREEN_BPP 32
#define M 100
#define N 100

#define WIDTH 25
#define HIGH 25
#define BOX 20


#define true         1
#define false         0
//#define BoardWidth   25 
//#define BoardHeight   25

#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define WIGHT 0xFFFFFF
#define YELLOW 0xFFFF00
#define PINE 0xFF00FF
#define DARK 0x00FFFF
#define BLACK	0x000000

/* ********************** fb.c ********************* */
extern u32_t * init_fb(const char *filename);
extern int fb_pixel(u32_t *p, int x, int y, u32_t color);

/* ******************** rand.c ********************* */
extern int my_rand();

/* ******************* draw_block.c **************** */
extern int draw_node(u32_t * p, int offset_x, int offset_y, int color);
extern int erase_node(u32_t * p, int offset_x, int offset_y, int color);
#if 0
extern void GenerateBlock(Block * block);
extern int RotateCells (int c[4][4], int blockSize);
extern int CanRotate();
extern int CanMove(int dx, int dy);
extern void DrawBlock(u32_t * p, Block * block, int bdLeft, int bdTop);
extern int RotateBlock(u32_t * p, Block * block);
extern void EraseBlock(u32_t * p, Block * block, int bdLeft, int bdTop);
extern int MoveBlock(u32_t *p, Block *block, int dx, int dy);
extern void CheckBoard();
#endif
#endif
