#include <mush.h>
#include <stdio.h>

void mush_pwd(void) {
	printf("%s\n", g_var("PWD"));
}
