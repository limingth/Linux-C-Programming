#include <sys/time.h>
#include <sys/resource.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	struct rlimit cur;
	int ret = getrlimit(RLIMIT_NPROC, &cur);
	if (ret) {
		perror("getrlimit");
		exit(1);
	}
	cur.rlim_cur = 1000;
	ret = setrlimit(RLIMIT_NPROC, &cur);
	if (ret) {
		perror("getrlimit");
		exit(1);
	}

	ret = getrlimit(RLIMIT_NPROC, &cur);
	if (ret) {
		perror("getrlimit");
		exit(1);
	}
	printf("soft limit:%d\n", cur.rlim_cur);
	return 0;
}

