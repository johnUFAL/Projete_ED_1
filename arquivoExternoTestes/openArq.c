//Abertura e fechamento de arquivo

#include <stdio.h>

int main()
{
    FILE * arquivo; //criando um ponteiro do tipo FILE  

    arquivo = fopen("arquivo.txt", "r"); //atribuindo um endereço de um arquivo ao ponteiro do tipo FILE

    if (arquivo == NULL) //verificação para saber se o arquivo foi aberto, ou não
    {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }
    else
    {
        printf("Sucesso ao abrir o arquivo!\n");
    }


    printf("Localização ponteiro: %p\n", arquivo);

    if (fclose(arquivo) == 0) //fechamento do arquivo
    {
        printf("Arquivo fechado com sucesso!\n");
    }
    else
    {
        printf("Erro ao fechar o arquivo!\n");
    }

    return 0;
}