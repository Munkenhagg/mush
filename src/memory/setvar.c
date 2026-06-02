#include <mush.h>
#include <stdlib.h>
#include <string.h>

void s_var(const char* varname, const char *varval) {
	for (int i=0;i<var_c;i++) {
		if (strcmp(global_vars[i].name,varname) == 0) {
			strncpy(global_vars[i].val,varval,MAX_VAR_VAL_SZ);
			return;
		}
	}
	if (var_c < MAX_G_VARS) {
		strncpy(global_vars[var_c].name,varname,MAX_VAR_NAME_SZ);
		strncpy(global_vars[var_c].val,varval,MAX_VAR_VAL_SZ);
		var_c++;
	}
}
