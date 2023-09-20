#include "main.h"

/**
 * main - Entry point for shell
 * @argsc: The number of arguments passed to the main function
 * @argsv: The arguments passed in to main function
 * Return: 0 on success / -1 on failure.
*/
int main(__attribute__((unused))int argsc, char **argsv)
{
	list_t *input = NULL;
	char **arguv = NULL;
	int build = 0;
	char *comm_full = NULL;

	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, SIG_IGN);  /* Ignore Ctrl+Z */

	while (1)
	{
		input = prompt_usr();
		if (input == NULL)
		{
			if (isatty(STDIN_FILENO))
				putchar('\n');
			break;
		}
		if (input->comm[0] != '\n')
		{
			build = buildin_detect(&input);
			if (build == 0)
			{
			arguv = command_tokenize(input->comm);
			if (arguv != NULL)
			{
				comm_full = find_path(arguv[0]);
				check_comm(comm_full, arguv, argsv[0]);
				free_arr(arguv);
				free(comm_full);
				comm_full = NULL;
			}
			}
			free_mem(&input);
		}
		else
			free_mem(&input);
	}
	return (0);
}

/**
* sigint_handler - handles the sigint signal
* by sending the program to a function to clean
* the remaining un freed memory
* @sig_num: The signal received
* Return: Nothing
*/
void sigint_handler(__attribute__((unused))int sig_num)
{
	write(STDOUT_FILENO, "\n$ ", 3);
	fflush(stdout);
}


/**
 * command_tokenize - It makes the user input into
 * an array of command and arguments
 * @arg: The input to tokenize
 * Return: Nothing.
*/
char **command_tokenize(char *arg)
{
	char *_token;
	char **args = NULL;
	int i;
	int v = 0;
	char *arg_cpy = strdup(arg);

	if (isatty(STDIN_FILENO))
	{
		_token = strtok(arg_cpy, " \t\n");

		i = 0;

		while (_token != NULL)
		{
			if (v == 0)
			{
				args = malloc(sizeof(char *) * 10);
				v += 1;
			}

			args[i] = strdup(_token);
			i++;
			_token = strtok(NULL, " \t\n");
		}
		if (args != NULL)
			args[i] = NULL;
	}
	else
	{
		non_interactive(&arg_cpy);
	}
	free(arg_cpy);

	return (args);
}

/**
 * free_arr - Frees the array after each use
 * @argsv: The dynamically allocated array to free
 * Return: Nothing
 */
void free_arr(char **argsv)
{
	int i;

	for (i = 0; argsv[i] != NULL; i++)
	{
		free(argsv[i]);
	}
	free(argsv);
	argsv = NULL;
}
