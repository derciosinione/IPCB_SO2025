// ex24a.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	pid_t pid = fork();

	if (pid == 0)
	{
		printf("[%d] Eu sou o processo filho. O meu pai é o processo %d\n", getpid(), getppid());
		sleep(20);
	}
	else if (pid > 0)
	{
		printf("PID filho no pai [%d]\n", pid);
		printf("[%d] Eu sou o processo pai. O meu pai é o processo %d\n", getpid(), getppid());
		printf("[%d] Eu sou o processo pai. O meu filho é o processo %d\n", getpid(), pid);
		sleep(20);
	}
	else
	{
		printf("Fork error!\n");
	}
	return 0;
}

// Compile with: gcc ./codigo/ex24a.c -o ex24a
// Execute with: ./ex24a&