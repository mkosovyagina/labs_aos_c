#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <signal.h>
#include <string.h>

#define FIFO_CH "fifo_channel"

int main(int argc, char* argv[]) {
    pid_t pid, parent_pid, child_pid, child_pid_finished;
    int	n;
    int status, fifo_status;
    int file_descriptors_fifo;
    char read_buffer[1];
    char text[512];
    
    strcpy((char*)&text, "Hello!!!! Have a nice day!\n");
    
    file_descriptors_fifo = open(FIFO_CH, O_WRONLY | O_NDELAY);		
    if(file_descriptors_fifo < 0){
    	printf("Failed to open FIFO\n");
    	perror("Access denired");
    	}
    printf("Writing to FIFO\n");	
    n = write(file_descriptors_fifo, text, sizeof(text));
    if(n<0){
    	perror("");
    }
    sleep(15);
    printf("Closing descriptor writer\n");	
    close(file_descriptors_fifo);
    	
    //unlink(FIFO_CH);	
    //while(read(file_descriptors_pipe[0], &read_buffer, 1) > 0){
    //    write(1, &read_buffer, 1);
   // }

    exit(0);
    
}
