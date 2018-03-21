#include <stdio.h>
#include <sys/time.h>
#include "rtnice.h"

#define SECOND 1000000000L

int main() {
	int ret = 0;
	float s = 0;

	printf("Enter number of seconds to give as rtnice to the parent process: ");
	scanf("%f", &s);

	ret = rtnice(getpid(), (long) (s * SECOND));

	if (ret == -1) {
		printf("Error: rtnice() returned -1.\n");
		return -1;
	}

	struct timeval start, stop;
	gettimeofday(&start, NULL);

	int pid = fork();

	if (pid == -1) {
		printf("Error: fork() returned -1.\n");
		return -1;
	}
	else if (pid == 0) {
		long i = 0;

		while (i++ < 1000000000);

		gettimeofday(&stop, NULL);

		printf("Time taken by child: %fs.\n", (stop.tv_sec - start.tv_sec) + ((stop.tv_usec - start.tv_usec) / 1000000.0));
	}
	else if (pid > 0) {
		long i = 0;

		while (i++ < 1000000000);

		gettimeofday(&stop, NULL);

		printf("Time taken by parent: %fs.\n", (stop.tv_sec - start.tv_sec) + ((stop.tv_usec - start.tv_usec) / 1000000.0));

		wait(NULL);
	}

	return 0;
}
