// ex21.c
#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("SLEEP... \n");
	sleep(30);
	printf("THE END \n");
}

// Compile: gcc ./ex21.c -o ex21
// Execute: ./ex21
// Execute: ./ex21 &
// Execute: ps -ef | grep ex21
// Execute: kill -9 <PID>