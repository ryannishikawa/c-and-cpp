#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    printf("Start PID %d\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "Error: call to fork() failed.\n"); 
        exit(1);
    } else if (rc == 0) {
        printf("Child (pid %d): hello\n", (int) getpid());
    } else {
        int letswait = wait(NULL);
        if (letswait == -1) {
            fprintf(stderr, "Error: wait() fail.\n"); 
            exit(1);
        }
        printf("wait returned %d\n", letswait);
        printf("Parent (pid %d): goodbye\n", (int) getpid());
    }
    return 0;
}