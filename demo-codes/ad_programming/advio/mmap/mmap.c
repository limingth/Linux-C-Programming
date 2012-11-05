#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return -1;
	int fd, ret;
	int size;
	struct stat buf;
	char * ptr = NULL;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	fstat(fd, &buf);

	size = buf.st_size ;
	
	ptr = (char *)mmap(NULL, size+1, PROT_READ, 
		MAP_PRIVATE , 
			fd, 0);
	if (((void *)(-1)) == ptr) {
		perror("mmap");
		close(fd);
		exit(1);
	}	

	ptr[size] = '\0';

	printf("%s\n", ptr);

	munmap(ptr, size+1);

	close(fd);

	exit(0);
}
