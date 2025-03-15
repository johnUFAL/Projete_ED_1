#include <stdio.h>
#include <wchar.h>
#include <locale.h>

int ehVogal(wchar_t c) {
    wchar_t vogais[] = L"aeiouáéíóúãõàèìòùâêîôûAEIOUÁÉÍÓÚÃÕÀÈÌÒÙÂÊÎÔÛ";

    for (int i = 0; vogais[i] != L'\0'; i++) {
        if (c == vogais[i]) {
            return 1;
        }
    }
    return 0;
}

int ehVogalII(wchar_t c) {
    wchar_t vogais[] = L"áéíóúãõàèìòùâêîôûÁÉÍÓÚÃÕÀÈÌÒÙÂÊÎÔÛ";

    for (int i = 0; vogais[i] != L'\0'; i++) {
        if (c == vogais[i]) {
            return 1;
        }
    }
    return 0;
}

int main() {
    setlocale(LC_ALL, ""); // Configura suporte a Unicode

    wchar_t texto[101];
    int contadorTotal = 0;
    int contadorAcento = 0;

    wprintf(L"Digite uma frase: ");
    fgetws(texto, sizeof(texto) / sizeof(wchar_t), stdin);

    for (int i = 0; texto[i] != L'\0'; i++) {
        if (ehVogal(texto[i])) {
            contadorTotal++;
        }
    }

    for (int i = 0; texto[i] != L'\0'; i++) {
        if (ehVogalII(texto[i])) {
            contadorAcento++;
        }
    }

    wprintf(L"Número de vogais (total): %d\n", contadorTotal);
    wprintf(L"Número de vogais (com acentos): %d\n", contadorAcento);
    return 0;
}