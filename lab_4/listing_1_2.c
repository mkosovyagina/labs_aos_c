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
    char message[] = "Hello, World!\nHave a nice day!!!\nWelcome to MEPHI! ;)";
    char message_child[] = "I've read all the written!\n \nI want to read more";
    int message_len = sizeof(message);
    int message_len_child = sizeof(message_child);
    char read_buffer[message_len], read_buffer_child[message_len_child];
    
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
    close(file_descriptors_pipe[0]);
    close(file_descriptors_pipe_child[1]);
    write(file_descriptors_pipe[1], message, message_len);
    
    printf("Parent process is reading from pipe\n");
    read(file_descriptors_pipe_child[0], &read_buffer_child, message_len_child);
    printf("%s\n", read_buffer_child);
    child_pid_finished = wait(&status);
    close(file_descriptors_pipe[1]);
    close(file_descriptors_pipe_child[0]);
    
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
    close(file_descriptors_pipe[1]);
    close(file_descriptors_pipe_child[0]);
    printf("Child process is readind from pipe\n");
    read(file_descriptors_pipe[0], &read_buffer, message_len);
    printf("%s\n", read_buffer);
    close(file_descriptors_pipe[0]);
    write(file_descriptors_pipe_child[1], message_child, message_len_child);
    printf("Child process is finishing\n");
    close(file_descriptors_pipe_child[0]);
    exit(0);
    }

}
