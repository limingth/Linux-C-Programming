#include "main.h"

int draw_block(u32_t * p, int offset_x, int offset_y, int color)
{
	int i, j;

	for (j = 0; j < WIDTH; j++)
	{
		for (i = 0; i < HIGH; i++)
		{
			fb_pixel(p, i+offset_x, j+offset_y, color);
		}
	}

	return 0;
}

