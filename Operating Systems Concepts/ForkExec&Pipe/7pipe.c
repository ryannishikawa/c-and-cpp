#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char* argv[]) { 
    int fpipe[2];
    if (pipe(fpipe) == -1) {
        fprintf(stderr, "Pipe failed\n");
    }

    int rc1 = fork();
    if (rc1 < 0) { 
        fprintf(stderr, "Fork failed\n"); 
        exit(1); 
    }
    else if (rc1 == 0) {
        close(fpipe[0]);
        dup2(fpipe[1], STDOUT_FILENO);
        printf("Child 1 (pid %d): hello from child 1.\n", (int) getpid());
    } else {
        wait(NULL);
        printf("\nChild 1 process is over\n\n");
        int rc2 = fork();
        if (rc2 < 0) { 
            fprintf(stderr, "Fork2 failed\n"); 
            exit(1); 
        } else if (rc2 == 0) {
            printf("Child 2 process start\n");
            close(fpipe[1]);
            dup2(fpipe[0], STDIN_FILENO);
            char buffer[64];
            fgets(buffer, sizeof(buffer), stdin);
            printf("%s", buffer);
            printf("Child 2 (pid %d): hi child 1, i'm child 2\n", (int) getpid());
        } else {
            wait(NULL);
            printf("Child 2 process is over\n\n");
            printf("Parent (pid %d): hello children.\n", (int) getpid());
        }
    }
    return 0;
}
