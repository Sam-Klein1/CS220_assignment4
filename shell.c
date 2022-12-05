#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

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
	pid_t pid;

	while(1) {
		printf("> "); //prompt
		if(fgets(command, 1023, stdin) == NULL) break; 
		if(strcmp(command, "exit\n") == 0) break; 
		
		// Remove newline character at end 
		command[strcspn(command, "\n")] = '\0';

		// Split command into command and arguments using strtok (a string tokenizer)
		// found https://www.tutorialspoint.com/c_standard_library/c_function_strtok.htm
    	char *command_name = strtok(command, " ");
		char *args[1024]; 
    	int num_args = 0;
    	while (command_name != NULL) {

      		args[num_args] = command_name;
      		num_args++;
      		command_name = strtok(NULL, " ");
   		}

		//if we get here, there is only the command to execute with no arguments
		if (num_args == 1){
			
			args[num_args] = NULL;
			if(!fork()) {
			if(execvp(args[0], args) == -1) {
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
		else{
		//if we get here, execute command with arguments as normal
			num_args++;
			args[num_args] = NULL;

		if(!fork()) {
			if(execvp(args[0], args) == -1) {
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
	}
	return 0; 
}