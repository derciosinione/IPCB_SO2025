// ex31.c
#include <stdio.h>
#include <unistd.h>

int main()
{
	int res_exec;

	printf("STARTED...\n");
	res_exec = execlp("ls", "ls", "-la", NULL);
	// Alternativa:
	// res_exec = execl("/bin/ls", "ls", "-la", NULL);
	if (res_exec == -1)
	{
		printf("exec() error");
	}

	printf("THE END\n");
	return 0;
}

// Compile: gcc ./codigo/ex31.c -o ex31
// Execute: ./ex31