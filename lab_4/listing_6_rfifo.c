#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <signal.h>

#define FIFO_CH "fifo_channel"

int main(int argc, char* argv[]) {
    pid_t pid, parent_pid, child_pid, child_pid_finished;
    int	child_ppid, child_pgid, parent_ppid, parent_pgid;
    int status, fifo_status, n;
    int file_descriptors_fifo;
    char read_buffer[512];
    
    file_descriptors_fifo = open(FIFO_CH, O_RDONLY | O_NDELAY);	
    	
    if(file_descriptors_fifo < 0){
    	printf("Failed to open FIFO\n");
    	exit(1);
    	}
    sleep(10);		
    printf("Reading from FIFO\n");
    n = read(file_descriptors_fifo, &read_buffer, 512);
    write(1, read_buffer, 512);
    //unlink(FIFO_CH);	
    //while(read(file_descriptors_pipe[0], &read_buffer, 1) > 0){
    //    write(1, &read_buffer, 1);
   // }
    printf("Closing descriptor\n");	
    close(file_descriptors_fifo);	
    exit(0);
    
}
