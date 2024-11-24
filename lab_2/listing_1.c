#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define DEFAULT_VARIABLE_NAME "NEW_VARIABLE"
#define DEFAULT_VARIABLE_VALUE "123456"
extern char **environ;

int main(int argc, char *argv[], char *envp[]) {
    char *variable_name;
    char *variable_value;
    if (argv[1] != NULL) {
    	variable_name = argv[1];
    }
    else {
    	variable_name = DEFAULT_VARIABLE_NAME;
    }
    
    if (argv[1] != NULL) {
    	variable_value = argv[2];
    }
    else {
    	variable_value = DEFAULT_VARIABLE_VALUE;
    }
		
    clearenv();
    if (setenv(variable_name, variable_value, 0) != 0) {
        printf("setenv failed");
        exit(1);
    }
	printf("%s\n", getenv(variable_name));
	while(*environ != NULL){
        printf("%s\n", *environ);
	environ++;
	}
	unsetenv(variable_name);
	
	while(*environ != NULL){
        printf("%s\n", *environ);
	environ++;
	}

    return 0;
}
