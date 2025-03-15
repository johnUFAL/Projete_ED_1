#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
 
//nome completo: Erivaldo Jose Da Silva Santos Junior
//nome teste: erivaldo jose silva santos

typedef struct {
    char nome[50];
    int periodo;
    int max_disciplina;
    int tempo_curso;
    int enfase;
    int modo_disciplina;
} Aluno;

typedef struct {
    char hora_inicial[6];//usar o horario militar (Ex: 1130 = 11:30)
    char hora_final[6];
    char dias[20];
} Horario;

typedef struct {
    char nome[60];
    int carga;
    char pre_requisitos[100];
    Horario horario;
} Disciplina;

typedef struct {
    char nome[60];
    int carga;
    char pre_requisitos[100];
    Horario horario;
} Eletiva;


void escolha_eletiva(Aluno aluno) {
    Eletiva eletivas[] = {
        {"Calculo 3", 72, "Calculo Diferencial e Integral", {}},
        {"Conceitos de Linguagem de Programação", 72, "Nenhum", {}},
        {"Apredizagem de Máquina", 72, "Calculo 3", {}},
        {"Sisitemas Digitais", 72, "Calculo 3", {}},
        {"Sistemas Distribuidos", 72, "Nenhum", {}},
        {"redes Neurais e Aprendizado Profundo", 72, "Nenhum", {}},
        {"FPGA", 72, "Nenhum", {}},
        {"Interacao Homem-Maquina", 72, "Programcao 3", {}},
        {"Processamento Digital de Imagem", 72, "Computaçao Grafica", {}},
        {"Computcao Evolucionaria", 72, "Nenhum", {}},
        {"Sistemas Embarcados", 72, "Nenhum", {}},
        {"Gerencia de Projeto", 72, "Projeto e Desenvolvimento de Sistemas", {}},
        {"Visao Computacional", 72, "Nenhum", {}},
        {"Ciencia de Dados", 72, "Probabilidade e Estatistica", {}},
        {"Microcontroladores e Aplicacoes", 72, "Nenhum", {}},
        {"Seguranca de Sistemas Computacionais", 72, "Redes de Computadores", {}}
    };
}

void matricula(Aluno aluno) {
    if (aluno.periodo == 1) {
        Disciplina disciplinas[] = {
            {"Programacao 1", 72, "Nenhum", {"15:20", "18:50", "Sex"}},
            {"Matematica Discreta", 72, "Nenhum", {"13:30", "15:10", "Ter, Qui"}},
            {"Calculo Diferencial e Integral", 144, "Nenhum", {"15:20", "18:50", "Ter, Qui"}},
            {"Logica para Programacao", 72, "Nenhum", {"14:20", "17:00", "Seg, Qua"}},
            {"Computacao, Sociedade e Etica", 72, "Nenhum", {"17:10", "18:50", "Seg, Qua"}}
        };

        puts("Sua grade eh:");
        for (int i = 0; i < 5; i++) {
            printf("%s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                   disciplinas[i].nome, disciplinas[i].carga, 
                   disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                   disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        printf("\n");
    } else if (aluno.periodo == 2) {
        Disciplina disciplinas[] = {
            {"Banco de dados", 72, "Nenhum", {"13:30", "15:20", "Seg, Qua"}},
            {"Geometria Analitica", 72, "Nenhum", {"15:20", "17:10", "Seg, Qua"}},
            {"Org. E arq. de Computadores", 72, "Nenhum", {"9:20", "11:00", "Ter, Qui"}},
            {"Estrutra de Dados", 72, "Programacao 1", {"11:10", "12:50", "Ter, Qui"}},
    };
    
        puts("Sua grade é:");
        for (int i = 0; i < 4; i++) {
            printf("%s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                    disciplinas[i].nome, disciplinas[i].carga, 
                    disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                    disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        printf("\n");
    } else if (aluno.periodo == 3) {
        Disciplina disciplinas[] = {
            {"Redes de Computadores", 72, "Programacao 1", {"15:20", "17:00", "Seg, Qui"}},
            {"Teoria dos Grafos", 72,  "Estrutra de Dados e Matematica Discreta", {"13:30", "15:10","Seg, Qui"}},
            {"Probabilidade e Estastistica", 72, "Calculo Diferencial e Integral", {"11:10", "12:50", "Seg, Qua"}},
            {"Algebra Linear", 72, "Geometria Analitica", {"9:20", "11:00", "Seg, Qua"}},
    };
    
        puts("Sua grade eh:");
        for (int i = 0; i < 4; i++) {
            printf("%s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                disciplinas[i].nome, disciplinas[i].carga, 
                disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        printf("\n");
    } else if (aluno.periodo == 4) {
        Disciplina disciplinas[] = {
            {"Programacao 2", 72, "Estrutura de Dados, Banco de dados e Redes de Computadores", {"15:20", "17:00", "Qua"}},
            {"Programacao 3", 72, "Estrutura de Dados, Banco de dados e Redes de Computadores", {"15:20", "17:00", "Ter, QUi"}},
            {"Projeto de Analise de Algoritmos", 72, "Estrutura de Dados e Teoria dos Grafos", {"17:10", "18:50", "Seg, Qui"}},
            {"Teoria da Computacao", 72, "Nenhum", {"13:30", "15:10", "Seg, Qua"}},
    };
    
        puts("Sua grade eh:");
        for (int i = 0; i < 4; i++) {
            printf("%s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                disciplinas[i].nome, disciplinas[i].carga, 
                disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        printf("\n");
    } else if (aluno.periodo == 5) {
        Disciplina disciplinas[] = {
            {"Sietemas Operacionais", 72, "Org. E arq. de Computadores", {"13:30", "15:20", "Seg, Qua"}},
            {"Compiladores", 72,  "Estrutura de Dados e Logica para Computacao", {"15:20", "17:00", "Seg, Qua"}},
            {"Inteligencia Artificial", 72, "Estrutura de Dados e Logica para Computacao", {"15:20", "17:00", "Ter, Qui"}},
            {"Computacao Grafica", 72, "Nenhum", {"17:10", "18:50", "Ter, Qui"}},
    };
    
        puts("Sua grade eh:");
        for (int i = 0; i < 4; i++) {
            printf("%s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                disciplinas[i].nome, disciplinas[i].carga, 
                disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        printf("\n");
    } else if (aluno.periodo == 6) {
        Disciplina disciplinas[] = {
            {"Projeto e Desenvolvimento de Sistemas", 288, "Todas as diciplinas de 1º ao 5º semestre", {"9:20", "15:10", "Seg, Qua, Qui"}},
    };
    
        puts("Sua grade eh:");
        for (int i = 0; i < 1; i++) {
            printf("%s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                disciplinas[i].nome, disciplinas[i].carga, 
                disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        printf("\n");
    } else if (aluno.periodo == 7) {
        Disciplina disciplinas[] = {
            {"Metodologias de Pesquisa e Trabalhos Individual", 72, "Nenhum", {"13:30", "15:10", "Ter, Qui"}},
            {"Nocoes de Direito", 72, "Nenhum", {"15:20", "18:50", "Ter"}},

    };
    
        puts("Sua grade eh:");
        for (int i = 0; i < 2; i++) {
            printf("%s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                disciplinas[i].nome, disciplinas[i].carga, 
                disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        printf("\n");
    }
}

//função para checar se todos os valores digitados na string são letras
int validation_string(char arr[]) {
   for (int i = 0; arr[i] != '\0'; i++) {
       if (!isalpha(arr[i])) {  //validacao de tipo string
           return 0;
       }
   }
   return 1;
}

int validation(char arr[]){
   int len = strlen(arr); //tamanho da string
   
   if (islower(arr[0]) || isspace(arr[0])) { //validacao de espaço e tipo de letra 
       printf("Nome não válido\n");
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
   setlocale(LC_ALL, "pt_BR.utf8");

   Aluno aluno;

   puts("Digite seu nome completo aqui: ");
   fgets(aluno.nome, sizeof(aluno.nome) / sizeof(char), stdin);
   aluno.nome[strcspn(aluno.nome, "\n")] = '\0';

   puts("Digite seu periodo aqui: ");
   scanf("%d", &aluno.periodo);
   getchar();
   
   //validacao do nome 
   if (validation_string(aluno.nome)) {
       validation(aluno.nome);
   }
   else{
        puts("Há caracteres não alfabéticos no seu nome!\n");
        return 1;
   }
   puts(" ");

   //decomposicao do nome e soma de cada um
   puts("Decomposicao do nome, some e resto");
   name_process(aluno.nome);

   printf("\n");

   //matricula do aluno e grade curricular
   matricula(aluno);

   return 0;
}