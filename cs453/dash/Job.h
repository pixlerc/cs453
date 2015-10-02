#ifndef __JOB_H
#define __JOB_H

#include <stdio.h>
#include <stdlib.h>
#include "common.h"

#define MAXPID_DIGITS 20
//exit status
#define RUNNING 1
#define COMPLETE 0
//job state
#define PROBLEM 1
#define NORMAL 0

typedef struct job Job;
typedef struct job *JobPtr;

struct job {
    int pid;
    int jobId;
    char *line;
    int exitStatus;
    int jobState;
};

/**
 * Creates a new job
 * @param const int - process id
 * @param const char* - the arguments passed by the user
 * @param const int - the new jobs id
 * @return JobPtr - returns the newley created job
 */
JobPtr createJob(const int, const char *, const int);

/**
 * Prints a string representation of the job
 * @param const void * - the job to represent
 * @return char* - returns the string representatin of the job
 */
char *toString(const void *);

/**
 * Frees the job
 * @param const void* - the job to free
 */
void freeJob(const void *);

/**
 * Compres two jobs
 * @param const void* - the first job to compare
 * @param const void* - the second job to compare
 * @return int - returns 0 for equal, 1 for the first is greater, -1 for the second is greater
 */
int compareTo(const void *, const void *);

/**
 * Prints the job
 * @param JobPtr - the job to print
 */
void printJob(JobPtr);

#endif				/* __JOB_H */
