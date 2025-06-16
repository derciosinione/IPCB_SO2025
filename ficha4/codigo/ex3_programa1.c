#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define KEY 123
#define NUM_SEMS 2

int main()
{
  // Programa 1 semaforo 0
  // Programa 2 semaforo 1

  int semid;
  struct sembuf sempar;
  if ((semid = semget(KEY, NUM_SEMS, IPC_CREAT | 0600)) == -1)
  {
    perror("Erro ao criar o semaforo");
    return 1;
  }
  printf("ID grupo semaforos: %d\n", semid);
  printf("Identificado pela chave unica : %d\n", KEY);

  sleep(10);

  // Liberar o semaforo 1
  sempar.sem_num = 1;
  sempar.sem_op = 1;
  sempar.sem_flg = SEM_UNDO;

  if (semop(semid, &sempar, 1) == -1)
  {
    perror("Error semop()");
    return -1;
  }

  printf("[Programa2] tem permissao para avancar!\n");
  // Esperar indicacao do semaforo 1
  sempar.sem_num = 0;
  sempar.sem_op = -1;
  sempar.sem_flg = SEM_UNDO;
  if (semop(semid, &sempar, 1) == -1)
  {
    perror("Error semop()");
    return -1;
  }
  printf("[Programa2] deu permissao para avancar!\n");
  sleep(5);
  printf("[Programa1] terminou!\n");
  // Destroi o grupo de semáforos
  if (semctl(semid, 0, IPC_RMID) == -1)
  {
    perror("Erro ao remover semáforo");
    exit(1);
  }
  printf("[Programa1] Semáforos removidos. Terminar.\n");

  return 0;
}

// Compile: gcc ./codigo/ex3_programa1.c -o ex3_programa1
// Execute: ./ex3_programa1
