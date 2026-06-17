#include <mush.h>
#include <user_config.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

void exit_iact_sh(int exit_num) {
	fflush(NULL);
	free(user);
	printf("\n%s (signal %d)\n", MUSH_EXIT_MSG, exit_num);
	_exit(exit_num);
}
