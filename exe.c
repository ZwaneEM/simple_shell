#include "main.h"

void exe_command(char **argv, char *erro)
{

//   char *command = NULL;

    if (argv){

        if (execve(argv[0], argv, NULL) == -1){
            perror(erro);
        }

    }

}
