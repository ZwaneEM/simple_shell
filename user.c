#include "main.h"

/**
 * prompt_usr - prompts the user and get the user data
 * after being inputed in the stdin
 * Return: A pointer to the typed data or NULL if failed
*/
list_t *prompt_usr(void)
{
	size_t nchar = 0;
	ssize_t t_nchar;
	list_t *fp;
	char *input_data = NULL;

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);

	t_nchar = getline(&input_data, &nchar, stdin);
	if (t_nchar == -1)
	{
		if (feof(stdin))/* looks for when a user types CTRL D*/
		{
			free(input_data); /*free the input*/
			return (NULL);
		}
		free(input_data);
		perror("Error");
		return (NULL);
	}
	fp = malloc(sizeof(list_t));

	fp->comm = strdup(input_data);
	fp->len = strlen(input_data);

	free(input_data);

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

	if (stat(comm_find, &fp_buf) == 0)
	{
		comm = strdup(comm_find);
		return (comm);
	}

	path_cpy = strdup(path);
	len_comm = strlen(comm_find);

	_token_path = strtok(path_cpy, ":");

	while (_token_path != NULL)
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
			return (comm);
		}

		free(comm);
		_token_path = strtok(NULL, ":");
	}
	free(path_cpy);

	comm = strdup(comm_find);

	return (comm);
}
