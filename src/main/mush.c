#include <mush.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char *builtins[MAX_BUILTINS_SZ];

int var_c = 0;
int func_c = 0;
int alias_c = 0;
bool interactive = true;

Alias global_aliases[MAX_G_ALIASES];
Var global_vars[MAX_G_VARS];
Function functions[MAX_FUNCTIONS];

int main(int argc, char *argv[]) {
	printf("running\n");
	if (argc < 2) {
		puts("Starting interactive shell");
		setup_default_environment();
		iactive_shell();
		return 0;
	}
	if (strcmp(argv[1], "-c") == 0) {
		if (argc >= 3) {
			printf("executing %s\n", argv[2]);
			// exec_cmd(argv[2]);
		} else {
			puts("No command for -c");
			return 1;
		}
	}
	return 0;
}
