#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/errno.h>

int main(int argc, char *argv[], char *envp[]) {
    pid_t pid, parent_pid, child_pid;
    int status;
    char *command = argv[1];
    argv++;
	
    pid = fork();
    printf("Current pid %d\n", pid);
    if (pid == -1){
    perror("Failed to create child process");}
    
    if (pid > 0){
    parent_pid = getpid();
    printf("Parent process executes, pid = %d\n", parent_pid);
    system("ls");
    wait(&status);
    exit(0);
    }
    else{
    child_pid = getpid();
    printf("Child process executes, pid = %d\n", child_pid);
    execvp(command, argv);
    exit(0);
    }

}
