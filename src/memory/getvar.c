#include <mush.h>
#include <string.h>
#include <stdlib.h>

const char* g_var(const char* find_name) {
    for (int i=0;i<var_c;i++) {
        if (strcmp(global_vars[i].name,find_name) == 0) {
            return global_vars[i].val;
        }
    }
    return NULL;
}
