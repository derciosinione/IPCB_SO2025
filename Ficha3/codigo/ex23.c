// ex23.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t p = fork();
	if (p == 0)
	{
		printf("Processo filho p value: %d.\n", p);
		printf("Eu sou o processo filho.\n");
		sleep(20);
	}
	else if (p > 0)
	{
		printf("Processo pai p value: %d.\n", p);
		printf("Eu sou o processo pai.\n");
		sleep(20);
	}
	else
	{
		printf("Fork error!\n");
	}
	return 0;
}

// Compile with: gcc ./codigo/ex23.c -o exe23
// Execute with: ./exe23&