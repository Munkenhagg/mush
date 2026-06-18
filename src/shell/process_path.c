#include <mush.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

char *proc_path(const char *path, const char *cmd) {
	char **arr_path = calloc(MAX_SHELL_PATHS, sizeof(char *));
	int curarrnum = 0;
	char *target = malloc(MAX_PATH_SZ + 1);
	if (!target) {
		printf("proc_path: malloc failed!");
		#ifdef STRICT_MODE
			printf("Exiting due to strict mode. Reason should be above\n");
			exit_iact_sh(1);
		#endif
	}
	size_t path_len = strlen(path);
	for (size_t i = 0; i < path_len; i++) {
		if (path[i] == ':') {
			curarrnum++;
			continue;
		}
		char stri[2] = {path[i], '\0'};
		char *append = NULL;
		if (arr_path[curarrnum] != NULL) {
			append = strjoin(arr_path[curarrnum], strdup(stri));
		} else {
			append = strdup(stri);
		}
		arr_path[curarrnum] = append;
	}
	struct stat st;
	for (int i = 0; arr_path[i] != NULL; i++) {
		snprintf(target, MAX_PATH_SZ, "%s/%s", arr_path[i], cmd);
		if (stat(target, &st) == 0 && S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR)) {
			free(arr_path);
			return target;
		}
	}
	free(arr_path);
	cmd_not_found_handle(cmd, CMD_N_F);
	return NULL;
}
