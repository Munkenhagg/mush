#include <mush.h>
#include <user_config.h>
#include <release_info.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <pwd.h>
#include <signal.h>

int var_c = 0;
int func_c = 0;
int alias_c = 0;
bool interactive = true;

uid_t uid;
char *user;

Alias global_aliases[MAX_G_ALIASES];
Var global_vars[MAX_G_VARS];
Function functions[MAX_FUNCTIONS];
ps_mode_t ps_mode;

builtin_t builtins[] = {
	{"chdir", (builtin_fn_t)mush_chdir},
	{"extern", (builtin_fn_t)extern_cmd},
	{"exit", (builtin_fn_t)exit_iact_sh},
	{"source", (builtin_fn_t)source},
	{".", (builtin_fn_t)source},
	{"pwd", (builtin_fn_t)mush_pwd},
	{NULL, NULL}
};

int main(int argc, char *argv[]) {
	uid = getuid();
	struct passwd *user_pw = getpwuid(uid);
	if (user_pw == NULL) {
		perror("getpwuid");
		printf("UID: %d\n", uid);
		#ifdef STRICT_MODE
			return 1;
		#endif
	}
	char *user = strdup(user_pw->pw_name);
	s_var("USER", user);
	struct sigaction saction;
	memset(&saction, 0, sizeof(saction));
	saction.sa_handler = exit_iact_sh;
	sigemptyset(&saction.sa_mask);
	saction.sa_flags = SA_RESTART;
	sigaction(SIGINT, &saction, NULL);
	#ifdef DUMP_DEBUG_INFO
		printf("global C user: %s\nglobal shell user: %s\nglobal C UID: %d\n", user, g_var("USER"), uid);
	#endif
	if (argc < 2) {
		puts("Starting interactive shell");
		setup_default_environment();
		iactive_shell();
		return 0;
	}
	if (strcmp(argv[1], "-c") == 0) {
		if (argc >= 3) {
			printf("executing %s\n", argv[2]);
			char **shifted_cmdbuf = argv + 1;
			exec_cmd(shifted_cmdbuf);
		} else {
			puts("No command for -c");
			return 1;
		}
	}
	if (strcmp(argv[1], "-v") == 0) {
		printf("Munken Shell mush, Version %s-%s\n<%s>\nLicense GPLv3 GNU GPL version 3\n", RELEASE_VERSION, RELEASE_BRANCH, RELEASE_MAIN_HOST_SITE);
		#ifdef RELEASE_FORK
			printf("Fork by: %s" RELEASE_FORK_CREATOR);
		#endif
	}
	return 0;
	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		printf("mush help:\n\t-c: executes a command\n\t-h, --help: prints this help message\n\nmush is a shell made for linux");
	}
}
