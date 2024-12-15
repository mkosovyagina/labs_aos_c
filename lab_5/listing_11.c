#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>
#include <unistd.h>
#include <math.h>
#include <inttypes.h>
#include <limits.h>
#include <memory.h>
#include <string.h>
#include <malloc.h>
//#include <assert.h>
//#include <time.h>
//#include <pthread.h>
//#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <fcntl.h>
#include <wait.h>


struct message {
    long type;
};

void process(int queue_id, char* text) {
    int file_descriptor;
    file_descriptor = open("file.txt", O_WRONLY | O_CREAT, 0666);
    if (file_descriptor == -1) {
        perror("Failed to open file");
        exit(1);
    }
    //file_descriptor = 1;
    struct message msg;
    int i;
    for(i=0; i < 5; i++){
        msgrcv(queue_id, &msg, 0, 0, 0);
        lseek(file_descriptor, 0, SEEK_END);
        write(file_descriptor, text, strlen(text));
        msgsnd(queue_id, &msg, 0, 0);
        sleep(1);
    }
    close(file_descriptor);
}

int main(int argc, char* argv[]) {
    key_t key;
    int queue_id;
    struct message msg;
    int status;
    
    key = ftok(argv[0], 1);
    queue_id = msgget(key, IPC_CREAT | 0666);
    
    msg.type = 1;
    msgsnd(queue_id, &msg, 0, 0);
    
    pid_t res = fork();
    if (res > 0) { // parent
        process(queue_id, "Message 1\n");
        wait(&status);
        msgctl(queue_id, IPC_RMID, NULL);
        return 0;
    } else { // child
        process(queue_id, "Message 2\n");
        return 0;
    }
}

