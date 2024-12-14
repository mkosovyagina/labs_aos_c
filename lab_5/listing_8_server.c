#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <inttypes.h>
#include <limits.h>
#include <memory.h>
#include <string.h>
#include <malloc.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <signal.h>

#define MAX_SIZE 10

struct message_simple {
    long type;
    char payload[100];
};

struct message_server {
    long type;
    int queue_key;
};
int id_server, is_client;
key_t clients[MAX_SIZE];
int clients_count = 0;

struct message_server msg_srv;
struct message_simple msg_smpl;

void custom_handler(int signal_num){
    printf("handler has been launched with signal %d\n", signal_num);
    int j, id_client;
    for(j=0; j < clients_count; j++){
        memset(&msg_smpl, 0, sizeof(msg_smpl));
        strcpy((char*)&msg_smpl.payload, "Shutdown");
        msg_smpl.type = 9;
        id_client = msgget(clients[j], 0);
        printf("Sending to client %d\n", id_client);
        msgsnd(id_client, &msg_smpl, sizeof(msg_smpl.payload), 0);
        sleep(5);
        
    }
        exit(0);
    }	

int is_already_client(key_t client_key, key_t arr[]){
    int i;
    for(i=0; i < clients_count; i++){
        if(arr[i] == client_key) return 1;
        }
    return 0; 	
	}
	
int main(int argc, char* argv[]) {
    int res, id_client;

    key_t key, key_client;
    signal(SIGINT, custom_handler);
    key = ftok(argv[0], 2);
    printf("%d\n", key);
    id_server = msgget(key, IPC_CREAT | 0666);
    printf("Server queue id %d\n", id_server);
    //struct message_server msg_srv;
    //struct message_simple msg_smpl;
    while (1) {
        
        memset(&msg_srv, 0, sizeof(msg_srv));
        msgrcv(id_server, &msg_srv, sizeof(msg_srv.queue_key), 0, 0);
        printf("Message from client with key %d\n", msg_srv.queue_key);
        
        is_client = is_already_client(msg_srv.queue_key, clients);
        if (is_client == 0){
            clients[clients_count] = msg_srv.queue_key;
            clients_count++;
            printf("Clients connected: %d\n", clients_count);
        }
        id_client = msgget(msg_srv.queue_key, 0);
        int j;
        for(j=0; j < clients_count; j++){
            id_client = msgget(clients[j], 0);
            msg_smpl.type = 7;
            char str[20];
            sprintf(str, "%d", msg_srv.queue_key);
            strcpy((char*)&msg_smpl.payload, str);
        
            msgsnd(id_client, &msg_smpl, sizeof(msg_smpl.payload), 0);
            printf("Sent message to client with key %d\n", msg_srv.queue_key);
    }}
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
