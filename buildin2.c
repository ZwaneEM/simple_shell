#include "main.h"

/**
 * buildin_detect_2 - handles buildin unsetenv and
 * setenv
 * @comm: The command inputed by the user
 * Return: Nothing
 */
void buildin_detect_2(char **comm)
{
	char *_token_env, *_token, *val, *env_name;
	char *comm_cpy = strdup(*comm);
	char *comm1 = strdup(*comm);
	int choice = 0;
	int ret_env, i;

	_token = strtok(comm1, " ");
	for (i = 0; _token != NULL; i++)
		_token = strtok(NULL, " ");
	free(comm1);
	_token_env = strtok(comm_cpy, " ");
	if (_token_env != NULL)
	{
		if (strcmp(_token_env, "setenv") == 0 && i == 3)
			choice += 1;
		else if (strcmp(_token_env, "unsetenv") == 0 && i == 2)
			choice += 2;
		else
			write(STDERR_FILENO, "Invalid no. arguments\n", 22);
	}
	if (choice == 1)
	{
		env_name = strdup(strtok(NULL, " "));
		val = strdup(strtok(NULL, " "));
		ret_env = setenv(env_name, val, 1);
		free(env_name);
		free(val);
		if (ret_env == -1)
			perror("Error");
	}
	else if (choice == 2)
	{
		env_name = strdup(strtok(NULL, " "));
		ret_env = unsetenv(env_name);
		free(env_name);
		if (ret_env == -1)
			perror("Error");
	}
	free(comm_cpy);
}
