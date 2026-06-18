#include <mush.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int exec_cmd(char **cmd) {
	if (cmd == NULL || cmd[0] == NULL) {
		printf("exec_cmd: No command, this shouldnt happen on a stable version\nIf this is a stable version and this still happend, please report it on github issues\n");
		return 1;
	}
	builtin_fn_t fun = g_builtin(cmd[0]);
	if (fun != NULL) {
		return fun((void *)cmd);
	}
	const char *path = g_var("PATH");
	char *tmp_cmd = strdup(cmd[0]);
	char *target = proc_path(path, tmp_cmd);
	free(tmp_cmd);
	pid_t pid = fork();
	if (pid == 0) {
		char **envp = vars2envp(global_vars, var_c);
		execve(cmd[0], cmd, envp);
		perror("exec_cmd: execve");
		fr_envp(envp);
		_exit(1);
	}
	waitpid(pid, NULL, 0);
	free(target);
	return 0;
}
