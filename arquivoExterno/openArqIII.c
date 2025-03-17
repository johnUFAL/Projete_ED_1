//Abertura e fechamento de arquivo, junto a impressão de uma linha por vez do arquivo

#include <stdio.h>

int main()
{
    FILE * arquivo;
    char frase[101];

    arquivo = fopen("arquivo.txt", "r");

    if (arquivo == NULL)
    {
        printf("Erro\n");
    }
    else
    {
        while (fgets(frase, sizeof(frase), arquivo) != NULL) //essa função irá ler uma linha do arquivo e ela finaliza quando encontra um "\n" ou atinge o número máximo de caracteres permitidos
        //fgets retorna um char
        {
            printf("%s", frase);
        }
    }

    fclose(arquivo);

    return 0;
}