#include "main.h"

/**
 * initialize_shell - a function to initialize the shell
*/

void initialize_shell()
{
	/* get process identification */
	HSH_PID = getpid();

	/* Check if the file descriptor refers to a terminal */
	HSH_IS_INTERACTIVE = isatty(STDIN_FILENO);

	if (HSH_IS_INTERACTIVE)
	{
		/* Loop until the process runs in the foreground */
		HSH_PGID = getpgrp();

		while (tcgetpgrp(STDIN_FILENO) != HSH_PGID)
			kill(HSH_PID, SIGTTIN);

		/* We set signal handlers for SIGCHILD AND SIGINT */
		act_child.sa_handler = signal_handler_child;
		act_int.sa_handler = signal_handler_int;

		sig_action(SIGCHLD, &act_child, 0);
		sig_action(SIGINT, &act_int, 0);

		/* make the hsh shell process the new process group leader */
		setpgid(HSH_PID, HSH_PGID);

		if (HSH_PID != HSH_PGID)
			exit(EXIT_FAILURE);
		
		/* TAKE CONTROL OF THE TERMINAL */
		tcsetpgrp(STDIN_FILENO, HSH_PGID);

		/* Save default terminal attributes for the shell */
		tcgetattr(STDIN_FILENO, &HSH_TMODES);

		/* set current working directory */
		current_directory = calloc(1024, sizeof(char));
	}
	else
	{
		exit(EXIT_FAILURE);
	}
}
