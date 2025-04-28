#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define KEY 123
#define SHM_SIZE 1024

int main()
{
  /* identificador do segmento de memoria partilhada*/
  int shmid;
  /* ponteiro para a zona de memória comum*/
  char *mem;

  /* aceder ao segmento de memoria partilhada*/
  if ((shmid = shmget(KEY, SHM_SIZE, 0)) == -1)
  {
    perror("Erro ao aceder 'a zona de memoria partilhada");
    return 1;
  }

  printf("Sou o processo: %d\n", getpid());
  printf("Vou aceder ao segmento de mem partilhada identificado por: %d\n", shmid);

  /* ligação do processo a zona de memoria
   * obter o pornteiro para o segmento de memoria partilhada*/
  if ((mem = (char *)shmat(shmid, 0, 0)) == (void *)-1)
  {
    perror("Erro shmat()");
    return 1;
  }

  /* ler da memoria partilhada */
  printf("Informacao da memoria %s\n", mem);

  /* escrever na memoria partilhada */
  strcpy(mem, "SISTEMAS OPERATIVOS");

  printf("MENSAGEM ESCRITA NO SEGMENTO DE MEMORIA PARTILHADA\n");

  /* desligar do segmento de memoria partilhada */
  if (shmdt(mem) == -1)
  {
    perror("Erro shmdt()");
    return 1;
  }

  return 0;
}

// Compile: gcc ./codigo/escrever_shm.c -o escrever_shm
// Execute: ./escrever_shm
