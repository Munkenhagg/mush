#include <mush.h>
#include <unistd.h>
#include <stdio.h>

int chdir(const char *path) {
	if (chdir(path)) {
		return 0;
	} else {
		perror("cd: ");
		return 1;
	}
	return 0;
}
