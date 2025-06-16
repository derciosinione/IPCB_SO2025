// ex31.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Construa um programa em C,
// recorrendo ao sistema operativo Linux, que execute 5 vezes o comando "ps", com intervalos de 5 segundos entre cada execução.

int main()
{
    int res_exec;
    int status = 0;

    for (int i = 0; i < 5; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("Fork failed");
            return 1;
        }

        if (pid == 0)
        {
            res_exec = execlp("ps", "ps", NULL);

            if (res_exec == -1)
                printf("exec() error");
        }
        else if (pid > 0)
        {
            printf("\n\n Execution %d of 'ps' command:\n\n", i + 1);

            sleep(3);

            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

// Compile: gcc ./test1.c -o test1
// Execute: ./test1