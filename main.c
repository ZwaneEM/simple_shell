#include "main.h"

/**
 * main - simple shell in c
 * @argsc: The number of args passed
 * @argsv: The args passed
 * @enviro: The environment of the program
 * Return: 0
 */
int main(int argsc, char **argsv, char **enviro)
{
	char path[100];

	while (1)
	{
		printf("ourshell $ ");

		if (fgets(path, sizeof(path), stdin) == NULL)
		{
			if (feof(stdin))
			{
				break;
			}

			perror(argsv[0]);
			continue;
		}

		path[strcspn(path, "\n")] = '\0';

		exe_command(path, argsv[0]);
	}

	return (0);
}
