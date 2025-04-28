#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

void contar(const char *nome_processo, pid_t pid)
{
    printf("Eu sou o processo %s com PID = %d\n", nome_processo, pid);
    for (int i = 1; i <= 10; i++)
    {
        printf("%s [%d]: %d\n", nome_processo, pid, i);
    }
}

int main()
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("Erro no fork");
        return 1;
    }

    if (pid == 0)
    {
        contar("Filho", getpid());
    }
    else
    {
        contar("Pai", getpid());
        waitpid(pid, &status, 0);
        printf("O processo filho [%d] terminou com status %d\n", pid, WEXITSTATUS(status));
    }

    return 0;
}

// Compile: gcc ./codigo/ex43.c -o ex43
// Execute: ./ex43