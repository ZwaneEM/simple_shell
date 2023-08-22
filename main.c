#include "main.h"

/**
 * main - simple shell in c
 * @argsc: The number of args passed
 * @argsv: The args passed
 * @enviro: The environment of the program
 * Return: 0
 * Mtho and Rosina
 */
int main(int argsc, char **argsv, char **enviro)
{
	char path[100];

	while (1)
	{
		printf("ourshell $ ");
		fgets(path, sizeof(path), stdin)

		int length = strlen(path);
		if (length > 0 && path[length-1] != '\n')
		{
			printf("Try Again, Command too long.\n");

			int character;
			while((character = getchar()) != '\n'
				&& character != EOF);
		} else 
			exit(0);

	return (0);
}
