// ex45c.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("INICIO...\n");
	
	if(fork()==0) {
		printf("FIM FILHO\n");
	}
	printf("FIM\n");
	return 0;
}

// Compile: gcc ./codigo/ex45c.c -o ex45c
// Execute: ./ex45c
