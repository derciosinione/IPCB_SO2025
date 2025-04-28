// ex25a.c
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
        exit(10);
    }
    else if (p > 0)
    {
        waitpid(p, &status, 0);
        printf("O processo filho terminou com estado %d.\n", WEXITSTATUS(status));
    }
    else
    {
        printf("Fork error!\n");
    }
    return 0;
}

// Compile with: gcc ./codigo/ex25a.c -o ex25a
// Execute with: ./ex25a&