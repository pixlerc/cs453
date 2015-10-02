#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <common.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include "sys/stat.h"
#include "sys/types.h"
#include <regex.h>
#include "errno.h"
#include "pwd.h"
#include "wait.h"
#include "unistd.h"
#include "ourhdr.h"
#include <List.h>
#include <Node.h>
#include <Job.h>

#ifndef MYDASH_H
#define MYDASH_H

#define MAX_ARGUMENTS 2049
#define MAX_PIPE 4096
#define MAX_DIRECTORY 1024
#define FAIL "FAIL"

/**
 * Process built in commands
 * @param char* - the arguments passed by the user
 * @param char** - the arguments passed by the user split into an array
 * @return int - returns 1 for success and 0 for failure
 */
int doWork(char *, char **);

#endif				/* MYDASH_H */
