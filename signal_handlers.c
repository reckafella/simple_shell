#include "main.h"

/**
 * signal_handler_child - a function handling signal for SIGCHLD
 * @p: process ID
 *
 * Return: nothing
*/

void signal_handler_child(int p)
{
	/**
	 * waiting for all dead processes
	 * Use WNOHANG to ensure this handler will not block
	 * if a child was cleaned in another part of the program
	*/
   pid_t process_id = waitpid(-1, NULL, WNOHANG);
   while(process_id > 0)
		continue;
	printf("\n");

}
void signal_handler_int(int p)
{
	/* Terminating a child process */
	if (kill(pid, SIGTERM) == 0)
	{
		printf("\nProcess %d received a SIGINT signal\n", pid);
	}
	else
	{
		printf("\n");
	}
}
