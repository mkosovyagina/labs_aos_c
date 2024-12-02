#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/errno.h>

int main() {
    pid_t pid, parent_pid, child_pid;
    int	child_ppid, child_pgid, parent_ppid, parent_pgid;
    int spgrp;
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
    pause();
    printf("Parent process was executed\n");
    exit(0);
    }
    else{
    child_pid = getpid();
    child_ppid = getppid();
    child_pgid = getpgid(child_pid);
    spgrp = setpgrp();
    printf("Child process executes, pid = %d\n", child_pid);
    printf("Child process parent pid = %d\n", child_ppid);
    printf("Child process group id = %d\n", child_pgid);
    pause();
    printf("Child process was executed\n");
    exit(0);
        }
}
