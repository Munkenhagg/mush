#include <mush.h>

void setup_default_environment() {
	s_var("PS1", "mush $ ");
	s_var("PATH", "/usr/bin:/usr/sbin:/usr/local/bin");
	s_var("TERM", "linux");
}
