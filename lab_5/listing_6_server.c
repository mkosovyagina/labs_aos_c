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

struct message_simple {
    long type;
    char payload[100];
};

struct message_server {
    long type;
    int queue_id;
};

int main(int argc, char* argv[]) {
    int res, id_server;
    key_t key;
    
    key = ftok("/home/vboxuser/mvkosovy/labs_aos_c/lab_5/token_2.txt", 2);
    printf("%d\n", key);
    id_server = msgget(key, IPC_CREAT | 0666);
    printf("Server queue id %d\n", id_server);
    struct message_server msg_srv;
    struct message_simple msg_smpl;
    while (1) {
        memset(&msg_srv, 0, sizeof(msg_srv));
        msgrcv(id_server, &msg_srv, sizeof(msg_srv.queue_id), 0, 0);
        printf("Message from client %d\n", msg_srv.queue_id);
        
        msg_smpl.type = 7;
        strcpy((char*)&msg_smpl.payload, "Success");
        
        msgsnd(msg_srv.queue_id, &msg_smpl, sizeof(msg_smpl.payload), 0);
        printf("Sent message to client %d\n", msg_srv.queue_id);
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
