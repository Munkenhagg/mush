#include <mush.h>
#include <unistd.h>

void exec(const char *path, char *args[]) {
	execvp(path, args);
	return;
}
