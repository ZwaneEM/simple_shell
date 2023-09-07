#include "main.h"

/**
 * buildin_detect - detects exit and env build in
 * @input: The input from user
 * Return: Nothing
*/
int buildin_detect(list_t **input)
{
	char *comm = strdup((*input)->comm);
	int call, i;

	for (i = 0; comm[i] != '\n'; i++)
		;
	comm[i] = '\0';

	call = strcmp(comm, "exit");

	if (call == 0)
	{
		free(comm);
		free_mem(&(*input));
		return (1);
	}

	free(comm);

	return (0);
}
