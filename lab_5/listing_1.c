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

int main() {
    int res;
    
    int id = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (id == -1) {
        perror("Failed to create message queue");
        exit(EXIT_FAILURE);
    }
    printf("queue id %d\n", id);
  
    struct message_simple msg;
    msg.type = 2;
    strcpy((char*)&msg.payload, "Hello!");

    do {  
        res = msgsnd(id, &msg, sizeof(msg), 0);
        if (res == -1) {
            if (errno == EINTR) continue;
            perror("Failed to send message");
            msgctl(id, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }   
    } while (res == -1);
    
    printf("sent\n");
    
    msg.type = 45;
    strcpy((char*)&msg.payload, "Welcome!");
    
    do {
        res = msgsnd(id, &msg, sizeof(msg), IPC_NOWAIT);
        if (res == -1) {
            if (errno == EINTR) continue;
            perror("Failed to send message");
            msgctl(id, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }
    } while (res == -1);
    
    printf("sent\n");
    
    msg.type = 966789;
    strcpy((char*)&msg.payload, "&&&&&7777777777777777777444444!");
    
    do {
        res = msgsnd(id, &msg, sizeof(msg), IPC_NOWAIT);
        if (res == -1) {
            if (errno == EINTR) continue;
            perror("Failed to send message");
            msgctl(id, IPC_RMID, NULL);
            exit(EXIT_FAILURE);
        }
    } while (res == -1);
    
    printf("sent\n");
    
    struct msqid_ds stat;
        
    res = msgctl(id, IPC_STAT, &stat);
    if (res == -1) {
        perror("Failed to get statistics");
        msgctl(id, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }
    printf("msg_cbytes %lu\n", stat.msg_cbytes);
    printf("msg_qnum %lu\n", stat.msg_qnum);
    printf("msg_qbytes %lu\n", stat.msg_qbytes);
    
    res = msgctl(id, IPC_RMID, NULL);
    if (res == -1) {
        perror("Failed to remove queue");
        exit(EXIT_FAILURE);
    }
    return 0;
}
