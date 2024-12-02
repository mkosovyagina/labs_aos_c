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
    sigset_t mask, old_mask;
    sigfillset(&mask);
    sigdelset(&mask, SIGUSR2);
    sigdelset(&mask, SIGTSTP);
    sigaction(SIGINT, &signal_action, &old_action);
    sigaction(SIGUSR2, &signal_action, &old_action);
    sigaction(SIGTSTP,&signal_action, &old_action);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    printf("Waiting for unblocked signal SIGTSTP\n");
    sleep(30);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    printf("Continue after signal was handled\n");
    sleep(30);
}

