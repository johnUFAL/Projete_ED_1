#include <stdio.h>

void imprimiArquivo (FILE * ptr)
{
    fprintf(ptr, "Hi, lady\n");
}

int main ()
{
    FILE * ptr;

    ptr = fopen("arquivo.txt", "a+"); //Adiciona conteúdo e permite leitura. Se o arquivo não existir, ele será criado

    imprimiArquivo(ptr);

    fclose(ptr);

    return 0;
}