#include <mush.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stddef.h>

int iactive_shell(void) {
	char cmdbuf[MAX_CMD_SZ];
	while (interactive) {
		const char *PS1 = g_var("PS1");
		const char *PS2 = g_var("PS2");
		const char *PS3 = g_var("PS3");
		const char *PS4 = g_var("PS4");
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
		cmdbuf[strcspn(cmdbuf, "\n")] = 0;
		char *tokbuf[512];
		tokenize(cmdbuf, tokbuf);
		log_hist(cmdbuf);
		exec_cmd(tokbuf);
	}
	return 0;
}
