#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>

#define KEY 123
#define NUM_SEMS 4

int main()
{
	struct sembuf sempar;
	int semid;

	/* Obter o identificador de um conjunto de semaforos anteriormente criado */
	if ((semid = semget(KEY, 0, 0)) == -1)
	{
		perror("Error semget()");
		return 1;
	}

	printf("ID grupo semaforos: %d\n", semid);
	printf("Identificado pela chave unica : %d\n", KEY);

	/* Operacao de decremento do segundo semaforo */
	sempar.sem_num = 1;		   // vamos operar o segundo semaforo
	sempar.sem_op = -1;		   // decrementa este valor ao valor do semaforo
	sempar.sem_flg = SEM_UNDO; // desfaz apos o processo terminar

	if (semop(semid, &sempar, 1) == -1)
	{
		perror("Error semop()");
		return -1;
	}

	printf("O valor do segundo semaforo foi decrementado!\n");

	return 0;
}

// Compile: gcc ./codigo/dec_op_sem.c -o dec_op_sem
// Execute: ./dec_op_sem