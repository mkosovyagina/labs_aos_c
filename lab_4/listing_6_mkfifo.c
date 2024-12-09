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
    int status, fifo_status;
    int file_descriptors_fifo;
    char read_buffer[1];
    
    fifo_status = mkfifo(FIFO_CH, S_IFIFO | 0777);
    
    if(fifo_status < 0){
    	printf("Fifo creation failed\n");}
    
    file_descriptors_fifo = open(FIFO_CH, O_WRONLY);	
    	
    if(fifo_status < 0){
    	printf("Failed to open FIFO\n");}
    close(file_descriptors_fifo);	
    //unlink(FIFO_CH);	
    //while(read(file_descriptors_pipe[0], &read_buffer, 1) > 0){
    //    write(1, &read_buffer, 1);
   // }

    return 0;
    
}
