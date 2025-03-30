#include <stdio.h>

int lerArquivo (FILE * ptr, char textos[][50], int max)
{
    int i = 0;
    
    while (fscanf(ptr, "%49[^\n]\n", textos[i]) != EOF) //você pode utilizar esse método tanto para ler entradas formatadas quanto para contabilizar o número de linhas do arquivo que nesse caso estará armazenada na variável i
    //todavia como o fscanf é para entradas formatadas, caso não seja especificado o que ele deve ler e até onde, como por ex.: "%49[^\n]\n"
    //ele irá ler string por string
    {
        i++;
        
        if (i >= max)
        {
            printf("Chegamos ao limite!\n");
            return i;
        }
    }

    return i;
}

int main ()
{
    FILE * ptr;
    char textos[10][50];
    int max;

    ptr = fopen("arquivo.txt", "r");

    if (ptr == NULL)
    {
        printf("Algo deu errado!\n");
        return 1;
    }

    max = lerArquivo(ptr, textos, 10);

    for (int i = 0; i < max; ++i)
    {
        printf("Texto[%d] = %s\n", i + 1, textos[i]);
    }

    fclose(ptr);

    return 0;
}