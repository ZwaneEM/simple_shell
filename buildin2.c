#include "main.h"

/**
 * buildin_detect_2 - handles buildin unsetenv and
 * setenv
 * @comm: The command inputed by the user
 * Return: Nothing.
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

/**
 * buildin_detect_3 - detects and processes the buildin cd
 * @comm: The command to process
 * Return: Nothing
 */
void buildin_detect_3(char **comm)
{
	char *comm_cpy = strdup(*comm);/*dynamically allocated*/
	char *comm_cpy2 = strdup(*comm);
	char *_token, *new_wd;
	int i;
	char *home = getenv("HOME");
	char *old_wd = getenv("PWD");

	_token = strtok(comm_cpy, " ");

	for (i = 0; _token != NULL; i++)
		_token = strtok(NULL, " "); /* gets the number of arguments + command*/

	_token = strtok(comm_cpy2, " ");
	_token = strtok(NULL, " ");

	if (i > 2)
	{
		write(STDERR_FILENO, "cd: too many arguments\n", 23);
		free(comm_cpy);
		return;
	}
	else if (i == 1 || strcmp(_token, "~") == 0)
	{
		_handle_change(old_wd, &home);
	}
	else if (i == 2)
	{
		new_wd = strdup(_token);
		_handle_change(old_wd, &new_wd);
		free(new_wd);
	}
	free(comm_cpy);
	free(comm_cpy2);
}

/**
 * _handle_change - handles the switching of the wd
 * @old_wd: old working directory
 * @new_wd: new working directory to change to
 * Return: Nothing.
 */
void _handle_change(char *old_wd, char **new_wd)
{
	int ret, sig, sig1;
	char pwd[1000];
	char *oldPWD = getenv("OLDPWD");
	char *filename = getenv("_");

	if (strcmp((*new_wd), "-") == 0)
	{
		handle_special(old_wd, oldPWD);
		return;
	}

	ret = chdir(*new_wd);
	if (ret == -1)
	{
		write(STDERR_FILENO, filename, strlen(filename));
		write(STDERR_FILENO, ": 1: cd: ", 9);
		perror("");
		return;
	}

	sig = setenv("OLDPWD", old_wd, 1);
	if (sig == -1)
	{
		perror("setenv() error");
		return;
	}

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd() error");

	sig1 = setenv("PWD", pwd, 1);
	if (sig1 == -1)
	{
		perror("setenv() errror");
		return;
	}
}

/**
 * handle_special - handles the execution of -
 * special char that means old pwd
 * @old_wd: the old path
 * @new_: new path to move in to
 * Return: Nothing
 */
void handle_special(char *old_wd, char *new_)
{
	int ret, sig, sig1;
	char pwd[1000];
	char *filename = getenv("_");

	if (new_ == NULL)
		return;

	ret = chdir(new_);
	if (ret == -1)
	{
		write(STDERR_FILENO, filename, strlen(filename));
		write(STDERR_FILENO, ": 1: cd: ", 9);
		perror("");
		return;
	}

	sig = setenv("OLDPWD", old_wd, 1);
	if (sig == -1)
	{
		perror("setenv() error");
		return;
	}

	if (getcwd(pwd, sizeof(pwd)) == NULL)
		perror("getcwd() error");

	sig1 = setenv("PWD", pwd, 1);
	if (sig1 == -1)
	{
		perror("setenv() errror");
		return;
	}
	write(STDOUT_FILENO, new_, strlen(new_));
	write(STDOUT_FILENO, "\n", 1);
}
