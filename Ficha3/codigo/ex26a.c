// ex26a.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int status;
	pid_t p = fork();
	if (p == 0)
	{
		printf("[%d] Eu sou o processo filho. O meu pai e o %d.\n", getpid(), getppid());
		sleep(15);
	}
	else if (p > 0)
	{
		printf("[%d] Eu sou o processo pai.\n", getpid());
		sleep(30);
		waitpid(p, &status, 0);
		printf("O meu filho terminou.\n");
		sleep(15);
	}
	else
	{
		printf("Fork error!\n");
	}
	return 0;
}

// Compile with: gcc ./codigo/ex26a.c -o ex26a
// Execute with: ./ex26a&