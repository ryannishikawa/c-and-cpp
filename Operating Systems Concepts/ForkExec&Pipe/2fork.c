#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        sleep(2);
        printf("Parent (pid %d): goodbye\n", (int) getpid());
    }
    return 0;
}