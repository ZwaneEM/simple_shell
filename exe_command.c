#include "main.h"

/**
* exe_command - executes a path or command provided
* 	by the user.
* @
*/
int exe_command(char *comm, char **comm_path, char *erroNo)
{
	if (execve(comm, comm_path, NULL) == -1)
	{
		perror(erroNo);
	}

	return (1);
}

/**
* check_comm - checks if the command exists in the user system
*	IF exits it sends it to the exe_command function.
* @comm_path: the command to work on
* @erroNo: The error message to print.
*/
void check_comm(char *comm, char **comm_path, char *erroNo)
{
	pid_t child;
	int i;
	int status;
	struct stat st_buf;

	i = stat(comm, &st_buf);

	if (i == 0)
	{
		child = fork();

		if (child == -1)
		{
			perror("Error with fork");
			return;
		}
		else if (child == 0)
		{
			exe_command(comm, comm_path, erroNo);
		}
		else
		{
			waitpid(child, &status, 0); /* waits for the child process */
		}
	}
	else
	{
		perror(erroNo);
		return;
	}
}
