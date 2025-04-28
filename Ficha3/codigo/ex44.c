// ex44.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int c = 2;
	pid_t p = 0;
	int status;

	p = fork();
	if (p == 0)
	{
		c = c + 5;
	}
	else if (p > 0)
	{
		c = c + 2;
		waitpid(p, &status, 0);
	}
	else
	{
		printf("Fork error!\n");
	}
	printf("c=%d\n", c);

	exit(0);
}

// Compile: gcc ./codigo/ex44.c -o ex44
// Execute: ./ex44
