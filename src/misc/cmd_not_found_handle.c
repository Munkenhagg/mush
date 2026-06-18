#include <mush.h>
#include <stdio.h>
#include <stddef.h>

void cmd_not_found_handle(const char *cmd, const cmd_reason_t reason) {
	switch(reason) {
		case CMD_N_F: {
			printf("mush: %s: command not found\n", cmd);
			break;
		}
		case CMD_N_EXE: {
			printf("mush: %s: command found but not executable\n", cmd);
			break;
		}
		default: {
			printf("mush: %s: command not found (unknown)\n", cmd);
			break;
		}
	}
	return;
}
