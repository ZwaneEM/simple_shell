#include "main.h"

/**
 * prompt_usr - prompts the user and get the user data
 * after being inputed in the stdin
 * Return: A pointer to the typed data or NULL if failed.
*/
list_t *prompt_usr(void)
{
	ssize_t t_nchar;
	list_t *fp;
	char *input_data = NULL;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	t_nchar = _get_line(&input_data);
	if (t_nchar == -1)
	{
		free(input_data);
		perror("Error");
		return (NULL);
	}
	fp = malloc(sizeof(list_t));
	fp->comm = strdup(input_data);
	fp->len = strlen(input_data);

	free(input_data);

	check_sep_op(&fp);

	return (fp);
}

/**
 * free_mem - free memory after use
 * @head: The memory to free
 * Return: Nothing.
*/
void free_mem(list_t **head)
{
	free((*head)->comm);
	free(*head);
}

/**
 * find_path - finds the true path of a command
 * @comm_find: The command to find path for
 *
 * Return: a pointer to the full path of the command
*/
char *find_path(char *comm_find)
{
	struct stat fp_buf;
	char *path = getenv("PATH");
	char *path_cpy;
	char *_token_path, *comm;
	int len_comm;
	int token_len;

	path_cpy = strdup(path);
	len_comm = strlen(comm_find);
	_token_path = strtok(path_cpy, ":");

	while (_token_path != NULL && comm_find[0] != '.')
	{
		token_len = strlen(_token_path);
		comm = malloc(sizeof(char) * (len_comm + token_len + 2));
		strcpy(comm, _token_path);
		strcat(comm, "/");
		strcat(comm, comm_find);
		strcat(comm, "\0");

		if (stat(comm, &fp_buf) == 0)
		{
			free(path_cpy);
			path_cpy = NULL;
			return (comm);
		}
		free(comm);
		_token_path = strtok(NULL, ":");
	}
	free(path_cpy);
	path_cpy = NULL;

	if (access(comm_find, X_OK) == 0)
	{
		comm = strdup(comm_find);
		return (comm);
	}
	comm = strdup(comm_find);

	return (comm);
}

/**
 * check_sep_op - checks and executes command separated by
 * by ; command separator
 * @input: structure containing the command
 * Return: nothing
 *
 */
void check_sep_op(list_t **input)
{
	char *comm_cpy = strdup((*input)->comm), *_token;
	int i = 0, v = 0;
	char **comm = NULL, **arg_comm = NULL;

	if (strchr(comm_cpy, ';') == NULL)
	{
		free(comm_cpy);
		return;
	}
	_token = strtok(comm_cpy, ";\n");
	while (_token != NULL)
	{
		if (comm == NULL)
			comm = malloc(sizeof(char *) * 10);
		if (comm == NULL)
		{
			free(comm_cpy);
			perror("Error");
			return;
		}
		comm[i] = strdup(_token);
		i++;
		_token = strtok(NULL, ";\n");
	}
	if (comm != NULL)
		comm[i] = NULL;
	while (comm[v] != NULL)
	{
		arg_comm = command_tokenize(comm[v]);
		if (arg_comm != NULL)
		{
			exe_sep_op(arg_comm);
			free_arr(arg_comm);
		}
		v++;
	}
	free_arr(comm);
	free(comm_cpy);
	free((*input)->comm);
	(*input)->comm = strdup("\n");
}

/**
 * exe_sep_op - executes the command passed by the
 * check sep function.
 * @comm: The command to execute
 * Return: Nothing
 */
void exe_sep_op(char **comm)
{
	char *comm_full;
	char *erroNo = getenv("_");

	comm_full = find_path(comm[0]);
	check_comm(comm_full, comm, erroNo);
	free(comm_full);
	comm_full = NULL;
}
