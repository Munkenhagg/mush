#include <mush.h>
#include <stddef.h>
#include <stdio.h>

int exec_cmd(char **cmd) {
	if (cmd == NULL || cmd[0] == NULL) {
		printf("exec_cmd: No command, this shouldnt happen on a stable version\nIf this is a stable version and this still happend, please report it on github issues\n");
		return 1;
	}
	builtin_fn_t fun = g_builtin(cmd[0]);
	if (fun != NULL) {
		return fun((void *)cmd);
	}
	return 0;
}
