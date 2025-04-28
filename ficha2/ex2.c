// Exercício 2
// Codifique um programa em C que receba dois números inteiros, enviados pela linha de
// comandos, e que apresente a soma de todos os números inteiros entre 1 e cada um deles.
// O programa a criar deve ainda apresentar a diferença entre os dois somatórios calculados.
// Exemplo de execução:
// @> somatorios 5 10
// S(5) = 15
// S(10) = 55
// S(10)-S(5) = 40

#include <stdio.h>
#include <stdlib.h>

int soma(int numero);

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Informa os dois valores para efetuar o somatorio \n");
        exit(1);
    }

    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    int somatorio1 = soma(num1);
    int somatorio2 = soma(num2);

    int diferenca = abs(somatorio2 - somatorio1);

    printf("S(%d) = %d\n", num1, somatorio1);
    printf("S(%d) = %d\n", num2, somatorio2);
    printf("S(%d)-S(%d) = %d\n", num2, num1, diferenca);

    return 0;
}

int soma(int numero)
{
    int somatorio = 0;

    for (int i = 0; i <= numero; i++)
        somatorio += i;

    return somatorio;
}
// Compile: gcc ./codigo/ex2.c -o ex2
// Execute: ./ex2 5 10
// Execute: ./ex2 10 5
// Execute: ./ex2 5
// Execute: ./ex2 5 10 20