#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

struct Aluno {
    char nome[50];
    int periodo;
};

struct Disciplina {
    char nome[50];
    int carga;
    int hora_inicio; //usar o horario militar (Ex: 1130 = 11:30)
    int hora_final;
    char pre_requisitos[100];
    float dias;  //Ex: 2,4 => segunda e quarta
};

struct Eletiva {
    char disciplina[50];
    int carga;
    int hora_inicio; //usar o horario militar (Ex: 1130 = 11:30)
    int hora_final;
    char pre_requisitos[100];
    float dias;
};

void matricula(struct Aluno aluno) {
    if (aluno.periodo == 1) {
        struct Disciplina disciplinas[] = {
            {"Programacao 1", 72, 1520, 1850, "", 6.0},
            {"Matematica Discreta", 72, 1330, 1510, "", 3.5},
            {"Calculo Diferencial e Integral", 144, 1520, 1850, "", 3.5},
            {"Logica para Programacao", 72, 1520, 1700, "", 2.4},
            {"Computacao, Sociedade e Etica", 72, 1710, 1850, "", 2.4},
        };

        puts("Sua grade é:");
        for (int i = 0; i < 5; i++) {
            printf("%s - Carga: %d, Horario: %d-%d, Pre-requisitos: %s, Dias: %.1f\n",
                   disciplinas[i].nome, disciplinas[i].carga, disciplinas[i].hora_inicio,
                   disciplinas[i].hora_final, disciplinas[i].pre_requisitos, disciplinas[i].dias);
        }
    }
    if (aluno.periodo == 2) {
        struct Disciplina disciplinas[] = {
            {"Banco de dados", 72, 1330, 1520, "", 2.4},
            {"Geometria Analitica", 72, 1520, 1710, "", 2.4},
            {"Org. E arq. de Computadores", 72, 920, 1100, "", 3.5},
            {"Estrutra de Dados", 72, 1110, 1250, "", 3.5},
    };
    
    puts("Sua grade é:");
        for (int i = 0; i < 4; i++) {
            printf("%s - Carga: %d, Horario: %d-%d, Pre-requisitos: %s, Dias: %.1f\n",
                    disciplinas[i].nome, disciplinas[i].carga, disciplinas[i].hora_inicio,
                    disciplinas[i].hora_final, disciplinas[i].pre_requisitos, disciplinas[i].dias);
        }
    }
}


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

int name_sum(char *nome) {
   if (*nome == '\0') return 0;
   return value_string(tolower(*nome)) + (name_sum(nome + 1));
}

int main() {
   setlocale(LC_ALL, "Portuguese");

   struct Aluno aluno;

   puts("Digite seu nome completo aqui:");
   fgets(aluno.nome, sizeof(aluno.nome), stdin);
   aluno.nome[strcspn(aluno.nome, "\n")] = '\0';

   puts("Digite seu período aqui:");
   scanf("%d", &aluno.periodo);
   getchar();
   
   //validacao do nome 
   if (validation_string(aluno.nome)) {
       validation(aluno.nome);
   }
   puts(" ");

   //decomposicao do nome e soma de cada um
   puts("Decomposição do nome");
   char *token = strtok(aluno.nome, " ");
   while (token !=  NULL) {
       printf("%s => %d\n", token, name_sum(token));
       token = strtok(NULL, " ");
   }
   puts(" ");

   matricula(aluno);

   return 0;
}