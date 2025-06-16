// Construa um programa que crie dois processos filho. Um desses processos deve aceitar
// sequências de caracteres introduzidas pelo utilizador e enviá-las ao segundo processo. O
// segundo processo deve esperar o enviado de sequências de caracteres pelo primeiro
// processo e imprimi-las no ecrã assim que cheguem. O programa deve terminar quando o
// utilizador digitar a sequência de caracteres “sair ”.

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#define KEY 1234
#define SHM_SIZE 1024

int main()
{
    /* identificador do segmento de memoria partilhada*/
    int shmid;
    char palavra[100];
    int status;
    pid_t pid;
    char *mem;

    pid = fork();

    /* criar o segmento de memoria partilhada*/
    if ((shmid = shmget(KEY, SHM_SIZE, IPC_CREAT | 0600)) == -1)
    {
        perror("Erro ao criar zona de memoria partilhada");
        return 1;
    }

    if ((mem = (char *)shmat(shmid, 0, 0)) == (void *)-1)
    {
        perror("Erro shmat()");
        return 1;
    }

    if (pid < 0)
    {
        printf("Fork error!\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("Informe a sequencia de caracteres: ");
        fflush(stdout);
        fgets(palavra, sizeof(palavra), stdin);

        palavra[strcspn(palavra, "\n")] = 0;

        strcpy(mem, palavra);
    }
    else if (pid > 0)
    {
        waitpid(pid, &status, 0);

        printf("A sequencia de caracteres e: %s\n", mem);

        printf("Fim do processo 2\n");
    }

    /* desligar do segmento de memoria partilhada */
    if (shmdt(mem) == -1)
    {
        perror("Erro shmdt()");
        return 1;
    }

    return 0;
}

// Compile with: gcc ./codigo/ex3.c -o ex3
// Execute with: ./ex3