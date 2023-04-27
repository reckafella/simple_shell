#ifndef MAIN_H
#define MAIN_H

#include "macros.h"
/* Headers */
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

#include <error.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

/* environment */

extern char **environ;

/* macros */
#define MAX_COMMANDS 20
#define MAX_LINE 1024
/* history file */
#define MAX_HISTORY 1000
#define HISTORY_FILE ".hsh_history"

/* FUNCTION PROTOTYPES */

void prompt(char **argv);
void execute_command(char **argv, char *command);
char *_getenv(const char *name);
int _strncmp(const char *first, const char *second, size_t len);
int _strlen(const char *str);
char *_strtok(char *str, const char *delim);
int _strcmp(const char *first, const char *second);
char *getpath(char *command);
char *_strdup(char *str);
int change_directory(char *argv[]);
void cleanup(char *command);
void print_env(void);
void read_history(void);
void append_history(char *command);

#endif
