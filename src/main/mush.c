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
	struct sigaction saction;
	memset(&saction, 0, sizeof(saction));
	saction.sa_handler = exit_iact_sh;
	sigemptyset(&saction.sa_mask);
	saction.sa_flags = SA_RESTART;
	sigaction(SIGINT, &saction, NULL);
	s_var("USER", user, true);
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
	#ifdef CONFIG_PRINT_COMPILED_CONFIG
		if (strcmp(argv[1], "-C") == 0 || strcmp(argv[1], "--print-compiled-config") == 0) {
			printf("DUMP_DEBUG_INFO: ");
			#ifdef DUMP_DEBUG_INFO
				printf("yes\n");
			#else
				printf("no\n");
			#endif
			printf("STRICT_MODE: ");
			#ifdef STRICT_MODE
				printf("yes\n");
			#else
				printf("no\n");
			#endif
			printf("VERBOSE_ERRORS: ");
			#ifdef VERBOSE_ERRORS
				printf("yes\n");
			#else
				printf("no\n");
			#endif
			printf("ALWAYS_ECHO_COMMANDS: ");
			#ifdef ALWAYS_ECHO_COMMANDS
				printf("yes\n");
			#else
				printf("no\n");
			#endif
			printf("CONFIG_PRINT_COMPILED_CONFIG: ");
			#ifdef CONFIG_PRINT_COMPILED_CONFIG
				printf("yes\n");
			#else
				printf("no\n");
			#endif
			printf("MUSH_EXITED_MSG: \"%s\"\n", MUSH_EXIT_MSG);
			printf("HISTORY_F: \"%s\"\n", HISTORY_F);
			printf("HOME_LOCATION: \"%s\"\n", HOME_LOCATION);
			printf("ROOT_HOME_LOCATION: \"%s\"\n", ROOT_HOME_LOCATION);
			printf("MAX_G_ALIASES: %d\n", MAX_G_ALIASES);
			printf("MAX_G_VARS: %d\n", MAX_G_VARS);
			printf("MAX_FUNCTIONS: %d\n", MAX_FUNCTIONS);
			printf("MAX_VAR_VAL_SZ: %d\n", MAX_VAR_VAL_SZ);
			printf("MAX_VAR_NAME_SZ: %d\n", MAX_VAR_NAME_SZ);
			printf("MAX_FUNCTION_LINES_SZ\n", MAX_FUNCTION_LINES_SZ);
			printf("MAX_CMD_SZ: %d\n", MAX_CMD_SZ);
			printf("MAX_PATH_SZ: %d\n", MAX_PATH_SZ);
			printf("MAX_SHELL_PATHS: %d\n", MAX_SHELL_PATHS);
			printf("MAX_SINGLE_ARG_SZ: %d\n", MAX_SINGLE_ARG_SZ);
		}
	#endif

	if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
		printf("mush help:\n\t-c: executes a command\n\t-h, --help: prints this help message\n");
		#ifdef CONFIG_PRINT_COMPILED_CONFIG
			printf("-C|--print-compiled-config: prints the core configuration mush was compiled with\n");
		#endif
		printf("\nMush is a shell made for linux");
	}
	return 0;
}
