#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/errno.h>

#define  FILE_OPEN_FAILED -1
#define  FILE_CHILD_PROCESS_OUTPUT "child_output.txt"
#define  FILE_PARENT_PROCESS_OUTPUT "parent_output.txt"


int main(int argc, char *argv[]) {
    pid_t pid, parent_pid, child_pid;
    int	child_ppid, child_pgid, parent_ppid, parent_pgid;
    int file_descriptor_common, file_descriptor_parent, file_descriptor_child;
    int file_size, status, read_bytes;
    char common_buffer[1];
    
	    	
    file_size = lseek(file_descriptor_common, 0, SEEK_END);
    printf("%d\n", file_size);
    lseek(file_descriptor_common, 0, SEEK_SET);
    
	    	
    pid = fork();
    printf("Current pid %d\n", pid);
    if (pid == -1){
    perror("Failed to create child process");}
    
    file_descriptor_common = open(argv[1], O_RDONLY);
    
    if (file_descriptor_common == FILE_OPEN_FAILED){
	    	perror("Failed to open file: ");
	    	exit(1);}
    
    if (pid > 0){
    parent_pid = getpid();
    parent_ppid = getppid();
    parent_pgid = getpgid(parent_pid);
    printf("Parent process executes, pid = %d\n", parent_pid);
    printf("Parent process parent pid = %d\n", parent_ppid);
    printf("Parent process group id = %d\n", parent_pgid);

    file_descriptor_parent = creat(FILE_PARENT_PROCESS_OUTPUT, 0775);
    
    while((read(file_descriptor_common, &common_buffer, sizeof(common_buffer))) > 0){
    	//printf("%s", common_buffer);
	write(file_descriptor_parent, common_buffer, sizeof(common_buffer));
    }
    close(file_descriptor_parent);
    wait(&status);
    
    close(file_descriptor_common);
    
    file_descriptor_child = open(FILE_CHILD_PROCESS_OUTPUT, O_RDONLY);
    while((read(file_descriptor_child, &common_buffer, sizeof(common_buffer))) > 0){
    	printf("%s", common_buffer);
    }

    file_descriptor_parent = open(FILE_PARENT_PROCESS_OUTPUT, O_RDONLY);
    while((read(file_descriptor_parent, &common_buffer, sizeof(common_buffer))) > 0){
    	printf("%s", common_buffer);
    }
    
    close(file_descriptor_child);
    close(file_descriptor_parent);
    exit(0);
    }
    else{
    child_pid = getpid();
    child_ppid = getppid();
    child_pgid = getpgid(child_pid);
    printf("Child process executes, pid = %d\n", child_pid);
    printf("Child process parent pid = %d\n", child_ppid);
    printf("Child process group id = %d\n", child_pgid);
    file_descriptor_child = creat(FILE_CHILD_PROCESS_OUTPUT, 0755);
    while((read(file_descriptor_common, &common_buffer, sizeof(common_buffer))) > 0){
    	//printf("%s", common_buffer);
	write(file_descriptor_child, common_buffer, sizeof(common_buffer));
    }
    
    close(file_descriptor_child);
    exit(0);
        }   
    return 0;
}
