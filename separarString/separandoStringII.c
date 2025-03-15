/*#include <stdio.h>
#include <string.h>

int main() {
    char frase[] = "Olá, como você está?";
    const char *delimitadores = " ,?";  // Espaço, vírgula e ponto de interrogação

    // Dividindo a string em tokens
    char *token = strtok(frase, delimitadores);

    // Imprimindo os tokens
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok(NULL, delimitadores);  // Continuar com a próxima chamada
    }

    return 0;
}*/


#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main ()
{
    setlocale(LC_ALL, "");

    wchar_t frase[] = L"Olá, Mundo vei! Bonjour!";
    wchar_t fraseCopia[100];
    const wchar_t * delimitadores = L" ,!"; //espaço, vírgula e exclamação

    wcscpy(fraseCopia, frase);

    wchar_t * ultimaParada;

    //Dividindo a string em tokens
    wchar_t * token = wcstok(fraseCopia, delimitadores, &ultimaParada);

    while (token != NULL)
    {
        wprintf(L"Token: %ls\n", token);
        token = wcstok(NULL, delimitadores, &ultimaParada); //Continuar com a próxima chamada
    }

    wchar_t frase02[101];
    wchar_t fraseCopia02[101];

    fgetws(frase02, sizeof(frase02) / sizeof(wchar_t), stdin);

    wcscpy(fraseCopia02, frase02);

    wchar_t * tokien = wcstok(fraseCopia02, delimitadores, &ultimaParada);

    while (tokien != NULL)
    {
        wprintf(L"Token: %ls\n", tokien);
        tokien = wcstok(NULL, delimitadores, &ultimaParada);
    }

    return 0;
}