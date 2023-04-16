#ifndef MAIN_H
#define MAIN_H

/* Header files to be included */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>


/* FUNCTION PROTOTYPES */
/**
 * Signal handlers
*/

/* signal hangler for SIGCHILD */
void signal_handler_child(int p);

/* signal handler for SIGINT */
void signal_handler_int(int p);

/**
 * OTHER FUNCTION PROTOYPES
*/
void initialize_shell();
int change_directory(char *args[]);
void shell_prompt();


/* Structures */
struct sig_action
{
	void (*sa_handler)(int);
	void (*sa_sig_action)(int, siginfo_t *, void *);
	sigset_t sa_mask;
	int sa_flags;
	void (*sa_restorer)(void);
};

struct sig_action act_child;
struct sig_action act_int;

/* CONSTANTS */
#define TRUE 1
#define FALSE !TRUE
#define MAX_LINE 1024
#define LIMIT 256

/* Shell PID, PGID & TERMINAL MODES */
static pid_t HSH_PID;
static pid_t HSH_PGID;
static int HSH_IS_INTERACTIVE;
static struct termios HSH_TMODES;

/*  Environment, current directory and other variables */
static char *current_directory;
static char **environment;
int no_reprint_prmpt;

pid_t pid;

#endif /* MAIN_H */
