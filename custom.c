#include "main.h"

/**
 * _strcmp - compares two strings together
 * @cmp1: The first string to compare
 * @test: The second string to compare
 * Return: -1 when strings dont match/ 0 on match
 */
int _strcmp(char *cmp1, char *test)
{
	int i;

	for (i = 0; cmp1[i] != '\0'; i++)
	{
		if (cmp1[i] == test[i])
			return (0);
	}

	return (-1);
}
