#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define KEY 12344     // Chave para a memória compartilhada
#define SHM_SIZE 1024 // Tamanho da memória compartilhada

int main()
{
    int shmid;
    int *x; // Ponteiro para a variável compartilhada x
    pid_t pid1, pid2;

    // Criar a memória compartilhada
    shmid = shmget(KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        perror("Erro ao criar memória compartilhada");
        return 1;
    }

    // Vincular o processo à memória compartilhada
    x = (int *)shmat(shmid, NULL, 0);
    if (x == (void *)-1)
    {
        perror("Erro ao vincular à memória compartilhada");
        return 1;
    }

    pid1 = fork(); // Cria o primeiro processo Filho
    if (pid1 == 0)
    {
        // Processo Filho 1: pede o valor de x e armazena na memória compartilhada
        printf("Filho 1: Informe o valor de x: ");
        scanf("%d", x); // Armazena o valor de x na memória compartilhada

        // Finaliza o primeiro processo Filho
        shmdt(x); // Desvincula a memória compartilhada
        return 0;
    }
    else
    {
        pid2 = fork(); // Cria o segundo processo Filho
        if (pid2 == 0)
        {
            // Processo Filho 2: espera o valor de x e calcula z
            wait(NULL); // Espera o Filho 1 terminar (termos o valor de x)

            // Calcula z = 11 + x - 3
            int z = 11 + (*x) - 3;
            printf("Filho 2: O valor de z é: %d\n", z);

            // Finaliza o segundo processo Filho
            shmdt(x); // Desvincula a memória compartilhada
            return 0;
        }
        else
        {
            // Processo Pai: espera os dois filhos terminarem
            wait(NULL);
            wait(NULL);

            // Destrói a memória compartilhada
            shmctl(shmid, IPC_RMID, NULL);
            return 0;
        }
    }
}

// Compile: gcc ./codigo/ex3Prova.c -o ex3Provas
// Execute: ./exProvas