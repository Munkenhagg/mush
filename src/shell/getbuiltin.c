#include <mush.h>
#include <stddef.h>
#include <string.h>

builtin_fn_t g_builtin(char *cmd) {
	for (int i = 0; builtins[i].name != NULL; i++) {
		if (strcmp(builtins[i].name,cmd) == 0) {
			return builtins[i].funct;
		}
	}
	return NULL;
}
