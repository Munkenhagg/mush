#include <mush.h>
#include <stdlib.h>
#include <stdio.h>

int source(char *path) {
	char buf[MAX_PATH_SZ];
	if (!realpath(path, buf)) {
		printf("realpath failed on file: %s\n", path);
		#ifdef STRICT_MODE
			printf("Exiting due to strict mode. Reason should be above\n");
			exit_iact_sh(0);
		#endif
	}
	FILE *source_file = fopen(buf, "r");
	if (!source_file) {
		perror("source");
	}
	fclose(source_file);
	return 0;
}
