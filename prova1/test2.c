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
        pid_t pidNeto = fork();
        int statusNeto;

        if (pidNeto == 0)
        {
            contar(10, 19, "Neto", getpid());
            exit(0);
        }
        else
        {
            contar(1, 9, "Filho", getpid());
            waitpid(pid, &statusNeto, 0);
            exit(0);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
        contar(20, 29, "Pai", getpid());
    }

    return 0;
}

// Compile: gcc ./test2.c -o test2
// Execute: ./test2