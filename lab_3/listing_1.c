#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void custom_handler(int signal_num){
    printf("handler has been launched with signal %d\n", signal_num);
    signal(SIGINT, SIG_DFL);	
}

int main() {
    printf("Waiting signal SIGINT\n");			
    signal(SIGINT, custom_handler);
    
    sleep(30);
    printf("Continue after signal was handled\n");
    sleep(30);
}

