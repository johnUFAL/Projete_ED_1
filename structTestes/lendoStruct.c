#include <stdio.h>

typedef struct
{
    char nome[50];
    int idade;
} pessoa;

void imprimaStruct (pessoa q)
{
    printf("Seu name eh: %s; idade: %d\n", q.nome, q.idade);

    printf("Digite seu nome: ");
    scanf("%49[^\n]", q.nome);
    printf("Digite sua idade: ");
    scanf("%d", &q.idade);

    printf("Nome após a alteração (dentro da função):\n");
    printf("Seu name eh: %s; idade: %d\n", q.nome, q.idade);

    return;
}

int main ()
{
    pessoa p;

    printf("Digite seu nome: ");
    scanf("%49[^\n]", p.nome);
    printf("Digite sua idade: ");
    scanf("%d", &p.idade);
    getchar();

    imprimaStruct(p); //passando struct por valor

    printf("Nome após a alteração (fora da função):\n");
    printf("Seu name eh: %s; idade: %d\n", p.nome, p.idade);

    return 0;
}