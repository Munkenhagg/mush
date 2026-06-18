#include <mush.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char **vars2envp(Var *vars, size_t count) {
	char **envp = malloc((count + 1) * sizeof(char*));
	for (size_t i = 0; i < count; i++) {
		size_t len = strlen(vars[i].name) + strlen(vars[i].val) + 2;
		envp[i] = malloc(len);
		snprintf(envp[i], len, "%s=%s", vars[i].name, vars[i].val);
	}
	envp[count] = NULL;
	return envp;
}
