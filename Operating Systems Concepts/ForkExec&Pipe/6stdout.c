#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char* argv[]) { 
    int rc = fork();
    if (rc < 0) { 
        fprintf(stderr, "Fork failed\n"); 
        exit(1); }
    else if (rc == 0) {
        printf("Child (pid %d)\n", (int) getpid());
        close(STDOUT_FILENO);
        printf("Child (pid %d): hey...Hey.......HEY..............HHHHHHHEEEEEEEEEEEEEYYYYYYYYYYYYYYYYY\n", (int) getpid());
    } else {
        wait(NULL);
        printf("wait is over\n");
        printf("Parent (pid %d): Where is child?\n", (int) getpid());
    }
    return 0;
}
