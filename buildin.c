#include "main.h"

/**
 * buildin_detect - detects exit and env build in
 * @input: The input from user
 * Return: Nothing.
*/
int buildin_detect(list_t **input)
{
	char *comm = strdup((*input)->comm);
	int call;
	int status_ = 0;
	char *_token;
	char *testc = strdup(comm);

	_token = strtok(testc, " ");
	call = strcmp(_token, "exit");

	if (call == 0)
	{
		status_ = check_status(comm);
		free(comm);
		free(testc);
		free_mem(&(*input));
		exit(status_);
	}

	if (strcmp(_token, "unsetenv") == 0 || strcmp(_token, "setenv") == 0)
	{
		buildin_detect_2(&comm);
		free(comm);
		free(testc);
		return (1);
	}

	if (strcmp(_token, "cd") == 0)
	{
		buildin_detect_3(&comm);
		free(comm);
		free(testc);
		return (1);
	}

	free(comm);
	free(testc);
	return (0);
}

/**
 * check_status - checks to see if valid status
 * is sent to the exit buildin
 * @comm: The command to check
 * Return: The status given or zero
 */
int check_status(char *comm)
{
	char *comm_cpy, *_token;
	int val, i;
	char *program = getenv("_");
	int sig = 0;

	comm_cpy = strdup(comm);
	_token = strtok(comm_cpy, " ");

	if (_token != NULL)
	{
		_token = strtok(NULL, " ");

		if (_token != NULL)
		{
			for (i = 0; _token[i] != '\0'; i++)
			{
				if (_token[i] >= '0' && _token[i] <= '9')
				{
				}
				else
				{
					sig += 2;
					write(STDERR_FILENO, program, strlen(program));
					write(STDERR_FILENO, ": 1: exit: Invalid number: ", 27);
					write(STDERR_FILENO, _token, strlen(_token));
					putchar('\n');
					break;
				}
			}
			if (sig != 2)
			{
				val = atoi(_token);
				free(comm_cpy);
				return (val);
			}
		}
	}
	free(comm_cpy);
	return (0);
}
