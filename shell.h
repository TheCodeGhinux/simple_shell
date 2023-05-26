#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

#define END_OF_FILE -2
#define EXIT -3

extern char **environ;

/* Global environemnt */
extern char **envn;
/* Global program name */
char *name;
/* Global history counter */
int hist;


/**
 * struct builtin_s - A new struct type defining builtin commands.
 * @name: Name of the builtin command.
 * @f: A function pointer to the builtin command's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **commandLine);
} builtin_t;


/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/**
 * struct list_s - A new struct type defining a linked list.
 * @num: the number field
 * @str: a string
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	int num;
	char *str;
	char *dir;
	struct list_s *next;
} list_t;


/**
 * struct passinfo - it contains pseudo-arguements to pass into a function,
 * allows uniform prototype for function pointer struct
 * @arg: string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: argument count
 * @line_count: error count
 * @err_num: error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_c;


/* strn1.c */
int interactive(info_c *);
int is_delimeter(char, char *);
int _isalphabet(int);
int _strn(char *);


/* Main Helpers */
ssize_t get_line(char **lineprev, size_t *n, FILE *stream);
void *re_alloc(void *prev, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *command);
list_t *get_path_dir(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);



/* Input Helpers */
void handle_line(char **line, ssize_t read);
void variable_replacement(char **args, int *exe_ret);
char *get_args(char *line, int *exe_ret);
int call_args(char **args, char **front, int *exe_ret);
int run_args(char **args, char **front, int *exe_ret);
int handle_args(int *exe_ret);
int check_args(char **args);
void free_args(char **args, char **front);
char **replace_aliases(char **args);


/* String functions */
int _strlen(const char *l);
char *_strcat(char *dest, const char *sc);
char *_strncat(char *dest, const char *sc, size_t n);
char *_strcpy(char *dest, const char *sc);
char *_strchr(char *l, char a);
int _strspn(char *l, char *y);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);


/* Builtins */
int (*get_builtin(char *command))(char **args, char **cmdline);
int shell_help(char **args, char __attribute__((__unused__)) **cmdline);
int shell_exit(char **args, char **cmdline);
int shell_env(char **args, char __attribute__((__unused__)) **cmdline);
int shell_setenv(char **args, char __attribute__((__unused__)) **cmdline);
int shell_unsetenv(char **args, char __attribute__((__unused__)) **cmdline);
int _mycd(info_c *);
int shell_alias(char **args, char __attribute__((__unused__)) **cmdline);


/* Builtin Helpers */
char **env_copy(void);
void free_env(void);
char **env_get(const char *var);

/* Error Handling */
int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/* Error Handling */
int create_error(char **args, int err);
char *err_env(char **args);
char *err_1(char **args);
char *err_2_exit(char **args);
char *err_2_cd(char **args);
char *err_2_syntax(char **args);
char *err_126(char **args);
char *err_127(char **args);

/* Linkedlist Helpers */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

int proc_file_commands(char *file_path, int *exe_ret);
#endif
