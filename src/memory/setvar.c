#include <mush.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void s_var(const char* varname, const char *varval, bool ro) {
	for (int i=0;i<var_c;i++) {
		if (strcmp(global_vars[i].name,varname) == 0) {
			if (!global_vars[i].readonly) {
				strncpy(global_vars[i].val,varval,MAX_VAR_VAL_SZ);
				if (ro) {
					global_vars[i].readonly = true;
				}
				return;
			} else {
				#ifdef VERBOSE_ERRORS
					printf("Error editing %s: Cannot edit readonly variables!\n", varname);
				#endif
				return;
			}
		}
	}
	if (var_c < MAX_G_VARS) {
		strncpy(global_vars[var_c].name,varname,MAX_VAR_NAME_SZ);
		strncpy(global_vars[var_c].val,varval,MAX_VAR_VAL_SZ);
		if (ro) {
			global_vars[var_c].readonly = true;
		}
		var_c++;
	}
}
