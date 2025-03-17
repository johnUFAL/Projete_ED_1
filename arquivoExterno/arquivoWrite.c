#include <stdio.h>

int main ()
{
    FILE * ptr;

    ptr = fopen("arquivo.txt", "a+");

    fprintf(ptr, "oi\n"); //Adiciona conteúdo e permite leitura. Se o arquivo não existir, ele será criado

    fclose(ptr);

    return 0;
}