#include <mush.h>
#include <string.h>
#include <stdlib.h>

const char *getali(const char* find_name) {
    for (int i=0;i<alias_c;i++) {
        if (strcmp(global_aliases[i].keyw,find_name) == 0) {
            return global_aliases[i].eq;
        }
    }
    return NULL;
}
