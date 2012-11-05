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
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 5;

		ret = fcntl(fd, F_GETLK, &lock);
		if (ret == -1) {
			perror("fcntl");
			exit(1);
		}
		
		if (lock.l_type == F_UNLCK) {
			ret = lock_file(fd, F_SETLK, 
				F_WRLCK,
				0, SEEK_SET, 5);
			if (ret == -1) {
				printf("pid=%d" 
					"lock file fail!",
					getpid());
				exit(1);	
			}
		} else {
			if (lock.l_type == F_RDLCK) {
				printf("old readlock!\n");
			} else if (lock.l_type == 
				F_WRLCK) {
				printf("old writelock!\n");
			}
			exit(0);
		}
		printf("lock sucess!\n");
		lseek(fd, 0, SEEK_SET);
		write(fd, "hello", 5);
		close(fd);
		exit(0);
	}

	if (pid > 0) {
	#if 0
		ret = lock_file(fd, F_SETLKW, F_RDLCK,
			0, SEEK_SET, 5);
		if (ret == -1) {
			printf("pid=%d lock file fail!",
				getpid());
			exit(1);	
		}
#endif
		char buf[5];
		lseek(fd, 0, SEEK_SET);

		int cnt = read(fd, buf, 5);
		if (cnt == -1) {
			perror("read");
			exit(1);
		}

	#if 0
		ret = lock_file(fd, F_SETLK, F_UNLCK, 0,
			SEEK_SET, 5);
		if (ret == -1) {
			printf("unlock fail!\n");
			exit(1);
		}	
	#endif
		write(1, buf, cnt);
		write(1, "\n", 1);
		sleep(5);
		close(fd);
		exit(0);
	}

}
