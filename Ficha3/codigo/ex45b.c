// ex45b.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("INICIO...\n");
	fork();
	fork();
	printf("FIM\n");
	return 0;
}

// Compile: gcc ./codigo/ex45b.c -o ex45b
// Execute: ./ex45b