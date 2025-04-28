#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

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
    pid_t pid, netoPid;
    int status;
    int pipeFilhoPai[2]; // Filho -> Pai (avisa que neto terminou)
    int pipePaiFilho[2]; // Pai -> Filho (avisa que pode imprimir)

    if (pipe(pipeFilhoPai) == -1 || pipe(pipePaiFilho) == -1)
    {
        perror("Erro ao criar pipes");
        exit(1);
    }

    pid = fork();

    if (pid < 0)
    {
        perror("Erro no fork do filho");
        return 1;
    }

    if (pid == 0)
    {
        // Processo Filho
        close(pipeFilhoPai[0]); // Fecha leitura
        close(pipePaiFilho[1]); // Fecha escrita

        netoPid = fork();

        if (netoPid < 0)
        {
            perror("Erro no fork do neto");
            return 1;
        }

        if (netoPid == 0)
        {
            // Processo Neto
            close(pipeFilhoPai[1]);
            close(pipePaiFilho[0]);
            contar(1, 9, "Neto", getpid());
            exit(0);
        }
        else
        {
            // Processo Filho
            waitpid(netoPid, &status, 0); // Filho espera neto terminar

            // Depois avisa o pai que o neto terminou
            write(pipeFilhoPai[1], "OK", 2);
            close(pipeFilhoPai[1]); // Fecha escrita

            // Espera o pai dar permissão para imprimir
            char buffer[3] = {0};
            read(pipePaiFilho[0], buffer, 2);
            close(pipePaiFilho[0]);

            // Agora sim, o filho imprime
            contar(20, 29, "Filho", getpid());
            exit(0);
        }
    }
    else
    {
        // Processo Pai
        close(pipeFilhoPai[1]); // Fecha escrita
        close(pipePaiFilho[0]); // Fecha leitura

        char buffer[3] = {0};
        read(pipeFilhoPai[0], buffer, 2); // Lê o aviso do filho
        close(pipeFilhoPai[0]);

        // Agora sabe que o neto terminou
        contar(10, 19, "Pai", getpid());

        // Depois avisa o filho que pode imprimir
        write(pipePaiFilho[1], "OK", 2);
        close(pipePaiFilho[1]);

        waitpid(pid, &status, 0); // Espera o filho terminar
    }

    return 0;
}

// Compile: gcc ./codigo/ex2Prova.c -o ex2Prova
// Execute: ./ex2Prova