#include "main.h"

/**
 * print_env - prints the variables in the
 * current path
 * @env: The pointer to all pointers in environment
 * Return: Nothing
 */
void print_env(char **env)
{
	/* declaration and initilization */
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}
