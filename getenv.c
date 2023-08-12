#include "main.h"

/**
 * get_env - gets the true path to a program or file
 * @str: The command to check for
 * Return: True path to the file or command/ NULL
 */
char *get_env(char *str)
{
	char *cpath = getenv("PATH");
	char *cpath_cpy, *comm_path, *direc;
	int str_len = strlen(str);
	int direc_len;
	struct stat st_buf;

	if (cpath)
	{
		cpath_cpy = strdup(cpath);
		direc = strtok(cpath_cpy, ":");

		while (direc != NULL)
		{
			direc_len = str_len;
			direc_len += strlen(direc);
			direc_len += 2;
			comm_path = malloc(direc_len);
			strcpy(comm_path, direc);/*construction*/
			strcat(comm_path, "/");
			strcat(comm_path, str);
			strcat(comm_path, "\0");

			if (stat(comm_path, &st_buf) == 0)
			{
				free(cpath_cpy);
				return (comm_path);
			}
			else
			{
				free(comm_path);
				direc = strtok(NULL, ":");
			}
		}
		if (stat(str, &st_buf) == 0)
		{
			return (str);
		}
		return (NULL);
	}
	return (NULL);
}
