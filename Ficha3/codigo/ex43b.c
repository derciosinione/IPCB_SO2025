#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void contar(int inicio, int fim, const char *nome_processo, pid_t pid)
{
    printf("Eu sou o processo %s com PID = %d\n", nome_processo, pid);
    for (int i = inicio; i <= fim; i++)
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
        contar(10, 20, "Filho", getpid());
        exit(0);
    }
    else
    {
        contar(1, 10, "Pai", getpid());
        waitpid(pid, &status, 0);
        contar(20, 30, "Pai", getpid());
    }

    return 0;
}

// Compile: gcc ./codigo/ex43b.c -o ex43b
// Execute: ./ex43b