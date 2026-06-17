#include <mush.h>
#include <user_config.h>
#include <stdio.h>

void setup_default_environment(void) {
	char uid_str[32];
	char home[MAX_PATH_SZ];
	snprintf(uid_str, sizeof(uid_str), "%u", uid);
	if (uid != 0) {
		snprintf(home, sizeof(home), "%s/%s", HOME_LOCATION, user);
	} else {
		snprintf(home, sizeof(home), "%s", ROOT_HOME_LOCATION);
	}
	s_var("PS1", "mush $ ");
	s_var("PATH", "/usr/bin:/usr/sbin:/usr/local/bin");
	s_var("TERM", "linux");
	s_var("UID", uid_str);
	s_var("HOME", home);
}
