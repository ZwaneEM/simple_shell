#include "main.h"

/**
 * buildin_detect - detects exit and env build in
 * @comm: The input from user
 * Return: Nothing
*/
int buildin_detect(list_t **input)
{
    int sum_char = 0;
    int i, s;
    int status_v = 0;
    char *comm = strdup((*input)->comm);
    
    for (i = 0; comm[i] != '\0'; i++)
    {
        sum_char += comm[i];
    }
    free(comm);
    
    /* checks for env buildin */
    if (sum_char == 339)
    {
        for (i = 0; environ[i] != NULL; i++)
            printf("%s\n", environ[i]);
    }
    /* checks for exit buildin */
    if (sum_char == 452)
    {
        free_mem(&(*input));
        return (1);
    }    

    return (0);
}