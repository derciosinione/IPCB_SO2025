#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define KEY 123
#define NUM_SEMS 4

int main()
{
  /* identificador do conjundo de semaforos */
  int semid;

  /* criar o grupo de semaforos (4 semaforos) */
  semid = semget(KEY, NUM_SEMS, IPC_CREAT | IPC_EXCL | 0600);

  if (semid == -1)
  {
    perror("Erro ao criar o semaforo");
    return 1;
  }

  printf("ID grupo semaforos: %d\n", semid);
  printf("Identificado pela chave unica : %d\n", KEY);

  // semctl(semid, 0, SETVAL, 2);
  // semctl(semid, 1, SETVAL, 3);

  // int valSem0 = semctl(semid, 0, GETVAL);
  // int valSem1 = semctl(semid, 1, GETVAL);

  // printf("Valor do semaforo 0: %d\n", valSem0);
  // printf("Valor do semaforo 1: %d\n", valSem1);
  // printf("Valor do semaforo 2: %d\n", semctl(semid, 2, GETVAL));

  return 0;
}

// Compile: gcc ./codigo/criar_sem.c -o criar_sem
// Execute: ./criar_sem
