#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main ()
{
    setlocale(LC_ALL, "");

    const wchar_t * delimitadores = L" ,!"; //espaço, vírgula e exclamação
    wchar_t * ultimaParada;

    wchar_t frase02[101];
    wchar_t fraseCopia02[101];

    wprintf(L"Insira uma frase qualquer: ");

    fgetws(frase02, sizeof(frase02) / sizeof(wchar_t), stdin);

    wchar_t * ptr = wcschr(frase02, '\n');

    if (ptr)
    {
        *ptr = '\0';
    }

    wcscpy(fraseCopia02, frase02);

     //Dividindo a string em tokens
    wchar_t * tokien = wcstok(fraseCopia02, delimitadores, &ultimaParada);

    while (tokien != NULL)
    {
        wprintf(L"Token: %ls, Endereço: %p, tamanho: %ld\n", tokien, tokien, wcslen(tokien));

        for (int i = 0; tokien[i] != L'\0'; ++i)
        {
            wprintf(L"%lc ", tokien[i]);
        }

        wprintf(L"\n");

        tokien = wcstok(NULL, delimitadores, &ultimaParada); //Continuar com a próxima chamada
    }

    return 0;
}