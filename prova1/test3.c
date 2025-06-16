#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#define KEY 12345
#define SHM_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Uso correto: %s <valor_inicial>\n", argv[0]);
        return 1;
    }

    int valor_inicial = atoi(argv[1]);
    int shmid;
    int *valor;
    pid_t pid1, pid2;
    int status;

    if ((shmid = shmget(KEY, SHM_SIZE, IPC_CREAT | 0600)) == -1)
    {
        perror("Erro ao criar zona de memória compartilhada");
        return 1;
    }

    if ((valor = (int *)shmat(shmid, NULL, 0)) == (void *)-1)
    {
        perror("Erro ao associar memória compartilhada");
        return 1;
    }

    *valor = valor_inicial;

    // Criar o primeiro processo filho (incrementador)
    pid1 = fork();
    if (pid1 < 0)
    {
        perror("Erro ao criar o primeiro processo filho");
        return 1;
    }

    if (pid1 == 0)
    {
        // Processo Filho 1 (Incrementador)
        while (*valor <= 100)
        {
            sleep(1);
            *valor += 5;
            // printf("Filho 1 (Incrementador): Valor atualizado para %d\n", *valor);
        }
        shmdt(valor);
        exit(0);
    }

    // Criar o segundo processo filho (exibidor)
    pid2 = fork();
    if (pid2 < 0)
    {
        perror("Erro ao criar o segundo processo filho");
        return 1;
    }

    if (pid2 == 0)
    {
        while (*valor <= 100)
        {
            printf("Filho 2 (Exibidor): Valor = %d\n", *valor);
            sleep(1);
        }
        shmdt(valor);
        exit(0);
    }

    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

// Compile with: gcc -o test3 test3.c
// Run with: ./test3 0
// Example: ./test3 0
