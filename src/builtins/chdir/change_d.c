#include <mush.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int mush_chdir(const char *path) {
	if (chdir(path)) {
		s_var("PWD", strdup(path));
		return 0;
	} else {
		perror("chdir: ");
		return 1;
	}
	return 0;
}
