#include <stdio.h>
#include <string.h>

int main() {
    char nome[36], primeiro_nome[10];
    char lm[62] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$&*()+=§{[]}ªº/?°;:><_.";
    int i;
    int j;
    int cont;

    printf("Qual seu nome? ");
    scanf("%[^\n]", nome);
    getchar();

    while (nome[0] != lm[0] && nome[0] != lm[1] && nome[0] != lm[2] && nome[0] != lm[3] && nome[0] != lm[4]
     && nome[0] != lm[5] && nome[0] != lm[6] && nome[0] != lm[7] && nome[0] != lm[8] 
     && nome[0] != lm[9] && nome[0] != lm[10] && nome[0] != lm[11] && nome[0] != lm[12] && nome[0] != lm[13]
     && nome[0] != lm[14] && nome[0] != lm[15] && nome[0] != lm[16] && nome[0] != lm[17] 
     && nome[0] != lm[18] && nome[0] != lm[19] && nome[0] != lm[20] && nome[0] != lm[21] 
     && nome[0] != lm[22] && nome[0] != lm[23] && nome[0] != lm[24] && nome[0] != lm[25])
    {
        printf("Por favor, insira um nome valido com a primeira letra maiuscula sem espaco: ");
        scanf("%[^\n]", nome);
        getchar();
    }

    for (i = 1; i <= strlen(nome); i++) {
        for (j = 0; j <= 61; j++){
            if (nome[i] == lm[j]) {
                printf("Insira um nome valido apenas com a primeira letra maiuscula sem espaco: ");
                scanf("%[^\n]", nome);
                getchar();
                j = 62;
                i = 1;
            }
        }
    }
    printf("Primeiro nome: ");

    scanf("%s", &primeiro_nome);

    cont = 0;
    
    for (i = 0; i <= strlen(primeiro_nome); i++) {
        if (primeiro_nome[i] == 'q' || primeiro_nome[i] == 'Q') {
            cont += 1;
        }

        else if (primeiro_nome[i] == 'w' || primeiro_nome[i] == 'W') {
            cont += 6; 
        }

        else if (primeiro_nome[i] == 'e' || primeiro_nome[i] == 'E') {
            cont += 7;
        }

        else if (primeiro_nome[i] == 'r' || primeiro_nome[i] == 'R') {
            cont += 6;
        }

        else if (primeiro_nome[i] == 't' || primeiro_nome[i] == 'T') {
            cont += 5;
        }

        else if (primeiro_nome[i] == 'y' || primeiro_nome[i] == 'Y') {
            cont += 2;
        }

        else if (primeiro_nome[i] == 'u' || primeiro_nome[i] == 'U') {
            cont += 3;
        }

        else if (primeiro_nome[i] == 'i' || primeiro_nome[i] == 'I') {
            cont += 8;
        }

        else if (primeiro_nome[i] == 'o' || primeiro_nome[i] == 'O') {
            cont += 9;
        }

        else if (primeiro_nome[i] == 'a' || primeiro_nome[i] == 'A') {
            cont += 2;
        }

        else if (primeiro_nome[i] == 's' || primeiro_nome[i] == 'S') {
            cont += 5;
        }

        else if (primeiro_nome[i] == 'd' || primeiro_nome[i] == 'D') {
            cont += 8;
        }

        else if (primeiro_nome[i] == 'f' || primeiro_nome[i] == 'F') {
            cont += 7;
        }

        else if (primeiro_nome[i] == 'g' || primeiro_nome[i] == 'G') {
            cont += 4;
        }

        else if (primeiro_nome[i] == 'h' || primeiro_nome[i] == 'H') {
            cont += 1;
        }

        else if (primeiro_nome[i] == 'j' || primeiro_nome[i] == 'J') {
            cont += 4;
        }

        else if (primeiro_nome[i] == 'k' || primeiro_nome[i] == 'K') {
            cont += 7;
        }

        else if (primeiro_nome[i] == 'l' || primeiro_nome[i] == 'L') {
            cont += 8;
        }

        else if (primeiro_nome[i] == 'z' || primeiro_nome[i] == 'Z') {
            cont += 3;
        }

        else if (primeiro_nome[i] == 'x' || primeiro_nome[i] == 'X') {
            cont += 4;
        }

        else if (primeiro_nome[i] == 'c' || primeiro_nome[i] == 'C') {
            cont += 9;
        }

        else if (primeiro_nome[i] == 'v' || primeiro_nome[i] == 'V') {
            cont += 8;
        }

        else if (primeiro_nome[i] == 'b' || primeiro_nome[i] == 'B') {
            cont += 3;
        }

        else if (primeiro_nome[i] == 'n' || primeiro_nome[i] == 'N') {
            cont += 2;
        }

        else if (primeiro_nome[i] == 'm' || primeiro_nome[i] == 'M') {
            cont += 5;
        }

        else if (primeiro_nome[i] == 'ó' || primeiro_nome[i] == 'Ó') {
            cont += 6;
        }

        else if (primeiro_nome[i] == 'õ' || primeiro_nome[i] == 'Õ') {
            cont += 7;
        }

    }

    printf("%d\n", cont);
    printf("Opção escolhida %d\n", cont % 3);

    return 0;
}