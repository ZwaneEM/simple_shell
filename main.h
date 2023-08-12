#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

void exe_command(char **av, char *erro);

char **path_arr(char *str);

void final_process(char **comm, char *erroN);

char **arr_make(char *str);

char *get_env(char *str);

void print_str(char *strp);

void exe_command(char **argv, char *errorval);

void print_env(char **env);

int check_comm(char *str);

#endif
