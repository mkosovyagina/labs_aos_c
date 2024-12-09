#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

#define  FILE_OPEN_FAILED -1
#define  FILE_OUTPUT "output.txt"


int main(int argc, char *argv[]) {
    pid_t pid, parent_pid, child_pid;
    int	child_ppid, child_pgid, parent_ppid, parent_pgid;
    int file_descriptor_parent, file_descriptor_child;
    int file_size, status, read_bytes, written_bytes;
    char common_buffer[1];
    char text[] = "A mean is a quantity representing the center of a collection of numbers and is intermediate to the extreme values of the set of numbers.\n";
	    	
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
    
    
    
    file_descriptor_parent = open(FILE_OUTPUT, O_WRONLY | O_CREAT, 0775);
    
    struct flock file_lock;
    
    file_lock.l_type = F_WRLCK;
    file_lock.l_whence = SEEK_SET;
    file_lock.l_start = 0;
    file_lock.l_len = 0;
    fcntl(file_descriptor_parent, F_SETLKW, &file_lock);
    
    for (int i = 0; i < 5; i++){
        //strcpy((char*)&common_buffer[1], text[i]);
        written_bytes = write(file_descriptor_parent, text, sizeof(text));
        //printf("%c\n", text[i]);
	if (written_bytes == -1){
	    perror("failed to write");
	}
    }
        file_lock.l_type = F_UNLCK;
        close(file_descriptor_parent);
        wait(&status);
        exit(0);
    }
    else{
    child_pid = getpid();
    child_ppid = getppid();
    child_pgid = getpgid(child_pid);
    printf("Child process executes, pid = %d\n", child_pid);
    printf("Child process parent pid = %d\n", child_ppid);
    printf("Child is reading\n");
    sleep(2);
    file_descriptor_child = open(FILE_OUTPUT, O_RDONLY);
    while((read_bytes  = read(file_descriptor_child, &common_buffer, sizeof(common_buffer))) > 0){
    	//printf("%s", common_buffer);
	write(1, common_buffer, sizeof(common_buffer));
    }
    if(read_bytes == -1){
    	perror("Failed to read from file by child\n");}
    
    close(file_descriptor_child);
    exit(0);
        }   
    return 0;
}
