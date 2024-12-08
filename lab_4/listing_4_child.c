#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/errno.h>
#include <signal.h>


int main(int argc, char *argv[], char *envp[]) {
    pid_t pid, parent_pid, child_pid, child_pid_finished;
    int	child_ppid, child_pgid, parent_ppid, parent_pgid;
    int status, pipe_status;
    char read_buffer[1];
      
    while(read(0, &read_buffer, 1) > 0){
        write(1, &read_buffer, 1);
    }
    
    printf("End of input reached\n");

}
