#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <errno.h>

int rtnice(int pid, long val) {
	long ret = syscall(323, pid, val);

	if (ret < 0) {
		if (errno == 3) {
			printf("Error: Process with pid %d not found.\n", pid);
			return -1;
		}
		if (errno == 22) {
			printf("Error: Invalid argument for val: %ld.\n", val);
			return -1;
		}
	}

	return 0;
}
