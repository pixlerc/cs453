#include "Job.h"

JobPtr createJob(const int pid, const char *line, int jobId)
{
    JobPtr newJob = (JobPtr) malloc(sizeof(Job));
    newJob->pid = pid;
    newJob->jobId = jobId;
    newJob->line = (char *) malloc(sizeof(char) * (strlen(line) + 1));
    newJob->jobState = RUNNING;
    newJob->exitStatus = NORMAL;
    strcpy(newJob->line, line);
    return newJob;
}


int compareTo(const void *obj, const void *other)
{
    JobPtr o1 = (JobPtr) obj;
    JobPtr o2 = (JobPtr) other;
    if (o1->pid == o2->pid)
	return 0;
    return o1->pid < o2->pid ? -1 : 1;
}

char *toString(const void *obj)
{
    JobPtr myobj = (JobPtr) obj;
    char *temp;
    temp =
	(char *) malloc(sizeof(char) * strlen(myobj->line) +
			1 + MAXPID_DIGITS + 4);
    sprintf(temp, "%d (%d) %s %s \"%s\"", myobj->pid, myobj->jobId,
	    myobj->jobState == RUNNING ? "Running" : "Completed",
	    myobj->exitStatus == NORMAL ? "Normal" : "Problem",
	    myobj->line);
    return temp;
}

void freeJob(const void *obj)
{
    JobPtr myobj = (JobPtr) obj;
    if (myobj == NULL)
	return;
    free(myobj->line);
    free(myobj);
}

void printJob(JobPtr job)
{
    printf("[%d] %d %s\n", job->jobId, job->pid, job->line);
}
