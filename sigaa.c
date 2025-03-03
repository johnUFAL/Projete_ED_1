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
    char disciplina[60];
    int carga;
    int hora_inicio; //usar o horario militar (Ex: 1130 = 11:30)
    int hora_final;
    char pre_requisitos[100];
    float dias;
};

void matricula(struct Aluno aluno) {
    if (aluno.periodo == 1) {
        struct Disciplina disciplinas[] = {
            {"Programacao 1", 72, 1520, 1850, "Nenhum", 6.0},
            {"Matematica Discreta", 72, 1330, 1510, "Nenhum", 3.5},
            {"Calculo Diferencial e Integral", 144, 1520, 1850, "Nenhum", 3.5},
            {"Logica para Programacao", 72, 1520, 1700, "Nenhum", 2.4},
            {"Computacao, Sociedade e Etica", 72, 1710, 1850, "Nenhum", 2.4},
        };

        puts("Sua grade eh:");
        for (int i = 0; i < 5; i++) {
            printf("%s - Carga: %d\n, Horario: %d-%d\n, Pre-requisitos: %s\n, Dias: %.1f\n",
                   disciplinas[i].nome, disciplinas[i].carga, disciplinas[i].hora_inicio,
                   disciplinas[i].hora_final, disciplinas[i].pre_requisitos, disciplinas[i].dias);
        }
    } else if (aluno.periodo == 2) {
        struct Disciplina disciplinas[] = {
            {"Banco de dados", 72, 1330, 1520, "Nenhum", 2.4},
            {"Geometria Analitica", 72, 1520, 1710, "Nenhum", 2.4},
            {"Org. E arq. de Computadores", 72, 920, 1100, "Nenhum", 3.5},
            {"Estrutra de Dados", 72, 1110, 1250, "Programacao 1", 3.5},
    };
    
        puts("Sua grade eh:");
        for (int i = 0; i < 4; i++) {
            printf("%s - Carga: %d\n, Horario: %d-%d\n, Pre-requisitos: %s\n, Dias: %.1f\n",
                disciplinas[i].nome, disciplinas[i].carga, disciplinas[i].hora_inicio,
                disciplinas[i].hora_final, disciplinas[i].pre_requisitos, disciplinas[i].dias);
        }
    } else if (aluno.periodo == 3) {
        struct Disciplina disciplinas[] = {
            {"Redes de Computadores", 72, 1520, 1700, "Programacao 1", 2.5},
            {"Teoria dos Grafos", 72, 1330, 1510, "Estrutra de Dados e Matematica Discreta", 2.5},
            {"Probabilidade e Estastistica", 72, 1110, 1250, "Calculo Diferencial e Integral", 2.4},
            {"Algebra Linear", 72, 920, 1100, "Geometria Analitica", 2.4},
    };
    
        puts("Sua grade eh:");
        for (int i = 0; i < 4; i++) {
            printf("%s - Carga: %d\n, Horario: %d-%d\n, Pre-requisitos: %s\n, Dias: %.1f\n",
                disciplinas[i].nome, disciplinas[i].carga, disciplinas[i].hora_inicio,
                disciplinas[i].hora_final, disciplinas[i].pre_requisitos, disciplinas[i].dias);
        }
    } else if (aluno.periodo == 4) {
        struct Disciplina disciplinas[] = {
            {"Programacao 2", 72, 1520, 1700, "Estrutura de Dados, Banco de dados e Redes de Computadores", 4.0},
            {"Programacao 3", 72, 1520, 1700, "Estrutura de Dados, Banco de dados e Redes de Computadores", 3.5},
            {"Projeto de Analise de Algoritmos", 72, 1710, 1850, "Estrutura de Dados e Teoria dos Grafos", 2.5},
            {"Teoria da Computacao", 72, 1330, 1510, "Nenhum", 2.4},
    };
    
        puts("Sua grade eh:");
        for (int i = 0; i < 4; i++) {
            printf("%s - Carga: %d\n, Horario: %d-%d\n, Pre-requisitos: %s\n, Dias: %.1f\n",
                disciplinas[i].nome, disciplinas[i].carga, disciplinas[i].hora_inicio,
                disciplinas[i].hora_final, disciplinas[i].pre_requisitos, disciplinas[i].dias);
        }
    } else if (aluno.periodo == 5) {
        struct Disciplina disciplinas[] = {
            {"Sietemas Operacionais", 72, 1330, 1520, "Org. E arq. de Computadores", 2.4},
            {"Compiladores", 72, 1520, 1700, "Estrutura de Dados e Logica para Computacao", 2.4},
            {"Inteligencia Artificial", 72, 1520, 1700, "Estrutura de Dados e Logica para Computacao", 3.5},
            {"Computacao Grafica", 72, 1710, 1850, "Nenhum", 3.5},
    };
    
        puts("Sua grade eh:");
        for (int i = 0; i < 4; i++) {
            printf("%s - Carga: %d\n, Horario: %d-%d\n, Pre-requisitos: %s\n, Dias: %.1f\n",
                disciplinas[i].nome, disciplinas[i].carga, disciplinas[i].hora_inicio,
                disciplinas[i].hora_final, disciplinas[i].pre_requisitos, disciplinas[i].dias);
        }
    } else if (aluno.periodo == 6) {
        struct Disciplina disciplinas[] = {
            {"Projeto e Desenvolvimento de Sistemas", 288, 920, 1510, "Todas as diciplinas de 1º ao 5º semestre", 2.405},
    };
    
        puts("Sua grade eh:");
        for (int i = 0; i < 1; i++) {
            printf("%s - Carga: %d\n, Horario: %d-%d\n, Pre-requisitos: %s\n, Dias: %.1f\n",
                disciplinas[i].nome, disciplinas[i].carga, disciplinas[i].hora_inicio,
                disciplinas[i].hora_final, disciplinas[i].pre_requisitos, disciplinas[i].dias);
        }
    } else if (aluno.periodo == 7) {
        struct Disciplina disciplinas[] = {
            {"Metodologias de Pesquisa e Trabalhos Individual", 72, 1330, 1510, "Nenhum", 3.5},
            {"Nocoes de Direito", 72, 1520, 1850, "Nenhum", 3.0},

    };
    
        puts("Sua grade eh:");
        for (int i = 0; i < 2; i++) {
            printf("%s - Carga: %d\n, Horario: %d-%d\n, Pre-requisitos: %s\n, Dias: %.1f\n",
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

int value_string(char letra) { //revisar melhor forma de usar palavras com acentos!!!!!!!!!!!!!!!!!!!!!!!!
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

//ignora essas palavras 
int ignorate(const char *primeiro_char) { //aponta para a primeeira letra 
    return (strcmp(primeiro_char, "da") == 0 || strcmp(primeiro_char, "de") == 0 || strcmp(primeiro_char, "do") == 0 ||
            strcmp(primeiro_char, "das") == 0 || strcmp(primeiro_char, "dos") == 0); //modifica os enderecos para 0
}
void name_process(char *nome) {
    char temp[50]; //copia da original antes de usar
    strcpy(temp, nome);  //não modificar o original

    char *token = strtok(temp, " ");
    
    puts("Resultado da divisao por 3 (resto):");
    while (token != NULL) {
        if (!ignorate(token)) {
            int soma = name_sum(token);
            printf("%s => Soma: %d, Resto da divisao por 3: %d\n", token, soma, (soma % 3));
        }
        token = strtok(NULL, " ");
    }
}

int main() {
   setlocale(LC_ALL, "Portuguese");

   struct Aluno aluno;

   puts("Digite seu nome completo aqui:");
   fgets(aluno.nome, sizeof(aluno.nome), stdin);
   aluno.nome[strcspn(aluno.nome, "\n")] = '\0';

   puts("Digite seu periodo aqui:");
   scanf("%d", &aluno.periodo);
   getchar();
   
   //validacao do nome 
   if (validation_string(aluno.nome)) {
       validation(aluno.nome);
   }
   puts(" ");

   //decomposicao do nome e soma de cada um
   puts("Decomposicao do nome, some e resto");
   name_process(aluno.nome);

   puts(" ");

   //matricula do aluno e grade curricular
   matricula(aluno);

   return 0;
}