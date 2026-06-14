#ifndef MUSH_H
#define MUSH_H

#define MAX_G_ALIASES 1024
#define MAX_G_VARS 4096
#define MAX_FUNCTIONS 128

#define MAX_VAR_VAL_SZ 1024
#define MAX_VAR_NAME_SZ 64
#define MAX_FUNCTION_LINES_SZ 1024

#define MAX_CMD_SZ 2048
#define MAX_BUILTINS_SZ 256

typedef struct {
	char keyw[MAX_VAR_NAME_SZ];
	char eq[MAX_VAR_VAL_SZ];
} Alias;

typedef struct {
	char name[MAX_VAR_NAME_SZ];
	char val[MAX_VAR_VAL_SZ];
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

/*
typedef struct {
	char *str;
	int count;
} String;
*/ // for mging strings like bash with ${var%%str} (example)

extern Alias global_aliases[MAX_G_ALIASES];
extern Var global_vars[MAX_G_VARS];
extern Function functions[MAX_FUNCTIONS];

extern int var_c;
extern int alias_c;
extern int func_c;
extern bool interactive;

extern char *builtins[MAX_BUILTINS_SZ];

int main(int argc, char *argv[]);
void s_var(const char *varname, const char *varval);
const char *g_var(const char *find_name);
int iactive_shell();
int exec_cmd(const char *cmd);
int cd(const char *path);
void exec(const char *path, char *args[]);
void terminal_wiz_alias();
void setali(const char *keyw, const char *eq);
const char *getali(const char *find_name);
void setup_default_environment();

#endif
