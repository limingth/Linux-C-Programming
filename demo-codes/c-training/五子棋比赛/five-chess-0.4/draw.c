#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fb.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <math.h>

void fb_pixel(unsigned short *fbmem,int w,
		int x,int y,int color)
{
	unsigned short *pos;
	pos  = fbmem + y*w + x;
	*pos = color;
}

void fb_hline(unsigned short *fbmem,int w,
		int x1,int y,int x2,int color)
{
	int i;
	for (i = x1; i < x2; i++)
		fb_pixel(fbmem,w,i,y,color);
}

void fb_vline(unsigned short *fbmem,int w,
		int x,int y1,int y2,int color)
{
	int i;
	for (i = y1; i < y2; i++)
		fb_pixel(fbmem,w,x,i,color);
}

/*======================rgb====================================*/
unsigned short rgb24_to16(unsigned char r,unsigned char g,unsigned char b)
{
	int r16,g16,b16;
	unsigned short rgb16;

	b16 = (b * 0x1f) / 0xff ;
	g16 = (g * 0x3f) / 0xff ;
	r16 = (r * 0x1f) / 0xff ;
	
	
	rgb16 = (r16<<11)|(g16<<5)|(b16);
	
	return rgb16;
}

void set_bgscreen (unsigned short *fbmem,int w,int h)
{
	unsigned short pixel,i,j;
	pixel = rgb24_to16(189,121,50);
	for (j = 0; j < h;j++)
		fb_hline(fbmem,w,0,j,w-1,pixel);
	
	for (i = 1 ; i < 20;i++)
	{	
		fb_hline (fbmem,w,100,30*i,670,0x3E0);
		fb_hline (fbmem,w,100,30*i+1,670,0xCCCC);
	}
	for (i = 0 ; i < 20;i++)
	{	
		fb_vline (fbmem,w,100 + 30*i,30,571,0x3E0);
		fb_vline (fbmem,w,101 + 30*i,30,571,0xCCCC);
	}
}

void draw_round(unsigned short * fbmem,int w,int x, int y,int ir,int color)
{
    int ixo, iyo, ix1, ix2, iy1, iy2, ix;
    int y1;

    ixo = x;
    iyo = y;
    iy1 = iyo - ir;
    iy2 = iyo + ir;
    for(y1=iy1; y1<=iy2; y1++)
    {
        ix = ( pow(ir, 2) - pow(y1-iyo, 2) ) / 2;
        ix = (int)sqrt( pow(ir, 2) - pow(y1-iyo, 2) );
        ix1 = ixo - ix;
        ix2 = ixo + ix;

	fb_hline (fbmem,w,ix1,y1,ix2,color);
    }
}

int fd;
unsigned short * fbmem;
int w,h,bpp;

int draw(int x, int y, int who)
{
	int posx, posy;

	posx = 100 + 30 * y;
	posy = 30 + 30 * x;

	if (who == 1)
	{
		draw_round(fbmem,w, posx, posy, 13,0xCCCC);
		draw_round(fbmem,w, posx, posy, 12,0x0);
	}	
	else
	{
		draw_round(fbmem,w, posx, posy, 13,0x0);
		draw_round(fbmem,w, posx, posy, 12,0xFFFF);
	}

	return 0;
}

	
int draw_init(void)
{
	struct fb_var_screeninfo fb_var;

	//1.) open fb
	fd = open ("/dev/fb0",O_RDWR);
	if (fd <0)
	{
		printf ("open /dev/fb0 error!\n");
		return -1;
	}
	//2. get framebuffer information
	ioctl(fd,FBIOGET_VSCREENINFO, &fb_var);
	
	w   = fb_var.xres;
	h   = fb_var.yres;
	bpp = fb_var.bits_per_pixel;

	//3. mmap framebuffer;
	fbmem = mmap (0,w * h * bpp/8,PROT_READ|PROT_WRITE,
			MAP_SHARED,fd,0);
	
	if(fbmem <0)
	{
		printf ("mmap fb error!\n");
		return 0;
	}

	return 0;
}

/* define chessboard size */
#define ROW  10
#define COL  10

int draw_board( int board[10][10] )
{
	int i, j;
	//4. draw pixel
	fb_pixel (fbmem,w,100,200,0xF800);
	fb_hline (fbmem,w,10,100,200,0x07E0);
	
	set_bgscreen (fbmem,w,h);

	for (i = 0; i < ROW; i++)
	{
		for (j = 0; j < COL; j++)
			/* if this pos is not empty */
			if (board[i][j])
				draw( i, j, board[i][j] );
	}

	return 0;
}



