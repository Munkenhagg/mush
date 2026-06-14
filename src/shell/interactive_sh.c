#include <mush.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int iactive_shell() {
	int mode;
	char cmdbuf[MAX_CMD_SZ];
	while (interactive) {
		char *PS1 = g_var("PS1");
		if (PS1 == NULL) {
			PS1 = "mush $ ";
		}
		printf("%s", PS1);
		fflush(stdout);

		if (!fgets(cmdbuf, sizeof(cmdbuf), stdin)) {
			break;
		}
		cmdbuf[strcspn(cmdbuf, "\n")] = 0;
		printf("%s\n", cmdbuf);
	}
	return 0;
}
