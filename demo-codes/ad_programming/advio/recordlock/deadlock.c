#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int lock_file(int fd, int cmd, short type, 
	off_t offset, short whence, off_t len)
{
	struct flock lock;

	lock.l_type = type;
	lock.l_whence = whence;
	lock.l_start = offset;
	lock.l_len = len;

	return fcntl(fd, cmd, &lock);
}	
int main(void)
{
	int fd, ret;
	pid_t pid;

	fd = open("passwd", O_RDWR);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	pid = fork();

	if (pid == -1) {
		perror("fork");
		close(fd);
		exit(1);
	}

	if (pid == 0) {
		ret = lock_file(fd, F_SETLKW, F_WRLCK, 0, 
			SEEK_SET, 5);
		if (ret == -1) {
			printf("child lock A fail!\n");
			exit(1);
		}

		sleep(5);
		ret = lock_file(fd, F_SETLKW, F_WRLCK, 5, 
			SEEK_SET, 5);
		if (ret == -1) {
			printf("child lock B fail!\n");
			exit(1);
		}

		exit(0);
	}

	if (pid > 0) {
		usleep(1000);
		ret = lock_file(fd, F_SETLKW, F_WRLCK, 5, 
			SEEK_SET, 5);
		if (ret == -1) {
			printf("father lock B fail!\n");
			exit(1);
		}

		sleep(3);
		ret = lock_file(fd, F_SETLKW, F_WRLCK, 0, 
			SEEK_SET, 5);
		if (ret == -1) {
			printf("father lock A fail!\n");
			exit(1);
		}

	}

}
