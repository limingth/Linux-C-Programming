#ifndef	_MAIN_H_
#define _MAIN_H_

typedef unsigned int u32_t;
typedef unsigned char u8_t;

#define SCREEN_W 1024
#define SCREEN_H 768
#define SCREEN_BPP 8

#define WIDTH 20
#define HIGH 20

/* ********************** fb.c ********************* */
extern u32_t * init_fb(const char *filename);
extern int fb_pixel(u32_t *p, int x, int y, u32_t color);

/* ******************** rand.c ********************* */
extern int my_rand(int bound);

/* ******************* draw_block.c **************** */
extern int draw_block(u32_t * p, int offset_x, int offset_y, int color);

#endif
