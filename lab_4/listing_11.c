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
    char common_buffer[16];
    struct flock wlock,rlock;
	    	
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
    
    rlock.l_type = F_RDLCK;
    rlock.l_whence = SEEK_CUR;
    rlock.l_start = 0;
    rlock.l_len = 0;
				
    wlock.l_type = F_WRLCK;
    wlock.l_whence = SEEK_CUR;
    wlock.l_start = 0;
    wlock.l_len = 0;
    
         //fcntl(0, F_SETLK, &rlock);
	 //fcntl(1, F_SETLK, &wlock);
    
    while(1) {
         rlock.l_type = F_RDLCK;
         wlock.l_type = F_WRLCK;
         fcntl(0, F_SETLK, &rlock);
	 fcntl(1, F_SETLK, &wlock);
         
         read_bytes = read(0, common_buffer, sizeof(common_buffer));
         
         if(read_bytes == -1){
    	     perror("Failed to read from input by parent\n");
    	     continue;
    	   }
	 write(1, "PARENT\n", 7);
	 write(1, common_buffer, read_bytes);
	 rlock.l_type = F_UNLCK;
	 wlock.l_type = F_UNLCK;
	 fcntl(0, F_SETLK, &rlock);
	 fcntl(1, F_SETLK, &wlock);
	}
		
	//wait(&status);
        exit(0);
    

    }
    else{
    child_pid = getpid();
    child_ppid = getppid();
    child_pgid = getpgid(child_pid);
    printf("Child process executes, pid = %d\n", child_pid);
    printf("Child process parent pid = %d\n", child_ppid);
    
    rlock.l_type = F_RDLCK;
    rlock.l_whence = SEEK_CUR;
    rlock.l_start = 0;
    rlock.l_len = 0;
				
    wlock.l_type = F_WRLCK;
    wlock.l_whence = SEEK_CUR;
    wlock.l_start = 0;
    wlock.l_len = 0;
    
    //fcntl(0, F_SETLKW, &rlock);
    //fcntl(1, F_SETLKW, &wlock);
    

    while(1) {
         rlock.l_type = F_RDLCK;
         wlock.l_type = F_WRLCK;
         fcntl(0, F_SETLK, &rlock);
	 fcntl(1, F_SETLK, &wlock);
        read_bytes = read(0, common_buffer, sizeof(common_buffer));//sleep(1);
        
        if(read_bytes == -1){
    	perror("Failed to read from input by child\n");
    	continue;
    	}
        write(1, "CHILD\n", 6);
	write(1, common_buffer, read_bytes);
	
	rlock.l_type = F_UNLCK;
	wlock.l_type = F_UNLCK;
	fcntl(0, F_SETLK, &rlock);
	fcntl(1, F_SETLK, &wlock);
	}
	
    exit(0);
        }   
    return 0;
}
