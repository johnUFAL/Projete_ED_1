#include <stdio.h>
#include <locale.h>
#include <wchar.h>

int main ()
{
    setlocale(LC_ALL, ""); //Permite suporte a caracteres Unicode

    /*
    setlocale(LC_ALL, "en_US.UTF-8"); // Para Linux/Mac
    setlocale(LC_ALL, "Portuguese_Brazil.1252"); // Para Windows
    */
    
    wchar_t frase[101];

    wprintf(L"Digite uma frase: "); //esse 'L' indica que a função irá lidar com caracteres largos da tabela Unicode
    fgetws(frase, sizeof(frase) / sizeof(wchar_t), stdin);

    wprintf(L"Frase com '\\n': %ls", frase);
    // %ls para strings
    // %lc para caracteres

    wchar_t * ptr = wcschr(frase, L'\n'); //wcschr é o equivalente do strcspn, onde este irá apontar para a 1° aparição do '\n'

    if (ptr) //se ptr for diferente de NULL então o ponteiro encontrou a posição do '\n'
    {
        *ptr = L'\0'; //substituindo
    }

    wprintf(L"Frase sem '\\n': %ls", frase);

    wprintf(L"Valor númerico de cada letra: ");

    for (int i = 0; frase[i] != L'\0'; i++)
    {
        wprintf(L"%d ", frase[i]);
    }

    return 0;
}