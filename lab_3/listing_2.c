#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void custom_handler(int signal_num){
    printf("handler has been launched with signal %d\n", signal_num);
    printf("Finishing handler\n");	
}

int main() {
    struct sigaction signal_action, old_action;
    signal_action.sa_handler = custom_handler;
   
    signal_action.sa_flags = SA_RESETHAND | SA_NODEFER;

    printf("Waiting signal SIGINT\n");
    
    sigaction(SIGINT, &signal_action, &old_action);
    
    sleep(30);
    printf("Continue after signal was handled\n");
    sleep(30);
}

