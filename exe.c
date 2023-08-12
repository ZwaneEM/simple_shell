#include "main.h"

/**
 * exe_command - executes a command
 * @argv: The command to executes with arguments
 * @erroval: The error to return
 * Return: Nothing
 */
void exe_command(char **argv, char *erroval)
{
	if (argv)
	{
		if (execve(argv[0], argv, NULL) == -1)
		{
			perror(erroval);
		}
	}
}

void final_process(char **comm, char *erroN)
{
	pid_t pid;

	if (comm[0] != NULL)
	{
		pid = fork();
		if (pid == -1)
			perror("process didnt start");

		if (pid == 0)
		{
			exe_command(comm, erroN);
		}
		else
		{
			wait(NULL);
		}
	}

}
