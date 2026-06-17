#include <mush.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

char *strjoin(char *stringa, char *stringb) {
	char *strings[] = {stringa,stringb};
	size_t total = 1;
	for (int i = 0; strings[i]; i++) {
		total += strlen(strings[i]);
	}
	char *combined_string = malloc(total);
	if (!combined_string) {
		return NULL;
	}
	char *p = combined_string;
	for (int i = 0; strings[i]; i++) {
		strcpy(p, strings[i]);
		p += strlen(strings[i]);
	}
	*p = '\0';
	return combined_string;
}
