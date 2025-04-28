// Construa um programa que aceite e execute comandos, do sistema Linux, indicados pelo
// utilizador. O programa deve estar sempre disponível para aceitar e executar novos
// comandos indicados pelo utilizador, e apenas deve terminar quando o utilizador digitar
// “quit”.

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

#define MAX 120

int main()
{
    int status, childStatus;
    char command[MAX];
    char *args[MAX];

    pid_t pid;

    while (1)
    {
        printf("Informe um comando: ");
        fflush(stdout);
        fgets(command, MAX, stdin);
        command[strcspn(command, "\n")] = 0; // Remove newline character

        if (strlen(command) == 0)
        {
            printf("Comando vazio. Tente novamente.\n");
            continue;
        }

        if (strcmp(command, "quit") == 0)
            exit(0);

        char *token = strtok(command, " ");

        int contador = 0;

        while (token != NULL)
        {
            args[contador] = token;
            token = strtok(NULL, " ");
            contador++;
        }

        args[contador] = NULL; // Null-terminate the array of arguments

        pid = fork();

        if (pid == 0)
        {
            int res_exec = execvp(args[0], args);

            if (res_exec == -1)
            {
                printf("O comando '%s' não foi encontrado.\n", args[0]);
                perror("exec() error ");
                exit(1);
            }

            exit(0);
        }
        else if (pid > 0)
        {
            waitpid(pid, &status, 0);

            childStatus = WEXITSTATUS(status);

            if (childStatus == 1)
            {
                printf("O processo filho terminou com estado %d.\n", childStatus);
                continue;
            }
        }
    }

    printf("Fim da execucao\n");
    return 0;
}

// Compile: gcc ./codigo/ex41.c -o ex41
// Execute: ./ex41