#include "main.h"

/**
 * main - simple shell
 * @argc: The number of arguments passed to main
 * @argv: arguments sent to main
 * @env: Current environment variables
 * Return: 0 on success
 */
int main(int argc, char **argv, char **env)
{
	char *prompt = getenv("PWD");
	char *input = NULL;
	ssize_t nchar;
	char **av = argv;
	size_t len = 0;
	int checked;
	char *command;
	(void)argc;
	while (4)
	{
		printf("%s $ ", prompt); /*prompt the user*/
		nchar = getline(&input, &len, stdin);
		if (nchar != -1)
		{
		argv = arr_make(input);
		checked = check_comm(argv[0]);
		if (checked == 3)
		{
			print_env(env);
		}
		if (checked == 2)
		{
			return (0);
		}
		if (checked == 1)
		{
			command = get_env(argv[0]);
			if (command != NULL)
			{
				argv[0] = strdup(command);
				final_process(argv, av[0]);
			}
			else
			{
				perror(av[0]);
			}
		}
		}
	}
	return (0);
}


/**
 * arr_make - takes user input and turn it to
 * array of words
 * @str: The string to process
 * Return: pointer to array of pointers
 */
char **arr_make(char *str)
{
	char *token = strtok(str, " \n");
	char **arg = malloc(sizeof(char *) * 8);
	int i = 0;

	while (token != NULL)
	{
		arg[i] = token;
		i++;
		token = strtok(NULL, " \n");
	}

	return (arg);
}
