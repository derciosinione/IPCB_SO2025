// ex22.c
#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid = getpid();
	printf("\nEu sou o processo %d\n", pid);
	printf("SLEEP... \n");
	sleep(30);
	printf("THE END \n");
}

// Compile with: gcc ./codigo/ex22.c -o exe22
// Execute with: ./ex22
