#include <mush.h>
#include <user_config.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

int log_hist(char *untok_logbuf) {
	const char *home = g_var("HOME");
	char hist_path[MAX_PATH_SZ];
	snprintf(hist_path, sizeof(hist_path), "%s/%s", home, HISTORY_F);
	FILE *HIST_F = fopen(hist_path, "a");
	if (HIST_F == NULL) {
		perror(hist_path);
		return 1;
	}
	fprintf(HIST_F, "%s\n", untok_logbuf);
	#ifdef ALWAYS_ECHO_COMMANDS
		printf("%s\n", untok_logbuf);
	#endif
	fclose(HIST_F);
	return 0;
}
