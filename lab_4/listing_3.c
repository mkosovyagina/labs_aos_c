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
    int status, pipe_status, pipe_status_child;
    int file_descriptors_pipe[2], file_descriptors_pipe_child[2];
    char read_buffer[1];
    
    pipe_status = pipe(file_descriptors_pipe);
    
    
    if(pipe_status < 0){
    	printf("Pipe creation failed\n");}
    	
        pipe_status_child = pipe(file_descriptors_pipe_child);
    
    if(pipe_status_child < 0){
    	printf("Pipe creation for child failed\n");}  		
    
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
    close(file_descriptors_pipe[1]);
    close(file_descriptors_pipe_child[0]);
    
    while(read(file_descriptors_pipe[0], &read_buffer, 1) > 0){
    	write(file_descriptors_pipe_child[1], &read_buffer, 1);
    }
    
    close(file_descriptors_pipe_child[1]);
    
    child_pid_finished = wait(&status);
    printf("Paretnt process successfully read all the content\n");
    close(file_descriptors_pipe[0]);
    close(file_descriptors_pipe_child[1]);
    
    printf("Child process %d successfully executed with code %d\n and status %d", child_pid_finished, WEXITSTATUS(status), status);
    exit(0);
    }
    else{
    child_pid = getpid();
    child_ppid = getppid();
    child_pgid = getpgid(child_pid);
    printf("Child process executes, pid = %d\n", child_pid);
    printf("Child process parent pid = %d\n", child_ppid);
    printf("Child process group id = %d\n", child_pgid);
    
    close(file_descriptors_pipe[0]);
    close(file_descriptors_pipe_child[1]);
    
    while(read(0, &read_buffer, 1) > 0){
    	
        write(file_descriptors_pipe[1], &read_buffer, 1);	
        }
        
        close(file_descriptors_pipe[1]);

        //printf("%s\n",read_buffer);
    while(read(file_descriptors_pipe_child[0], &read_buffer, 1) > 0){
        write(1, &read_buffer, 1);
    }    
        
    printf("Child process is finishing\n");
    close(file_descriptors_pipe_child[0]);
    
    exit(0);
    }

}
