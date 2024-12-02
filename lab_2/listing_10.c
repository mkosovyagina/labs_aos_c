#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/errno.h>

int main(int argc, char *argv[], char *envp[]) {
    pid_t pid, parent_pid, child_pid, child_pid_finished;
    int	child_ppid, child_pgid, parent_ppid, parent_pgid;
    int status;
    int i = 0;
    char *env[] = {"CHILD_VAR=CHILD"};
    pid = fork();
    printf("Current pid %d\n", pid);
    if (pid == -1){
    perror("Failed to create child process");}
    
    if (pid > 0){
    child_pid_finished = wait(&status);
    parent_pid = getpid();
    parent_ppid = getppid();
    parent_pgid = getpgid(parent_pid);
    printf("Parent process executes, pid = %d\n", parent_pid);
    printf("Parent process parent pid = %d\n", parent_ppid);
    printf("Parent process group id = %d\n", parent_pgid);
    setenv("PARENT", "PARENT_VALUE", 0);
    printf("Number of arguments for parent: %d\n",argc);
    printf("Arguments for parent: ");
       while(argv[i] != NULL)
            printf("%s ", argv[i++]);
            i = 0;
      printf("\nEnvironment for parent:\n");
       while(envp[i] != NULL)
                printf("%s\n", envp[i++]);
    wait(&status);            
    exit(0);
    }
    else{
    child_pid = getpid();
    child_ppid = getppid();
    child_pgid = getpgid(child_pid);
    printf("Child process executes, pid = %d\n", child_pid);
    printf("Child process parent pid = %d\n", child_ppid);
    printf("Child process group id = %d\n", child_pgid);
    printf("Number of arguments for child: %d\n",argc);
    printf("Arguments for child: ");
       while(argv[i] != NULL)
            printf("%s ", argv[i++]);
            i = 0;
      printf("\nEnvironment for child:\n");
       while(envp[i] != NULL)
                printf("%s\n", envp[i++]);
    execvpe(argv[1], "ONE", "TWO", "THREE", NULL, env);
    exit(0);
    }
   return 0;}
