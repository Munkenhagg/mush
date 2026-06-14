#include <mush.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void setalias(const char* keyw, const char *eq) {
	for (int i=0;i<alias_c;i++) {
		if (strcmp(global_aliases[i].keyw,keyw) == 0) {
			strncpy(global_aliases[i].eq,eq,MAX_VAR_VAL_SZ);
			return;
		} else {
			printf("Could not edit alias (%s)", keyw);
			return;
		}
	}
	if (alias_c < MAX_G_ALIASES) {
		strncpy(global_aliases[alias_c].keyw,keyw,MAX_VAR_NAME_SZ);
		strncpy(global_aliases[alias_c].eq,eq,MAX_VAR_VAL_SZ);
		alias_c++;
	} else {
		printf("Max aliases hit (%d)", MAX_G_ALIASES);
		return;
	}
}
