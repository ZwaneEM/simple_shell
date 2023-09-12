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

#define BUFFER_FLUSH -1
#define MAX_ARGU 64
#define MAX_READ 1000

extern char **environ;


/**
 * struct command - stores the data typed by the user
 * @comm: the command the user inputs
 * @len: the length of the command
*/
typedef struct command
{
	char *comm;
	int len;
} list_t;

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
int check_comm(char *comm, char **comm_path, char *erroNo);

/*buildin.c*/
int buildin_detect(list_t **input);
void exit_func(int status_);
int check_status(char *comm);

/*custom.c*/
int _strcmp(char *cmp1, char *test);

/*get_line.c*/
ssize_t _get_line(char **line);
void non_interactive(char **comm);
char **non_inttokenize(char *arg);

/*buildin2.c*/
void buildin_detect_2(char **comm);

#endif
