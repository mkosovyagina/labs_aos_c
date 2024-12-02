#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <signal.h>


void custom_handler_1(int signal_num){
    printf("handler 1 has been launched with signal %d\n", signal_num);	
}

void custom_handler_2(int signal_num){
    printf("handler 2 has been launched with signal %d\n", signal_num);	
}

int main() {
    pid_t pid, parent_pid, child_pid, child_pid_finished;
    int	child_ppid, child_pgid, parent_ppid, parent_pgid;
    static struct sigaction signal_action_1, signal_action_2;
    sigset_t mask, wait_mask;
    int status, i, j;
    int N = 10;
    
    signal_action_1.sa_handler = custom_handler_1;
    sigaction(SIGUSR1, &signal_action_1, NULL);
    signal_action_1.sa_flags = 0;
    signal_action_2.sa_handler = custom_handler_2;
    signal_action_2.sa_flags = 0;
    sigaction(SIGUSR2, &signal_action_2, NULL);
    
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR2); 
    sigaddset(&mask, SIGUSR1);
    sigprocmask(SIG_BLOCK, &mask, &wait_mask);
    
    pid = fork();
    printf("Current pid %d\n", pid);
    
    
    if (pid == -1){
    perror("Failed to create child process");}
    
    if (pid > 0){
    
    //child_pid_finished = wait(&status);
    parent_pid = getpid();
    parent_ppid = getppid();
    parent_pgid = getpgid(parent_pid);
    printf("Parent process executes, pid = %d\n", parent_pid);
    printf("Parent process parent pid = %d\n", parent_ppid);
    printf("Parent process group id = %d\n", parent_pgid);
    while(N > 0){
	N--;
	sigsuspend(&wait_mask);
	kill(pid, SIGUSR2);
	     	}

    wait(NULL);
    printf("Child process %d successfully executed with code %d\n", child_pid_finished, status);
    exit(0);   
    }
    else{
    child_pid = getpid();
    child_ppid = getppid();
    child_pgid = getpgid(child_pid);
    printf("Child process executes, pid = %d\n", child_pid);
    printf("Child process parent pid = %d\n", child_ppid);
    printf("Child process group id = %d\n", child_pgid);
   
    while(N != 0){
        N--;
        kill(child_ppid, SIGUSR1);
        sigsuspend(&wait_mask);
	    	}

	exit(0);
    }	    
}

