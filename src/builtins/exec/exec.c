#include <mush.h>
#include <unistd.h>

void exec(const char *path, const char *args[]) {
	execve(path, args[]);
	return NULL;
}
