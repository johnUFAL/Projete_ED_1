#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int main() {
    setlocale(LC_ALL, "");

    wprintf(L"Teste: á é í ó ú ç ã õ ñ\n");

    return 0;
}
