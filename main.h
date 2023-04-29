#ifndef MAIN_H
#define MAIN_H
#include "macros.h"
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
/* #include <signal.h>*/
#include <sys/stat.h>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define COMMAND_NORM 0
#define COMMAND_OR 1
#define COMMAND_AND 2
#define COMMAND_CHAIN 3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USING_GETLINE 0
#define USING_STRTOK 0

#define HISTORY_FILE	".hsh_history"
#define MAX_HISTORY	1000

extern char **environ;


/**
 * struct list_s - a singly linked list
 * @number: number field
 * @string: a string
 * @next: points to the next node
 */
typedef struct list_s
{
	int number;
	char *string;	
	struct list_s *next;
} list_t;

/**
 *struct func_data - to pass data to a function,
 *@getline_arg: a string generated from getline containing arguements
 *@agstr: array of str chars tokenized from argument
 *@command_path: a string containing path of current command
 *@ac: number of arguments
 *@err_count: the error count
 *@er_num: the error code for exit functions
 *@lc_flag: when set to on, count current command line input
 *@filename: filename
 *@env: a linked list of the environment
 *@environ: copy of environ
 *@hist: history node
 *@alias_node_node: the alias_node node
 *@env_status: set to on when environ is changed
 *@exec_stat: return's status of the last command
 *@command_buffer: address of pointer to cmd_buf, set to on if chaining
 *@command_btype: stores command type "||, &&, ;"
 *@rfd: file descriptor for reading input
 *@hist_cnt: the number of commands executed
 */
typedef struct data
{
	char *getline_arg;
	char **agstr;
	char *command_path;
	int ac;
	unsigned int err_count;
	int er_num;
	int lc_flag;
	char *filename;
	list_t *env;
	list_t *hist;
	list_t *alias_node;
	char **environ;
	int env_status;
	int exe_stat;

	char **command_buffer;
	int command_btype;
	int rfd;
	int hist_cnt;
} func_t;

#define FUNCT_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, \
NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, 0, 0, 0}

/**
 *struct builtin_strings - contains a builtin string and related function
 *@s_type: builtin command flags
 *@fun: function pointer
 */
typedef struct builtin_strings
{
	char *s_type;
	int (*fun)(func_t *);
} builtins_t;


/* commands found in loops.c */
int check_if_interactive(func_t *);
int check_delim(char, char *);
int check_alpha(int);
int prompt(func_t *, char **);
void find_command(func_t *data);
void fork_command(func_t *);
int handle_builtins(func_t *);

/* found in  */
int valid_command(func_t *, char *);
char *_charsdup(char *, int, int);
char *_find_full_path(func_t *, char *, char *);

void _eputs(char *str);
int _erratoi(char *s);
void print_error(func_t *data, char *estr);
int print_echar(char c);
int put_fd(char c, int fd);
int puts_fd(char *str, int fd);

int _strlen(char *);
int _strcmp(const char *first, const char *second);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

char *_strcpy(char *, char *);
char *_strdup(const char *str);
void _puts(char *);

int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);
int bfree(void **);


int _atoi(char *);

int print_decimal(int, int);
char *convert_num(long int, int, int);
void remove_comments(char *);

int exit_shell(func_t *);
int change_directory(func_t *);
int shell_help(func_t *data);

int hist_list(func_t *data);
int print_alias_node(list_t *node);
int set_alias_node(func_t *data, char *str);
int unset_alias_node(func_t *data, char *string);
int alias_node(func_t *);

ssize_t getline_input(func_t *data);
int _getline(func_t *, char **, size_t *);
ssize_t read_buffer(func_t *data, char *buffer, size_t *i);
void sigint_handler(int);
ssize_t input_buffer(func_t *data, char **buffer, size_t *length);
int _getline(func_t *data, char **ptr, size_t *length);

void clear_data(func_t *data);
void set_data(func_t *data, char **av);
void free_data(func_t *data, int all);

char *_getenv(func_t *, const char *);
int set_env(func_t *data);
int unset_env(func_t *data);
int shell_env(func_t *);
int append_env_list(func_t *);

char **get_environ(func_t *);
int _unsetenv(func_t *, char *);
int _setenv(func_t *, char *, char *);

char *get_history_file(func_t *data);
int write_history(func_t *data);
int read_history(func_t *data);
int build_history_list(func_t *data, char *buf, int linecount);
int renumber_history(func_t *data);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t list_length(const list_t *);
char **list_arrays(list_t *);
size_t print_linked_list(const list_t *);
list_t *node_matches_prefix(list_t *, char *, char);
ssize_t getnode_at_index(list_t *, list_t *);

int check_chain_delims(func_t *, char *, size_t *);
void continue_chains(func_t *, char *, size_t *, size_t, size_t);
int replace_alias_node(func_t *);
int replace_variables(func_t *);
int replace_str(char **, char *);

/* tokens.c */
char **strtwd(char *str, char *delim);
char **strtwd2(char *str, char delim);
void *reallocate_memory(void *ptr, unsigned int old_size, unsigned int new_size);
#endif
