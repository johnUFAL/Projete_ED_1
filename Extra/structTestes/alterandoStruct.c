#include <stdio.h>

typedef struct
{
    char nome[50];
    int idade;
} pessoa;

void atualizarNome (pessoa * ptr)
{
    printf("Digite seu novo nome: ");
    scanf("%49[^\n]", ptr->nome);

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

    atualizarNome(&p); //passagem por referência

    printf("Novo nome: %s\n", p.nome);

    return 0;
}