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
    int status, pipe_status;
    int file_descriptors_pipe[2];
    char read_buffer[1];
    
    pipe_status = pipe(file_descriptors_pipe);
    
    if(pipe_status < 0){
    	printf("Pipe creation failed\n");}
    
    pid = fork();
    printf("Current pid %d\n", pid);
    if (pid == -1){
    perror("Failed to create child process");}
    
    if (pid > 0){
    dup2(file_descriptors_pipe[1], 1);
    close(file_descriptors_pipe[1]);
    close(file_descriptors_pipe[0]);
    
    execlp("who", "who", NULL);
    exit(1);
    }
    else{

    dup2(file_descriptors_pipe[0], 0);
    
    close(file_descriptors_pipe[0]);
    close(file_descriptors_pipe[1]);
    
    execlp("wc", "wc", "-l", NULL);
    
    exit(1);
    }
}
