#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <errno.h>

#define NUM_SEMS 3
#define KEY 1234

void contar(int inicio, int fim, const char *nome)
{
    for (int i = inicio; i <= fim; i++)
    {
        printf("[%s] %d\n", nome, i);
    }
}

int main()
{
    int semid;
    struct sembuf op;
    pid_t pid1, pid2;

    // Criar conjunto de semáforos
    semid = semget(KEY, NUM_SEMS, IPC_CREAT | 0666);
    if (semid == -1)
    {
        perror("Erro ao criar semáforo");
        return 1;
    }

    // Inicializar os semáforos
    semctl(semid, 0, SETVAL, 0); // Semáforo 0 - Neto deve começar primeiro
    semctl(semid, 1, SETVAL, 0); // Semáforo 1 - Pai só começa depois do Filho
    semctl(semid, 2, SETVAL, 0); // Semáforo 2 - Pai sinaliza quando terminou

    // Criar o primeiro processo (Filho)
    pid1 = fork();

    if (pid1 == 0)
    {
        // Processo Filho
        pid2 = fork(); // Criar o processo Neto dentro do Filho

        if (pid2 == 0)
        {
            // Processo Neto
            contar(1, 9, "Neto");

            // Semáforo: sinaliza para o Filho que o Neto terminou
            op.sem_num = 0;
            op.sem_op = 1; // Sinaliza o Filho (incrementa o semáforo)
            op.sem_flg = 0;
            semop(semid, &op, 1);

            // Semáforo: sinaliza para o Pai que o Neto terminou
            op.sem_num = 2;
            op.sem_op = 1; // Sinaliza o Pai (incrementa o semáforo)
            semop(semid, &op, 1);
        }
        else
        {
            // Processo Filho espera o Neto terminar
            op.sem_num = 0;
            op.sem_op = -1; // Espera o Neto terminar antes de imprimir
            semop(semid, &op, 1);

            contar(20, 29, "Filho");

            // Semáforo: sinaliza para o Pai que o Filho terminou
            op.sem_num = 1;
            op.sem_op = 1; // Sinaliza o Pai (incrementa o semáforo)
            semop(semid, &op, 1);
        }
    }
    else
    {
        // Processo Pai
        op.sem_num = 2;
        op.sem_op = -1; // Espera o Neto terminar (significado do semáforo 2)
        semop(semid, &op, 1);

        contar(10, 19, "Pai");

        // Espera o Filho terminar
        op.sem_num = 1;
        op.sem_op = -1; // Espera o Filho terminar (semáforo 1)
        semop(semid, &op, 1);
    }

    // Destruir o conjunto de semáforos após o uso
    semctl(semid, 0, IPC_RMID, 0);

    return 0;
}

// Compile: gcc ./codigo/exProvas.c -o exProvas
// Execute: ./exProvas