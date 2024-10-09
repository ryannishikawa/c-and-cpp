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
        printf("Child (pid %d): Hello I'm child process :D\n", (int) getpid());
        char *args[] = {"ls", "-l", NULL};
        int status = execvp("ls", args);
        if (status == -1) {
            fprintf(stderr, "Exec call failed.\n"); 
            exit(1);
        }
    } else {
        sleep(2);
        printf("Parent (pid %d): Hi, I'm parent :|\n", (int) getpid());
    }
    return 0;
}