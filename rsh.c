#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

#define N 12

extern char **environ;

char *allowed[N] = {"cp","touch","mkdir","ls","pwd","cat","grep","chmod","diff","cd","exit","help"};

int isAllowed(const char*cmd) {
	// return 1 if cmd is one of the allowed commands
	// return 0 otherwise
    for (int s=0; s < N; s++){
		if (strcmp(allowed[s],cmd) == 0){
			return 1;
		}
    }
	return 0;
}

int main() {

    // TODO
    // Add variables as needed

    char line[256];

    while (1) {

	fprintf(stderr,"rsh>");

	if (fgets(line,256,stdin)==NULL) continue;

	if (strcmp(line,"\n")==0) continue;

	line[strlen(line)-1]='\0';

	// TODO
	// Add code to spawn processes for the first 9 commands
	// And add code to execute cd, exit, help commands
	// Use the example provided in myspawn.c
        pid_t pid;
        int status;
        posix_spawnattr_t attr;

        char *argv[64];
        int argc = 0;

        char *token = strtok(line, " ");
        while (token != NULL && argc < 63) {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;


        // Check if the command is invalid
        if (isAllowed(argv[0]) == 0){
            printf("NOT ALLOWED!\n");
        } else if(strcmp(argv[0],"cd") != 0) {
            if(argc >2){
                printf("-rsh: cd: too many arguments");
            } else {
                chdir(argv[1]);
            }
        } else if(strcmp(argv[0],"help") == 0) {
            printf("The allowed commands are:\n");
            for (int i = 0; i < N; i++) {
                printf("%d: ", i);
                printf("%s\n", allowed[i]);
            }
        }




    }
    return 0;
}
