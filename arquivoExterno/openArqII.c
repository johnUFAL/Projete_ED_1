//Abertura e fechamento de arquivo, e impressão de uma caractere por vez do arquivo

#include <stdio.h>

int main()
{
    FILE * arquivo;
    char caractere;

    arquivo = fopen("arquivo.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro\n");
    }
    else
    {
        while ((caractere = fgetc(arquivo)) != EOF) //a função irá ler um caractere do arquivo por vez, até chegar ao seu fim onde receberá EOF como valor
        //fgetc retorna um inteiro
        {
            putchar(caractere); // == printf("%d", caractere)
            printf(" - %d\n", caractere);
        } 
    }

    fclose(arquivo);

    return 0;
}