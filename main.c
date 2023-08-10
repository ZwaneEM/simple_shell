#include "simpleShell.h"

/**
* main- prompts user to enter a command
*    prompt displayed in a loop while
*    the command is being executed
*
* Return: command, or prompt again
*/

int main(int n, char **argv)
{
    char *command;
    prompt = "(Enter a command:) $ ";
    
    char *linepointer2 = NULL;
    size_t m = 0;
    char *linepointer1 = NULL;
    ssize_t numChars;
    (void)n;

    while (1)
    {
        printf("%s", command);
        numChars = getline(&linepointer1, &m, stdin);
         
        if (numChars == -1)
        {
            printf("ERROR! \n");
            return (-1);
        }

        linepointer2 = malloc(sizeof(char) * numChars);
        if (linepointer2 == NULL)
        {
            perror("ERROR: MEMORY ALLOCATION!");
            return (-1);
        }
        
        strcpy(linepointer2, linepointer1);
        const char *delimiter = " \n";
        int numOfTokens = 0;
        char *tok;
        tok = strtok(linepointer1, delimiter);

        while (tok != NULL)
        {
            numOfTokens++;
            tok = strtok(NULL, delimiter);
        }numOfTokens++;

        argv = malloc(sizeof(char *) * numOfTokens);
        int index;
        tok = strtok(linepointer1, delimiter);
        
        for (index = 0; token != NULL; index++)
        {
            argv[index] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[index], token);
            token = strtok(NULL, delimiter);
        }
        argv[index] = NULL;
        execmd(argv);

    } 
 
    free(linepointer1);
    free(linepointer2);

    return (0);
}
