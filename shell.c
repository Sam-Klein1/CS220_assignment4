#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>

/*
 * shell() {
 * 	display_prompt(); 
 * 	accept_command(); 
 *
 * 	pid = fork(); 
 * 	if(fork == 0) { //create a child process
 * 		exec(command); //replace the child with the command
 * 	}
 * 	wait_for_the_child(); 
 * }
 */

int main()
{
	char command[1024];
	char *args[] = {&command[0], NULL}; 

	while(1) {
		printf("hi> "); //prompt
		if(fgets(command, 1023, stdin) == NULL) break; 
		if(strcmp(command, "exit\n") == 0) break; 
		
		char *p = &command[0]; 
		while(*p != '\n') p++; 
		*p = '\0';

		if(!fork()) {
			if(execv(args[0], args) == -1) {
				printf("Exec failed!\n"); 
				perror(NULL); 
			}
			exit(0); 
		}
		else {
			//this is the parent
			wait(NULL); 
		}
	}

	return 0; 
}


