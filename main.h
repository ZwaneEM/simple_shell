#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUF_FLUSH -1
#define MAX_ARGU 64

extern char **environ;


/**
 * list_t - stores the data typed by the user
*/
typedef struct command
{
    char *comm;
    int len;
} list_t;

/*Hold all the command and arguments*/
typedef struct user
{
    char *comm_input;
    char path;
} data_t;

typedef struct tokenize
{
    char *command;
    char *arguments[18];
} token_t;

/* user.c */
list_t *prompt_usr(void);
char **command_tokenize(char *arg);
void sigint_handler(__attribute__((unused))int sig_num);
char *find_path(char *comm_find);

/* shell.c */
void free_mem(list_t **head);
void free_arr(char **argsv);

/*exe_command.c*/
int exe_command(char *comm, char **comm_path, char *erroNo);
void check_comm(char *comm, char **comm_path, char *erroNo);

/*buildin.c*/
int buildin_detect(list_t **input);



#endif
