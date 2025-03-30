#include <stdio.h>
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
}
