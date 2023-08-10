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

    /* declaring void variables */
    (void)n;

    /* Create a loop for the shell's prompt */
    while (1)
    {
        printf("%s", prompt);
        numChars = getline(&linepointer1, &m, stdin);
        
        /* check if the getline function failed or reached EOF or user use CTRL + D */ 
        if (numChars == -1)
        {
            printf("ERROR! \n");
            return (-1);
        }

        /* allocate space for a copy of the linepointer1 */
        linepointer2 = malloc(sizeof(char) * numChars);
        if (linepointer2 == NULL)
        {
            perror("ERROR: MEMORY ALLOCATION!");
            return (-1);
        }
        
        /* copy linepointer1 to linepointer2 */
        strcpy(linepointer2, linepointer1);

        
        /* calculate the total number of tokens */
        const char *delimiter = " \n";
        int numOfTokens = 0;
        char *token;
        token = strtok(linepointer1, delimiter);

        while (token != NULL)
        {
            numOfTokens++;
            token = strtok(NULL, delimiter);
        }numOfTokens++;

        
        /* Allocate space to hold the array of strings */
        argv = malloc(sizeof(char *) * numOfTokens);

        /* Store each token in the argv array */
        int index;
        token = strtok(linepointer1, delimiter);
        
        for (index = 0; token != NULL; index++)
        {
            argv[index] = malloc(sizeof(char) * strlen(token));
            strcpy(argv[index], token);
            token = strtok(NULL, delimiter);
        }argv[index] = NULL;

        /* execute the command */
        execmd(argv);

    } 

    /* free up allocated memory */ 
    free(linepointer1);
    free(linepointer2);

    return (0);
}
