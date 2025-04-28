#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define KEY 123
#define SHM_SIZE 1024

int main()
{
  /* identificador do segmento de memoria partilhada */
  int shmid;
  /* ponteiro para a zona de memória comum */
  char *mem;

  /* aceder ao segmento de memoria partilhada */
  if ((shmid = shmget(KEY, SHM_SIZE, 0)) == -1)
  {
    perror("Erro ao aceder a zona de memoria partilhada");
    return 1;
  }

  printf("Sou o processo: %d\n", getpid());
  printf("Vou aceder ao segmento de mem partilhada identificado por: %d\n", shmid);

  /* ligacao do processo a zona de memoria
   * obter o pornteiro para o segmento de memoria partilhada */
  if ((mem = (char *)shmat(shmid, 0, 0)) == (void *)-1)
  {
    perror("Erro shmat()");
    return 1;
  }

  printf("LEITURA DA MENSAGEM NO SEGMENTO DE MEMORIA PARTILHADA\n");

  /* ler da memoria partilhada */
  printf("%s\n", mem);

  /* desligar do segmento de memoria partilhada */
  if (shmdt(mem) == -1)
  {
    perror("Erro shmdt()");
    return 1;
  }

  return 0;
}

// Compile: gcc ./codigo/ler_shm.c -o ler_shm
// Execute: ./ler_shm