#include <stdio.h>

int main()
{
    int idade;
    double altura;
    char nome[73];
    FILE * arquivo;

    arquivo = fopen("arquivoII.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
   
    fscanf(arquivo, "Idade n°1: %d, Nome: %72[^,], Altura n°1: %lf", &idade, nome, &altura);
    //Idade n°1: 23, Nome: Guilherme, Altura n°1: 1.76

    printf("%d %s %.2lf\n", idade, nome, altura);

    fclose(arquivo);

    return 0;
}