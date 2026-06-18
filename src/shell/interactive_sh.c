#include <mush.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

int iactive_shell(void) {
	while (interactive) {
		char cmdbuf[MAX_CMD_SZ];
		const char *PS1 = g_var("PS1");
		const char *PS2 = g_var("PS2");
		const char *PS3 = g_var("PS3");
		const char *PS4 = g_var("PS4");
		const char *path = g_var("PATH");
		if (PS1 == NULL) {
			PS1 = "mush $ ";
		}
		if (PS2 == NULL) {
			PS2 = "> ";
		}
		if (PS3 == NULL) {
			PS3 = "#? ";
		}
		if (PS4 == NULL) {
			PS4 = "+ ";
		}
		printf("%s", PS1);
		fflush(stdout);

		if (!fgets(cmdbuf, sizeof(cmdbuf), stdin)) {
			break;
		}
		if (cmdbuf[0] == '\0') {
			continue;
		}
		cmdbuf[strcspn(cmdbuf, "\n")] = 0;
		char *tokbuf[MAX_SINGLE_ARG_SZ];
		tokenize(cmdbuf, tokbuf);
		char *proc_cmdbuf = proc_path(path, tokbuf[0]);
		tokbuf[0] = proc_cmdbuf;
		#ifdef LIGHT_HISTORY
			log_hist(tokbuf[0]);
		#else
			log_hist(cmdbuf);
		#endif
		exec_cmd(tokbuf);
	}
	return 0;
}
