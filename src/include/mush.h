#ifndef MUSH_H
#define MUSH_H

#define MAX_G_ALIASES 1024
#define MAX_G_VARS 4096
#define MAX_FUNCTIONS 128

#define MAX_VAR_VAL_SZ 1024
#define MAX_VAR_NAME_SZ 64
#define MAX_FUNCTION_LINE_SZ 1024

typedef struct {
	char keyword[MAX_VAR_NAME_SZ];
	char equals[MAX_VAR_VAL_SZ];
} Alias;

typedef struct {
	char name[MAX_VAR_NAME_SZ];
	char val[MAX_VAR_VAL_SZ];
} Var;

typedef struct {
	char name[MAX_VAR_NAME_SZ];
	char *code[MAX_FUNCTION_LINE_SZ];
	int len;
} Function;

extern Alias global_aliases[MAX_G_ALIASES];
extern Var global_vars[MAX_G_VARS];
extern Function functions[MAX_FUNCTIONS];

extern int var_c;
extern int alias_c;
extern int func_c;

int main(int argc, char *argv[]);
void s_var(const char *varname, const char *varval);
const char *g_var(const char *find_name);
int iactive_shell();
int exec_cmd(const char *cmd);
int cd(const char *path);
void exec(const char *path, const char *args[]);
void terminal_wiz_alias();
void setalias(const char *keyw, const char *eq);

#endif
