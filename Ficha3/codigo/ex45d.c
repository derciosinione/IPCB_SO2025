// ex45d.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	printf("INICIO...\n");
	
	if(fork()==0) {
		printf("FIM FILHO\n");
		exit(0);
	}
	printf("FIM\n");
	return 0;
}

// Compile: gcc ./codigo/ex45d.c -o ex45d
// Execute: ./ex45d
