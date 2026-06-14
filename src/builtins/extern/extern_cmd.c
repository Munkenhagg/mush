#include <mush.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int extern_cmd(char *cmd[]) {
	if (cmd == NULL) {
		printf("No command specified");
		return 1;
	}
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		return 1;
	}
	if (pid == 0) {
		execvp(cmd[0], cmd);
		perror(cmd[0]);
		exit(1);
	}
	int stus;
	waitpid(pid, &stus, 0);
	return WEXITSTATUS(stus);

}
