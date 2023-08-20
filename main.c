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
	ssize_t nchar;
	char *av = getenv("_");
	size_t len = 0;
	int checked;
	char *command, *input;
	(void)argc;
	while (4)
	{
		printf("%s $ ", prompt);
		nchar = getline(&input, &len, stdin);
		if (nchar == -1)
		{
			free(input);
			return (0);
		}
		argv = arr_make(input);
		checked = check_comm(argv[0]);
		if (checked == 3)
			print_env(env);
		if (checked == 2)
		{
			free(argv);
			free(input);
			return (0);
		}
		if (checked == 1)
		{
			command = get_env(argv[0]);
			if (command != NULL)
			{
				argv[0] = strdup(command);
				final_process(argv, av);
			}
			else
				perror(av);
			free(argv);
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
	const char *delim = " \n";
	char *_token = strtok(str, delim);
	char **arg;
	int i = 0;
	int ntoken = 0;

	while (_token != NULL)
	{
		ntoken++;
		_token = strtok(NULL, delim);
	}

	_token = strtok(str, delim);
	arg = malloc(sizeof(char *) * ntoken);

	while (_token != NULL)
	{
		arg[i] = malloc(sizeof(char) * strlen(_token));
		arg[i] = _token;
		i++;
		_token = strtok(NULL, delim);
	}
	return (arg);
}

/**
 * clean_mem - clean allocated memory left behind
 * @pron: The integer
 * Return: Nothing
 *
 *void clean_mem(int pron)
 *{
 *	free(input);
 *	free(command);
 *	putchar('\n');
 *	exit(98);
 *}
 */
