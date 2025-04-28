
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define NUM_PROCS 4

int main()
{
    pid_t pid;
    int status;

    int count = 1;

    while (count <= NUM_PROCS)
    {
        pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            exit(1);
        }

        if (pid == 0)
        {
            count++;
        }
        else if (pid > 0)
        {
            printf("[%d] Eu sou o processo nível %d\n", getpid(), count);
            waitpid(pid, &status, 0);
            printf("[%d] O meu filho [%d] do nível %d terminou\n", getpid(), pid, count);
            exit(0);
        }
    }

    return 0;
}

// Compile: gcc ./codigo/ex42.c -o ex42
// Execute: ./ex42