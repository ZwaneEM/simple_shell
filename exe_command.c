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
	if (execve(comm, comm_path, environ) == -1)
	{
		write(STDERR_FILENO, erroNo, strlen(erroNo));
		write(STDERR_FILENO, ": 1: ", 5);
		write(STDERR_FILENO, comm, strlen(comm));
		write(STDERR_FILENO, ": not found\n", 12);
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
int check_comm(char *comm, char **comm_path, char *erroNo)
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
			return (0);
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

		write(STDERR_FILENO, erroNo, strlen(erroNo));
		write(STDERR_FILENO, ": 1: ", 5);
		write(STDERR_FILENO, comm, strlen(comm));
		write(STDERR_FILENO, ": not found\n", 12);
		return (1);
	}

	return (0);
}
