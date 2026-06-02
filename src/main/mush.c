#include <mush.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int var_c = 0;
int func_c = 0;
int alias_c = 0;

Alias global_aliases[MAX_G_ALIASES];
Var global_vars[MAX_G_VARS];
Function functions[MAX_FUNCTIONS];

int main(int argc, char *argv[]) {
	printf("running\n");
	if (argc < 2) {
		// iactive_shell();
		printf("Starting interactive shell");
	}
	if (strcmp(argv[1], "-c") == 0) {
		// exec_cmd(argv[2]);
		printf("executing %s", argv[2]);
	}
	return 0;
}
