#ifndef _SIMPLESHELL_H_
#define _SIMPLESHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

void prompt(void);
void print_str(char *strp);
void execmd(char **argv);

#endif
