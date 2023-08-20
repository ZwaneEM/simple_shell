#include "main.h"

/**
 * get_env - gets the path of the command inputed
 * @str: Pointer to the command inputed
 * Return: The full path to the file or program
 */
char *get_env(char *str)
{

	char *path_enviro = getenv("PATH");
	char *pathdup;
	char *direx;
	char true_path[1000];

	if (path_enviro == NULL)
		return (NULL);

	pathdup = strdup(path_enviro);
	direx = strtok(pathdup, ":");

	while (direx != NULL)
	{
		strcpy(true_path, direx);
		strcat(true_path, "/");
		strcat(true_path, str);
		strcat(true_path, "\0");

		if (access(true_path, X_OK) == 0)
		{
			free(pathdup);

			return (strdup(true_path));
		}

		direx = strtok(NULL, ":");
	}

	free(pathdup);
	return (NULL);
}
