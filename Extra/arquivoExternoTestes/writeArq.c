//Abertura e fechamento de arquivo, e escrita

#include <stdio.h>

int main()
{
    FILE * arquivo;
    int i;
    int idade[10];
    double alt[10];

    arquivo = fopen("arquivoI.txt", "w");

    if (arquivo == NULL)
    {
        printf("Erro de abertura do arquivo!\n");
        return 1;
    }

    printf("CADASTRO DE PESSOAS\n");
    printf("Você pode cadastrar até 10 pessoas! Quantas irá cadastrar? ");
    scanf("%d", &i);

    if (i > 10)
    {
        printf("Erro! Limite excedido\n");
        return 1;
    } 

    for (int j = 0; j < i; ++j)
    {
        printf("Idade n°%d: ", j + 1);
        scanf("%d", &idade[j]);

        printf("Altura n°%d: ", j + 1);
        scanf("%lf", &alt[j]);
    }

    for (int j = 0; j < i; ++j)
    {
        fprintf(arquivo, "Idade n°%d: %d, Altura n°%d: %.2lf\n", j + 1, idade[j], j + 1, alt[j]); //grava os dados do arquivo com formatação
    }

    fputs("Escrevendo mais uma linha\n", arquivo); //escreve uma string no arquivo

    fputc('A', arquivo);
    fputc(' ', arquivo);
    fputc('B', arquivo);
    fputc(' ', arquivo);
    fputc('C', arquivo);
    fputc('\n', arquivo);

    fclose(arquivo);

    return 0;
}