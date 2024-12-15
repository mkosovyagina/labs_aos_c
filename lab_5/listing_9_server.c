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
    char payload[100];
};
int id_server, is_client, id_client;
long clients[MAX_SIZE];
int clients_count = 0;

struct message_server msg_srv;
struct message_simple msg_smpl;

void custom_handler(int signal_num){
    printf("handler has been launched with signal %d\n", signal_num);
    int j;
    for(j=0; j < clients_count; j++){
        memset(&msg_smpl, 0, sizeof(msg_smpl));
        strcpy((char*)&msg_smpl.payload, "Shutdown");
        msg_smpl.type = clients[j];
        //id_client = msgget(clients[j], 0);
        printf("Sending to client pid %lu\n", msg_smpl.type);
        msgsnd(id_client, &msg_smpl, sizeof(msg_smpl.payload), msg_smpl.type);
        sleep(5);
        
    }
        exit(0);
    }	

int is_already_client(long client_pid, long arr[]){
    int i;
    for(i=0; i < clients_count; i++){
        if(arr[i] == client_pid) return 1;
        }
    return 0; 	
	}
	
int main(int argc, char* argv[]) {
    int res;

    key_t key, key_client;
    signal(SIGINT, custom_handler);
    key = ftok(argv[0], 2);
    key_client = ftok("/home/vboxuser/mvkosovy/labs_aos_c/lab_5/listing_9_client", 1);
    printf("%d\n", key);
    printf("%d\n", key_client);
    id_server = msgget(key, IPC_CREAT | 0666);
    id_client = msgget(key_client, IPC_CREAT | 0666);
    printf("Server queue id %d\n", id_server);
    printf("Clients queue id %d\n", id_client);
    //struct message_server msg_srv;
    //struct message_simple msg_smpl;
    while (1) {
        
        memset(&msg_srv, 0, sizeof(msg_srv));
        msgrcv(id_server, &msg_srv, sizeof(msg_srv.payload), 0, 0);
        printf("Message from client with key %ld\n", msg_srv.type);
        
        is_client = is_already_client(msg_srv.type, clients);
        if (is_client == 0){
            clients[clients_count] = msg_srv.type;
            printf("Clients pid: %lu\n", clients[clients_count]);
            clients_count++;
            printf("Clients connected: %d\n", clients_count);
            
        }

        int j;
        for(j=0; j < clients_count; j++){
            //id_client = msgget(clients[j], 0);
            memset(&msg_smpl, 0, sizeof(msg_smpl));
            msg_smpl.type = clients[j];
            char str[20];
            sprintf(str, "Message from %lu", msg_srv.type);
            strcpy((char*)&msg_smpl.payload, str);
            printf("Queue id to send is %d", id_client);
            msgsnd(id_client, &msg_smpl, sizeof(msg_smpl.payload), msg_smpl.type);
            printf("Sent message to client with key %lu\n", msg_srv.type);
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
