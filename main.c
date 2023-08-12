#include "main.h"

char **arr_make(char *str);

extern char **environ;

/**
 *
 *
 */
int main(int argc, char **argv)
{

	/* declaration and initilization */
	char *prompt = "#ourshell $ ";
	char *input = NULL;
	ssize_t nchar;
	char **av = argv;
	int ac = argc;
	size_t len = 0;
	int i = 0;
	pid_t pid;

	(void)argc;


	printf("%s", prompt); /*prompt the user*/

	nchar = getline(&input, &len, stdin);
	if (nchar == -1)
		return (0);

	argv = arr_make(input);
	
	pid = fork();

	if (pid == -1)
		return (0);

	
	if (pid == 0)
	{
		exe_command(argv, av[0]);
	}
	else
	{
		wait(NULL);
	}

	return main(ac, av);

}	


/**
 * arr_make - takes user input and turn it to
 * array of words
 * @str: The string to process
 * Return: pointer to array of pointers
 */
char **arr_make(char *str)
{
	const char *delim = " \n";
	char *token = strtok(str, delim);
	char **arg = malloc(sizeof(char *) * 8);
	int i = 0;

	while (token != NULL)
	{
		arg[i] = token;
		i++;
		token = strtok(NULL, delim);
	}
	arg[i] = "/usr/";

	return (arg);
}	
