#include "main.h"

/**
* _get_line - reads a line from the standard input
*	and writes it into line pointer
* @line: The pointer to store the line read in
* Return: The actual number of char read.
*/
ssize_t _get_line(char **line)
{
	static char buffer[MAX_READ];
	ssize_t nread;
	int size = 10;
	int i;

	if (*line == NULL)
	{
		*line = malloc(sizeof(char) * 10);
		if (*line == NULL)
		{
			perror("Malloc failure");
			return (-1);
		}
	}
	nread = read(STDIN_FILENO, buffer, MAX_READ);
	if (nread == -1)
	{
		free(*line);
		perror("Read error");
		return (-1);
	}
	if (nread == 0)
	{
		free(*line);
		if (isatty(STDIN_FILENO))
			putchar('\n');
		exit(0);
	}
	if (nread > size)
	{
		*line = realloc(*line, (nread + 1));
	}
	for (i = 0; i < nread; i++)
	{
		(*line)[i] = buffer[i];
	}
	i--;
	(*line)[i] = '\0';

	return (nread);
}

/**
 * non_interactive - is going to execute command in
 *	non interactive mode
 * @comm: The command to start executing
 * Return: Nothing
 */
void non_interactive(char **comm)
{
	char **arg_commands = NULL;
	char *_token_f;
	char **args;
	int i = 0;
	int v = 0;
	char *filename = getenv("_");
	char *full_comm = NULL;

	_token_f = strtok(*comm, "\n");
	while (_token_f != NULL)
	{
		if (arg_commands == NULL)
			arg_commands = malloc(sizeof(char *) * 10);
		arg_commands[i] = strdup(_token_f);
		i++;
		_token_f = strtok(NULL, "\n");
	}
	if (arg_commands != NULL)
		arg_commands[i] = NULL;
	while (arg_commands[v] != NULL)
	{
		args = non_inttokenize(arg_commands[v]);
		if (args != NULL)
		{
			full_comm = find_path(args[0]);
			check_comm(full_comm, args, filename);
			free_arr(args);
			free(full_comm);
			full_comm = NULL;
			v++;
		}
	}
}
/**
 * non_inttokenize - tokenizes a list of command passed
 * in non_interactive mode
 * @arg: Pointer to the string of commands
 * Return: Pointer to Pointers of the commands
 */
char **non_inttokenize(char *arg)
{
	char **args = NULL;
	int i = 0;
	char *_token_2nd;

	if (arg == NULL)
		return (NULL);

	args = malloc(sizeof(char *) * 10);

	_token_2nd = strtok(arg, " \t\n");

	while (_token_2nd != NULL)
	{
		args[i] = strdup(_token_2nd);
		i++;
		_token_2nd = strtok(NULL, " \t\n");
	}

	if (arg != NULL)
		args[i] = NULL;

	return (args);
}
