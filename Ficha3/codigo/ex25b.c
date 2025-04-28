// ex25b.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int status = 0;
    pid_t p = fork();
    if (p == 0)
    {
        printf("[%d] Eu sou o filho. O meu pai é o processo PPID [%d]\n", getpid(), getppid());
        sleep(15);
        exit(10);
    }
    else if (p > 0)
    {
        printf("[%d] Eu sou o processo pai\n", getpid());
        waitpid(p, &status, 0);
        printf("O processo filho [%d] terminou com estado %d.\n", p, WEXITSTATUS(status));
    }
    else
    {
        printf("Fork error!\n");
    }
    return 0;
}

// Compile with: gcc ./codigo/ex25b.c -o ex25b
// Execute with: ./ex25a&