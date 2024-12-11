#include <stdio.h>
#include <stdlib.h>
//#include <stdint.h>
//#include <unistd.h>
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

struct message_simple {
    long type;
    char payload[100];
};

void send(int id, int type, char* text) {
    int res;
    struct message_simple msg;
    msg.type = type;
    strcpy((char*)&msg.payload, text);
    do {  
        res = msgsnd(id, &msg, sizeof(msg.payload), 0);
        if (res == -1) {
            if (errno == EINTR) continue;
            perror("Failed to send message");
            msgctl(id, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }   
    } while (res == -1);
    printf("sent\n");    
}

int main(int argc, char* argv[]) {
    int res;
    
    int id = atoi(argv[1]);
    long type = atoi(argv[2]);
    
    printf("Requested message queue id %d\n", id);
    printf("Requested message queue type %ld\n", type);
  
    struct message_simple msg;
    for (int i = 0; i < 3; i++) {   
        res = msgrcv(id, &msg, sizeof(msg.payload), type, MSG_NOERROR | IPC_NOWAIT);
        if (res == -1 && errno == ENOMSG) {
            printf("No messages with type %d\n", type);
            exit(EXIT_FAILURE);
        } else if (res == -1) {
            perror("Something went wrong\n");
            exit(EXIT_FAILURE);
        }
        printf("Message type %ld\n", msg.type);
        printf("Message text %s\n", msg.payload);
    }
    
    return 0;
}


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
