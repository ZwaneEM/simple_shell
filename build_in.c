#include "main.h"

/**
 * check_comm - checks to see if the command if
 * env or exit
 * @str: strng to check if its whithin the scope
 * Return: 2 if command exit/ 3 if command env/ 1 if not
 */
int check_comm(char *str)
{

	if (str[0] == 'e')
	{
		if (str[1] == 'n')
		{
			if (str[3] == '\0' && str[2] == 'v')
			{
				return (3);
			}
			else
			{
				return (1);
			}
		}

		if (str[1] == 'x')
		{
			if (str[4] == '\0' && str[3] == 't' && str[2] == 'i')
			{
				return (2);
			}
			else
			{
				return (1);
			}
		}
	}

	return (1);
}
