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
    perror("Error semget()");
    return 1;
  }
  printf("ID grupo semaforos: %d\n", semid);
  printf("Identificado pela chave unica : %d\n", KEY);
  // Esperar indicacao do semaforo 0
  sempar.sem_num = 1;
  sempar.sem_op = -1;
  sempar.sem_flg = SEM_UNDO;

  if (semop(semid, &sempar, 1) == -1)
  {
    perror("Error semop()");
    return -1;
  }

  printf("[Programa1] deu permissao para avancar!\n");

  sleep(20);

  // Liberar o semaforo 0
  sempar.sem_num = 0;
  sempar.sem_op = 1;
  sempar.sem_flg = SEM_UNDO;
  if (semop(semid, &sempar, 1) == -1)
  {
    perror("Error semop()");
    return -1;
  }
  printf("[Programa1] tem permissao para avancar!\n");
  sleep(5);
  printf("[Programa2] terminou!\n");
  return 0;
}

// Compile: gcc ./codigo/ex3_programa2.c -o ex3_programa2
// Execute: ./ex3_programa2
