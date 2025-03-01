#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

char validation_string(char arr[]) {
   for (int i = 0; arr[i] != '\0'; i++) {
       if (!isalpha(arr[i])) {  //validacao de tipo string
           return 0;
       }
   }
   return 1;
}

char validation(char arr[]){
   int len = strlen(arr);
   
   if (arr[len - 1] == '\n') { //validacao de quebra de linha
       arr[len - 1] = '\0';
   }

   if (islower(arr[0]) || isspace(arr[0])) { //validacao de espaço e tipo de letra 
       printf("Nome nao valido\n");
       return 0;
   }
   printf("Nome valido\n");
   return 0;
}

int value_string(char letra) {
   switch (letra) {
       case 'q': return 1; case 'w': return 6; case 'e': return 7;
       case 'r': return 6; case 't': return 5; case 'y': return 2;
       case 'u': return 3; case 'i': return 8; case 'o': return 9;
       case 'p': return 4; case 'á': return 3; case 'ã': return 4;
       case 'a': return 2; case 's': return 5; case 'd': return 8;
       case 'f': return 7; case 'g': return 4; case 'h': return 1;
       case 'j': return 4; case 'k': return 7; case 'l': return 8;
       case 'ç': return 5; case 'é': return 2; case 'í': return 3;
       case 'z': return 3; case 'x': return 4; case 'c': return 9;
       case 'v': return 8; case 'b': return 3; case 'n': return 2;
       case 'm': return 5; case 'ó': return 6; case 'õ': return 7;
       case 'ô': return 6; case 'â': return 1; case 'ê': return 2;
       default: return 0;
   }
}

int name_sum(char *letra) {
   if (*letra == '\0') return 0;
   return value_string(tolower(*letra)) + (name_sum(letra + 1));
}

int main() {
   setlocale(LC_ALL, "Portuguese");

   puts("Digite seu nome completo aqui:");
   char nome[100];
   fgets(nome, 100, stdin);
   if (validation_string(nome)) { 
       validation(nome);
   }
   puts(" ");

   //decomposicao do nome e soma de cada um
   char *token = strtok(nome, " ");
   while (token !=  NULL) {
       int sum = name_sum(token);
       printf("%s  => %d\n", token, sum);
       token = strtok(NULL, " ");
   }
   return 0;
}