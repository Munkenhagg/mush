#include <mush.h>
#include <user_config.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

void exit_iact_sh(int exit_num) {
	fflush(NULL);
	free(user);
	printf("%s (signal %d)", MUSH_EXIT_MSG, exit_num);
	exit(exit_num);
}
