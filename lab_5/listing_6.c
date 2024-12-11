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

int main_server(int argc, char* argv[]) {
    int res, id_server;
    key_t key;
    
    key = ftok("/tmp/marina_lab_6", 2);
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

// client
int main_client(int argc, char* argv[]) {
    struct message_server msg_request;
    struct message_simple msg_answer;
    int id_client, id_server;  

    key_t key;
    id_client = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (id_client == -1) {
        perror("Client msgget\n");
        exit(1);
    }
    printf("Client id: %d\n", id_client);
    
    key = ftok("/tmp/marina_lab_6", 2);
    id_server = msgget(key, 0);
    printf("Server id: %d\n", id_server);
    
    msg_request.type = 2;
    msg_request.queue_id = id_client;
    
    for(int i = 0; i < 5; i++) {
        msgsnd(id_server, &msg_request, sizeof(msg_request.queue_id), 0);
        printf("Client sent a request\n");
        memset(&msg_answer, 0, sizeof(msg_answer));
        msgrcv(id_client, &msg_answer, sizeof(msg_answer.payload), 0, 0);
        printf("Answer for client id %d: %s\n", id_client, msg_answer.payload);
    }
    msgctl(id_client, IPC_RMID, NULL);
    return 0;
}

int main() {
    //msgctl(50, IPC_RMID, NULL);
    pid_t res = fork();
    if (res > 0) { // server
        return main_server(0, NULL);
    } else { // child
        usleep(100 * 1000); 
        pid_t res2 = fork();
        if (res2 > 0) { // child 1
            return main_client(0, NULL);
        } else { // child 2
            return main_client(0, NULL);
        }
    }
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
