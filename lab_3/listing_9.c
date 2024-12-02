#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <signal.h>

int N = 100;

void custom_handler(int signal_num){
    printf("handler has been launched with signal %d\n", signal_num);	
}

int main() {
    pid_t pid, parent_pid, child_pid, child_pid_finished;
    int	child_ppid, child_pgid, parent_ppid, parent_pgid;
    int status, i, j;
    
    pid = fork();
    printf("Current pid %d\n", pid);
    if (pid == -1){
    perror("Failed to create child process");}
    
    if (pid > 0){
    sleep(1);
    //alarm(2);
    child_pid_finished = wait(&status);
    parent_pid = getpid();
    parent_ppid = getppid();
    parent_pgid = getpgid(parent_pid);
    printf("Parent process executes, pid = %d\n", parent_pid);
    printf("Parent process parent pid = %d\n", parent_ppid);
    printf("Parent process group id = %d\n", parent_pgid);
    
    printf("Child process %d successfully executed with code %d\n", child_pid_finished, status);
    }
    else{
    alarm(6);
    child_pid = getpid();
    child_ppid = getppid();
    child_pgid = getpgid(child_pid);
    printf("Child process executes, pid = %d\n", child_pid);
    printf("Child process parent pid = %d\n", child_ppid);
    printf("Child process group id = %d\n", child_pgid);
    for(i=0; i < N; i++){
        printf("Outer loop iteration number: i =  %d\n", i);
                for(j=0; j < 100; j++){
                        usleep(1000);}
            }    
    printf("Child process is finishing\n");
    exit(5);
    }

}

