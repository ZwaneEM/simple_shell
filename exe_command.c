#include "main.h"

/**
* exe_command - executes a path or command provided
* by the user.
* @comm: The full path command to executed
* @comm_path: the array of arguments for command
* @erroNo: The message to execute if error occur
*
* Return: 1 on error and No return on success
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
* @comm: The command to check for
* @comm_path: The array of arguments to command
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
