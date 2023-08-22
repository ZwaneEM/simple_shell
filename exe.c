#include "main.h"

/**
 * exe_command - executes a command
 * @pathname: The command to execute
 * @perr: Error to give
 * Return: Nothing
 */
void exe_command(char *pathname, char *perr)
{
	pid_t pid = fork();

	if (pid == 0)
	{
		if (execlp(pathname, pathname, NULL) == -1)
		{
			perror(perr);
			exit(EXIT_FAILURE);
		}

	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		perror(perr);
		exit(EXIT_FAILURE);
	}
}
