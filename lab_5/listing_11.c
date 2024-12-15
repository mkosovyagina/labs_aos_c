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
    file_descriptor = open("/tmp/file.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (file_descriptor == -1) {
        perror("open");
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

//msgctl(id_client, IPC_RMID, NULL);
    /*key_t key = ftok(argv[0], 1);
    printf("%d\n", key);
    int id = msgget(key, IPC_CREAT | 0666);
    if (id == -1) {
        perror("Failed to get message queue");
        exit(EXIT_FAILURE);
    }
    printf("queue id %d\n", id);    */
    //send(id, 1, "Hello");
    //send(id, 1, "Welcome");
    //send(id, 1, "123456");
    //send(id, 2, "Hello!!!");
    //send(id, 3, "Blablabla");

/*
    struct message_simple msg;
    /for (int i = 0; i < 3; i++) {   
        memset(&msg, 0, sizeof(msg));
        res = msgrcv(id, &msg, msg_size, 0, MSG_NOERROR | IPC_NOWAIT);
        if (res == -1 && errno == ENOMSG) {
            printf("No messages\n");
            exit(EXIT_FAILURE);
        } else if (res == -1) {
            perror("Something went wrong\n");
            exit(EXIT_FAILURE);
        }
        printf("Message type %ld\n", msg.type);
        printf("Message text %s\n", msg.payload);
    }
*/    
