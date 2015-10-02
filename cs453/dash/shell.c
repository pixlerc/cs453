#include "shell.h"

char *line;
char *DASH_PROMPT;
char cStatus[MAXLINE];
int status;
int command;
int ampersand;
int pipeError[2];
int jobIndex;
pid_t pid;
regex_t word;
List *jobs;

char **getTokens(char *);
char *getDirectory();
int state(int);
int exitStatus(int);
int isBackground();
Boolean startBackground(char *, char **, int);
Boolean executeCommand(char *, char **);
void removeAmpersand(char **, int);
void updateBackground(int, char *);
void freeTokens(char *, char **);
void goHome();
void updateJobs();
void removeJobs();
void displayJobs();
void printAllJobs();

/**
 * This is main.  This is the heart of mydash
 * @param argc - argument count
 * @param **argv - arguments
 * @return int - exit status
 */
int main(int argc, char **argv)
{
    DASH_PROMPT = "mydash-->";
    jobIndex = 0;
    jobs = createList(compareTo, toString, freeJob);

    command = regcomp(&word, "[\\w]*", 0);
    if (command) {
	err_ret("There was an error with your commands");
    }

    using_history();

    while ((line = readline(DASH_PROMPT))) {
	if (pipe(pipeError) < 0) {
	    err_sys("There was an error piping");
	}
	if (strlen(line) == 0) {
	    free(line);
	    printAllJobs();
	    continue;
	}

	char **tokens = getTokens(line);

	add_history(line);

	if (doWork(line, tokens)) {
	    continue;
	}

	ampersand = isBackground(tokens);

	if ((pid = fork()) < 0) {
	    err_sys("There was an error with fork");
	} else if (pid == 0) {
	    close(pipeError[0]);
	    if (ampersand >= 0) {
		startBackground(line, tokens, ampersand);
		write(pipeError[1], FAIL, strlen(FAIL) + 1);
		usleep(1000);
	    } else {
		executeCommand(line, tokens);
	    }
	    exit(EXIT_FAILURE);
	}

	if (ampersand < 0) {
	    pid = waitpid(pid, &status, 0);

	    if (!pid) {
		err_sys("There was an error with waitpid");
	    }
	} else {
	    sleep(1);

	    if (!state(pid) && exitStatus(pid)) {
		read(pipeError[0], cStatus, MAXLINE);
	    }

	    if (!strstr(cStatus, FAIL)) {
		updateBackground(pid, line);
	    }

	    int i;
	    for (i = 0; i < MAXLINE; i++) {
		cStatus[i] = 0;
	    }
	}
    }

    regfree(&word);
    exit(EXIT_SUCCESS);
}

/**
 * This will split the arguments into array indexs
 * @param *line - the arguments entered by the user
 * @eturn char ** - an array of tokens from line
 */
char **getTokens(char *line)
{
    char *next;
    const char *delim = " ";
    int count = 0;
    char **tokens;
    char *copy = (char *) malloc(strlen(line) * sizeof(char));

    strcpy(copy, line);

    tokens = (char **) malloc(MAX_ARGUMENTS * sizeof(char *));

    next = strtok(copy, delim);

    while (next) {
	tokens[count] = (char *) malloc(strlen(next) + 1);
	char *token = tokens[count++];
	strcpy(token, next);
	next = strtok(NULL, delim);
    }

    tokens[count] = (char *) 0;

    free(copy);
    return tokens;

}

/**
 * Checks to see if the command entered should be a background job or not
 * @param **tokens - the arguments entered by the user
 * @return int - the index where the apersand exists or -1 if it does not
 */
int isBackground(char **tokens)
{
    int i;
    for (i = 0; i < MAX_ARGUMENTS && tokens[i]; i++);

    i--;

    if (strstr(tokens[i], "&")) {
	return i;
    }

    if (i >= 1 && strstr(tokens[i - 1], "&")) {
	return i;
    }

    return -1;
}

/**
 * Runs the arguments passed by the user in the background
 * @param *line - the arguments entered by the user
 * @param *char ** tokens - line split into an array
 * @param ampersand - the location of ampersand in tokens
 * @return Boolean - If the function succeeded or not
 */
Boolean startBackground(char *line, char **tokens, int ampersand)
{
    removeAmpersand(tokens, ampersand);
    return executeCommand(line, tokens);
}

/**
 * This adds the background job to the list
 * @param pid - process id
 * @param *line - the arguments entered by the user
 */
void updateBackground(int pid, char *line)
{
    char *copy = (char *) malloc(strlen(line) + 1 * sizeof(char));

    strcpy(copy, line);

    Job *job = createJob(pid, copy, ++jobIndex);
    Node *node = createNode(job);
    addAtRear(jobs, node);
    printAllJobs();	
}

/**
 * Removes the ampersand from tokens
 * @param **tokens - the arguments entered by the user
 * @param ampersand - the index of the ampersand in tokens
 */
void removeAmpersand(char **tokens, int ampersand)
{
    char *token = tokens[ampersand];

    if (strlen(token) == 1) {
	tokens[ampersand] = (char *) 0;
	return;
    }

    while (*token) {
	if (*token == '&') {
	    *token = 0;
	    return;
	}

	token++;
    }
}

/**
 * Changes the directory to the users home directory
 */
void goHome()
{
    struct passwd *pwd;
    errno = 0;
    char *dir;

    pwd = getpwuid(getuid());

    if ((errno = EIO || errno == EINTR || errno == EMFILE)) {
	fprintf(stderr, "There was an error getting home");
	dir = "/";
    } else {
	dir = pwd->pw_dir;
    }

    printf("%s\n", dir);
    chdir(dir);
}

/**
 * Gets the current working directory
 * @return char* - return the current directory
 */
char *getDirectory()
{
    char *dir = (char *) malloc(MAX_DIRECTORY * sizeof(char));

    if (getcwd(dir, sizeof(dir)) != NULL) {
	return dir;
    } else {
	err_sys("There was an error getting dir");
    }

    return NULL;

}

/**
 * Executes the command
 * @param *line - the arguments entered by the user
 * @param **tokens - the line split into an array
 * @return Boolean - return the success of the function
 */
Boolean executeCommand(char *line, char **tokens)
{
    execvp(tokens[0], tokens);
    err_ret("There was an error executing");
    return FALSE;
}

/**
 * Updates each jobs current state
 */
void updateJobs()
{
    Node *node = jobs->head;

    if (node == NULL) {
	return;
    }

    do {
	Job *job = (Job *) (node->obj);
	job->job_state = state(job->pid);

	if (job->job_state == COMPLETE) {
	    job->exit_status = exitStatus(job->pid);
	}
    }
    while ((node = node->next));
}

/**
 * Gets the state of the process
 * @param pid - process id
 * @return int - returns RUNNING or COMPLETE
 */
int state(int pid)
{
    int status;
    int cPid = waitpid(pid, &status, WNOHANG);

    if (!cPid && WIFEXITED(status)) {
	return RUNNING;
    } else {
	return COMPLETE;
    }

}

/**
 * Gets the exit status of the process
 * @param pid - process id
 * @return int - returns NORMAL or PROBLEM
 */
int exitStatus(int pid)
{
    int status;
    int cPid = waitpid(pid, &status, WUNTRACED);

    if (cPid == -1 && errno == ECHILD) {
	return NORMAL;
    }

    if (!cPid && (WEXITSTATUS(status) || WIFSIGNALED(status))) {
	return PROBLEM;
    } else {
	return NORMAL;
    }

}
/**
 * Process built in commands
 * @param *line - the arguments entered by the user
 * @param **tokens - the line split into an array
 * @retun int - return 1 for success and 0 for failure
 */
int doWork(char *line, char **tokens)
{
    char *command = tokens[0];

    if (strstr(command, "cd") && tokens[1] == NULL) {
	goHome();
	return 1;
    } else if (strstr(command, "cd") && tokens[1] != NULL) {
	chdir(tokens[1]);
	return 1;
    } else if (strstr(command, "exit")) {
	freeList(jobs);
	freeTokens(line, tokens);
	kill(getpid(), SIGKILL);
    } else if (strstr(command, "jobs")) {
	printAllJobs();
	return 1;
    }
    return 0;
}

/**
 * Removes completed jobs from the list
 */
void removeJobs()
{
    Node *node = jobs->head;

    if (node == NULL) {
	return;
    }

    while (node != NULL) {
	Job *job = (Job *) (node->obj);

	if (job->job_state == COMPLETE) {
	    Node *copy = node->next;
	    freeNode(removeNode(jobs, node), freeJob);
	    node = copy;
	} else {
	    node = node->next;
	}
    }

    if (jobs->size == 0) {
	jobIndex = 0;
    }

}

/**
 * Frees the tokens and line
 * @param *line - the argumentts entered by the user
 * @param **tokens - the line split into an array
 */
void freeTokens(char *line, char **tokens)
{
    free(line);

    int i;
    for (i = 0; i < MAX_ARGUMENTS; i++) {
	free(tokens[i]);
    }

    free(tokens);
}

/**
 * Prints the list of jobs
 */
void displayJobs()
{
    if (jobs->size == 0) {
	printf("No jobs\n");
    }

    printList(jobs);

}

/**
 * Prints all of the jobs after updating their status
 */
void printAllJobs()
{
    updateJobs();
    displayJobs();
    removeJobs();
}
