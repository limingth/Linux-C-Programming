#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

typedef unsigned int u32_t;
typedef unsigned char u8_t;

#define SCREEN_W 1024
#define SCREEN_H 768
#define SCREEN_BPP 32

/* return NULL: Error */
u32_t * init_fb(const char *filename)
{
	if (filename == NULL)
		filename = "/dev/fb0";

	/* step 1: open file*/
	int fd;
	if ((fd = open(filename, O_RDWR)) < 0)
	{
		perror("Error open for fb");
		return NULL;		
	}

	//printf("open success : %d\n", fd);

	/* step 2: mmap file to memory */
	u32_t *p;
	p = mmap(NULL, SCREEN_W * SCREEN_H * SCREEN_BPP/8, PROT_READ|PROT_WRITE,
		 MAP_SHARED, fd, 0);

	if (p == MAP_FAILED)
	{
		perror("Error mmap");
		return NULL;
	}

	//printf("mmap success\n");

	/* step 3: close */
	close(fd);

	return p;
}

int fb_pixel(u32_t *p, int x, int y, u32_t color)
{
	*(p + y*SCREEN_W + x) = color;	

	return 0;
}
