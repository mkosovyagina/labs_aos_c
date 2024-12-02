#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <signal.h>

int main() {
    pid_t pid, parent_pid, child_pid, child_pid_finished;
    int	child_ppid, child_pgid, parent_ppid, parent_pgid;
    int status;
    
    struct sigaction signal_action, old_action;
    signal_action.sa_handler = SIG_IGN;

    printf("Waiting for child executing process\n");
    
    sigaction(SIGCHLD, &signal_action, &old_action);
    
    pid = fork();
    printf("Current pid %d\n", pid);
    if (pid == -1){
    perror("Failed to create child process");}
    
    if (pid > 0){
    parent_pid = getpid();
    parent_ppid = getppid();
    parent_pgid = getpgid(parent_pid);
    printf("Parent process executes, pid = %d\n", parent_pid);
    printf("Parent process parent pid = %d\n", parent_ppid);
    printf("Parent process group id = %d\n", parent_pgid);
    sleep(30);
    if ( WIFEXITED(status) ) // returns true if the child terminated normally
        { 
        	int exit_status = WEXITSTATUS(status);         
        	printf("Exit status of the child %d was %d\n", pid, exit_status); 
        }
   
    }
    else{
    child_pid = getpid();
    child_ppid = getppid();
    child_pgid = getpgid(child_pid);
    printf("Child process executes, pid = %d\n", child_pid);
    printf("Child process parent pid = %d\n", child_ppid);
    printf("Child process group id = %d\n", child_pgid);
    
    sleep(20);
    printf("Child process is finishing\n");
    //exit(0);
    }

}

