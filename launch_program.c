#include "main.h"

/**
 * launch_program -  function for launching the program
 * @args: commandline args
 * @background: status, whether program runs in fore/background.
*/

void launch_program(char **args, int background)
{
	int error = -1;

	pid = fork();
	if (pid == -1)
	{
		printf("\nChild process not created\n");
		return;
	}

	if (pid == 0)
	{
		/* Child process set to ignore SIGINT signals */
		signal(SIGINT, SIG_IGN);

		/*set parent=<current directory> as an environment variable */
		setenv("parent", getcwd(current_directory, MAX_LINE), 1);

		/* if launched program does not exist, end the process */
		if (execvp(args[0], args) == error)
		{
			printf("\n%s: Command not found\n");
			kill(getpid(), SIGTERM);
		}
	}

	/**
	 * Executed by parent
	 * if process not requested to be in background,
	 * wait for the child to complete execution
	*/

	if (background == 0)
		waitpid(pid, NULL, 0);
	else
		printf("Process created with PID: %d\n", pid);
}
