#include "../comm.h"

int writeFileToSharedMemory(const char * path)
{
	int fd, ret, shmid, semid, offset = 0;
	char buf[100];
	struct stat filestat;
	
	ret = stat(path, &filestat);

	shmid = shm_init(filestat.st_size);
	fd = open(path, O_RDONLY);
	semid = sem_init();

	p(semid);
	while (1) {
		ret = read(fd, buf, 100);
		if (ret == 0)
			break;
		if (ret > 0) {
			write_shm(buf, offset, ret);
			offset += ret;
		}	
	}
	v(semid);
	return 0;
}

int main(void)
{
	char buf[100];
	int ret;

	while (1) {
		printf("Waiting input file: ");
		fflush(stdout);
		ret = read(0, buf, 100);
		if (ret > 0) {
			writeFileToSharedMemory(buf);
		}
	}
}
