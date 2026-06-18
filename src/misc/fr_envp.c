#include <mush.h>
#include <stddef.h>
#include <stdlib.h>

void fr_envp(char **envp) {
	for (size_t i = 0; envp[i] != NULL; i++) {
		free(envp[i]);
	}
	free(envp);
	return;
}
