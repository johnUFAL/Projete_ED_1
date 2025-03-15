#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main ()
{
    setlocale(LC_ALL, "");
    
    wchar_t c;

    wprintf(L"Digite uma letra: ");
    wscanf(L"%lc", &c);

    wprintf(L"Letra digitada: %lc\n", c);

    switch (c)
    {
        case L'á':
            wprintf(L"%lc = 7\n", c);
            break;

        case L'é':
            wprintf(L"%lc = 6\n", c);
            break;

        case L'í':
            wprintf(L"%lc = 5\n", c);
            break;

        case L'ó':
            wprintf(L"%lc = 4\n", c);
            break;  
            
        case L'ú':
            wprintf(L"%lc = 3\n", c);
            break;

        default:
            wprintf(L"Letra normal\n");    
    }

    return 0;
}