/*
Linden Beemer
CPSC 346
Project 2 - History Shell
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE        80
#define MAX_COMMANDS    9

char history[MAX_COMMANDS][MAX_LINE];
char display_history[MAX_COMMANDS][MAX_LINE];

int command_count = 0;

/**
 * Add the most recent command to the history.
 */
void addToHistory(char inputBuffer[]) {
    // update array"history": add the command to history, strcpy(str1,str2);
    if(command_count < MAX_COMMANDS) {
        strcpy(history[command_count], inputBuffer);
    }
    // update array"display_history": remove characters like '\n', '\0' in order to display nicely
    for(int i = 0; i < command_count; ++i) {
        for(int j = 0; j < command_count; ++j) {
            if(history[i][j] != '\n' && history[i][j] != '\0') {
                display_history[i][j] = history[i][j];
            }
        }
    }
    ++command_count;

    return;
}

/** 
 * The setup function below will not return any value, but it will just: read
 * in the next command line; separate it into distinct arguments (using blanks as
 * delimiters), and set the args array entries to point to the beginning of what
 * will become null-terminated, C-style strings. 
 */

int setup(char inputBuffer[], char *args[], int *background) {
    int length,		/* # of characters in the command line */
	i,				/* loop index for accessing inputBuffer array */
	command_number;	/* index of requested command number */

	//define your local varialbes here;
	int firstArg = 0;
    int historyNum;
    int numChars = 0;
	
    /* read what the user enters on the command line */

    // read input
    do {
        printf("osh>");
        fflush(stdout);
        length = read(STDIN_FILENO, inputBuffer, MAX_LINE);
    } while(inputBuffer[0] == '\n'); /* swallow newline characters */

    if(length == 0)
        exit(0);        /* ^d was entered, end of user command stream */

    if(length < 0) {
        perror("error reading the command");
        exit(-1);           /* terminate with error code of -1 */
    }

    /**
	 * Check if they are using history
	 */
	
	// fill in your code here Part II, if the user input is to repeat some history commands
    if(inputBuffer[0] == '!') {
        if(command_count == 0) {
            printf("no previous commands\n");
            return 1;
        } else {
            for(int i = 0; i < MAX_LINE; ++i) {
                ++numChars;
            }
            if(inputBuffer[1] == '!') {
                inputBuffer = history[command_count - 1];
                length = numChars;
            }
            if(isdigit(inputBuffer[1])) {
                historyNum = inputBuffer[1] - 48;
                //printf("%d\n", historyNum);
                if(historyNum > 0 && historyNum <= command_count) {
                    inputBuffer = history[historyNum - 1];
                    length = numChars;
                } else {
                    printf("No such command in history\n");
                    return 1;
                }
            }
        }
        //printf("%s", inputBuffer);
    }
    strcpy(&inputBuffer[length], "\0");
    addToHistory(inputBuffer);

    /**
	 * Add the command to the history
	 */
	 // fill in your code here Part II, add the following line for PartII
    int argIndex = 0;
    for(i = 0; i < length; ++i) {
        /* examine every character in the inputBuffer */
        switch(inputBuffer[i]) {
            case ' ': 
                inputBuffer[i] = *"\0";
                firstArg = 0;
                break;
            case '\t': /* argument separators */
                inputBuffer[i] = *"\0";
                firstArg = 0;
                break;
            case '\n': /* should be the final char examined */
                args[++argIndex] = NULL;
                inputBuffer[i] = *"\0";
                firstArg = 0;
                break;
                /* no more arguments to this command */	
            default: /* some other character */
                if(inputBuffer[i] == '&') {
                    *background = 1;
                    inputBuffer[i] = '\0';
                } else if(firstArg == 0) {
                    args[argIndex] = &inputBuffer[i];
                    ++argIndex;
                    firstArg = 1;
                }
                break;
        } /* end of switch */
    } /* end of for */

    /**
	 * Here you finish parsing the input. 
	 * There is one more thing to assure. If we get '&', make sure you don't enter it in the args array
	 */
    if(*background == 1) {
        args[MAX_COMMANDS] = NULL;
    }

    return 1;
}

int main(void) {
    char inputBuffer[MAX_LINE]; 	/* buffer to hold the command entered */
	int background;             	/* equals 1 if a command is followed by '&' */
	char *args[MAX_LINE/2 + 1];	    /* command line (of 80) has max of 40 arguments */
	pid_t child;            		/* process id of the child process */
	
	//define your local variables here, at the beginning of your program. 

	int shouldrun = 1;
    pid_t pid;

    while(shouldrun) {              /* Program terminates normally inside setup */
        background = 0;
        shouldrun = setup(inputBuffer, args, &background);  /* get next command */

        // fill in your code here Part I
		/* if the user typed in "exit", the shell program will return (or terminate). 
		* Call strncmp(str1,str1,count). The function call will return 0 if str1 == str2.
		* "count" is the number of characters we use to compare.    
		*/

        if(strncmp("exit", args[0], 4) == 0) {
            shouldrun = 0;
            return 0;
        }

        // fill in your code here Part II
		/* if the user typed in "history", the shell program will display the history commands. 
		* you will use "printf" to print the display_history
		* after you display all the array, this command is done. 
		* Your program should go to read again, which means calling the "setup" function.  
		*/
        int isHistory = strncmp("history", args[0], 7);

        if(isHistory == 0) {
            for(int i = 0; i < command_count - 1; ++i) {
                printf("%s", display_history[i]);
                printf("\n");
            }
            shouldrun = setup(inputBuffer, args, &background);
        } 
        
        if(shouldrun) {
            pid = fork();
            if(pid < 0) {
                printf("error\n");
                exit(0);
            } else if(pid == 0) { // child process
                execvp(args[0], args);
            } else {
                if(background == 0) {
                    waitpid(pid, NULL, 0);
                }
            }
        }
    } 

    return 0;
}