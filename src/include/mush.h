#ifndef MUSH_H
#define MUSH_H

#include <sys/types.h>

#define MAX_G_ALIASES 1024
#define MAX_G_VARS 4096
#define MAX_FUNCTIONS 128

#define MAX_VAR_VAL_SZ 1024
#define MAX_VAR_NAME_SZ 64
#define MAX_FUNCTION_LINES_SZ 1024

#define MAX_CMD_SZ 2048
#define MAX_PATH_SZ 2048

typedef struct {
	char keyw[MAX_VAR_NAME_SZ];
	char eq[MAX_VAR_VAL_SZ];
} Alias;

typedef struct {
	char name[MAX_VAR_NAME_SZ];
	char val[MAX_VAR_VAL_SZ];
	bool readonly;
} Var;

typedef struct {
	char name[MAX_VAR_NAME_SZ];
	char *code[MAX_FUNCTION_LINES_SZ];
	int len;
} Function;

typedef enum cmd_kind_e {
	CMD_BUILTIN,
	CMD_EXTERNAL,
	CMD_NOT_FOUND
} cmd_kind_t;

typedef struct exec_target_s {
	char *path;
	cmd_kind_t type;
} exec_target_t;

typedef int (*builtin_fn_t)(void *);

typedef struct builtin_s {
	const char *name;
	builtin_fn_t funct;
} builtin_t;

typedef enum tok_state_e {
	NORMAL,
	SINGLE_QUOTE,
	DOUBLE_QUOTE
} tok_state_t;

typedef enum ps_mode_e {
	PRIMARY = 1,
	CONTINUATION = 2,
	SELECT = 3,
	TRACING = 4
} ps_mode_t;

typedef enum tok_flags_e {
	NONE = 0,
	ESCAPE = 1 << 0,
	VARIABLE = 1 << 1
} tok_flags_t;

/*
typedef struct {
	char *str;
	int count;
} String;
*/ // for mging strings like bash with ${var%%str} (example)

extern Alias global_aliases[MAX_G_ALIASES];
extern Var global_vars[MAX_G_VARS];
extern Function functions[MAX_FUNCTIONS];
extern ps_mode_t ps_mode;
extern builtin_t builtins[];

extern uid_t uid;
extern char *user;

extern int var_c;
extern int alias_c;
extern int func_c;
extern bool interactive;

int main(int argc, char *argv[]);
void s_var(const char *varname, const char *varval, bool readonly);
const char *g_var(const char *find_name);
int iactive_shell(void);
int exec_cmd(char **cmd);
int mush_chdir(const char *path);
void exec(const char *path, char *args[]);
void terminal_wiz_alias(void);
void setali(const char *keyw, const char *eq);
const char *getali(const char *find_name);
void setup_default_environment(void);
builtin_fn_t g_builtin(char *cmd);
char **tokenize(char *cmdinput, char **cmdoutput);
void exit_iact_sh(int exit_num);
int extern_cmd(char *cmd[]);
char *strjoin(char *stringa, char *stringb);
int source(char *path);
int log_hist(char *untok_logbuf);
void mush_pwd(void);

#endif
