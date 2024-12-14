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
    key_t  queue_key;
};


// client
int main(int argc, char* argv[]) {
    struct message_server msg_request;
    struct message_simple msg_answer;
    int id_client, id_server;  

    key_t key, key_server;
    key = ftok(argv[0], atoi(argv[1]));
    id_client = msgget(key, IPC_CREAT | 0777);
    if (id_client == -1) {
        perror("Client msgget\n");
        exit(1);
    }
    printf("Client id: %d\n", id_client);
    
    key_server = ftok("/home/vboxuser/mvkosovy/labs_aos_c/lab_5/listing_8_server", 2);
    printf("%d\n", key);
    printf("%d\n", key_server);
    id_server = msgget(key_server, 0);
    if (id_server == -1) {
        perror("Client failed connect to server\n");
        exit(1);
    }
    printf("Server id: %d\n", id_server);
    
    msg_request.type = atoi(argv[1]);
    msg_request.queue_key = key;
    
    for(int i = 0; i < 100; i++) {
        msgsnd(id_server, &msg_request, sizeof(msg_request.queue_key), 0);
        printf("Client sent a request\n");
        memset(&msg_answer, 0, sizeof(msg_answer));
        msgrcv(id_client, &msg_answer, sizeof(msg_answer.payload), 0, 0);
        
        printf("Answer for client id %d: %s\n", id_client, msg_answer.payload);
        sleep(1);
        if(strcmp(msg_answer.payload,"Shutdown") == 0){
            //printf("Answer for client id %d: %s\n", id_client, msg_answer.payload);
            printf("The server was shut down\n");
            msgctl(id_client, IPC_RMID, NULL);
            exit(0);	
        }
    }
    printf("Deleting client queue\n");
    msgctl(id_client, IPC_RMID, NULL);
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
