// ex45a.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	printf("INICIO...\n");
	fork();
	printf("FIM\n");
	return 0;
}

// Compile: gcc ./codigo/ex45a.c -o ex45a
// Execute: ./ex45a