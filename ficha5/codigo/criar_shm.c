#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>

#define KEY 123
#define SHM_SIZE 1024

int main()
{
  /* identificador do segmento de memoria partilhada*/
  int shmid;

  /* criar o segmento de memoria partilhada*/
  if ((shmid = shmget(KEY, SHM_SIZE, IPC_CREAT | IPC_EXCL | 0600)) == -1)
  {
    perror("Erro ao criar zona de memoria partilhada");
    return 1;
  }
  printf("ID do segmento de memoria partilhada: %d\n", shmid);
  printf("Identificado pela chave unica : %d\n", KEY);
  return 0;
}

// Compile: gcc ./codigo/criar_shm.c -o criar_shm
// Execute: ./criar_shm
