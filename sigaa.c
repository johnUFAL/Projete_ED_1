#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
 
//nome completo: Erivaldo Jose Da Silva Santos Junior
//nome teste: erivaldo jose silva santos

typedef struct {
    wchar_t nome[50];
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
int validation_string(Aluno aluno) {
    for (int i = 0; aluno.nome != L'\0'; ++i)
    {
        if (!iswapha(aluno.nome[i])) //validacao de tipo string
        {
            return 0;
        }
    }

   return 1;
}

int value_string(wchar_t letra) { //revisar melhor forma de usar palavras com acentos!!!!!!!!!!!!!!!!!!!!!!!!
   switch (letra) {
       case L'q': return 1; case L'w': return 6; case L'e': return 7;
       case L'r': return 6; case L't': return 5; case L'y': return 2;
       case L'u': return 3; case L'i': return 8; case L'o': return 9;
       case L'p': return 4; case L'á': return 3; case L'ã': return 4;
       case L'a': return 2; case L's': return 5; case L'd': return 8;
       case L'f': return 7; case L'g': return 4; case L'h': return 1;
       case L'j': return 4; case L'k': return 7; case L'l': return 8;
       case L'ç': return 5; case L'é': return 2; case L'í': return 3;
       case L'z': return 3; case L'x': return 4; case L'c': return 9;
       case L'v': return 8; case L'b': return 3; case L'n': return 2;
       case L'm': return 5; case L'ó': return 6; case L'õ': return 7;
       case L'ô': return 6; case L'â': return 1; case L'ê': return 2;
       default: return 0;
   }
}

int name_sum(wchar_t *nome) {
   int soma = 0;

   for (int i = 0; nome[i] != L'\0'; ++i)
   {
        soma += value_string(towlower(nome[i]));
   }
   
   return soma;
}

//função para separação do nome em partes para fazer a divisão
void name_process(Aluno aluno, int resto[]) {

    wchar_t * ultimaParada; //ponteiro que guarda a posição de onde a função wcstok parou
    wchar_t * delimitadores = " "; //delimitador = espaço
    wchar_t * token = wcstok(aluno.nome, delimitadores, &ultimaParada); //como a struct foi copiada para a função não é necessário fazer uma cópia da string

    int j = 0; //indice para o array inteiro de restos

    wprintf(L"Resultado da divisão por 3 (resto):");
    while (token != NULL) 
    {
        
        if (wcslen(token) > 3)
        {
            wprintf(L"%d palavra: %ls\n", j + 1, token);
            resto[j] = (name_sum(token) % 3);
            j++;
        }

        token = wcstok(NULL, delimitadores, &ultimaParada);
    }

    return;
}

int main() {
   setlocale(LC_ALL, "pt_BR.utf8");

   Aluno aluno;
   int resto[4]; //guardará o resto das divisões das particões do nome

   wprintf(L"Digite seu nome completo aqui: ");
   fgetws(aluno.nome, sizeof(aluno.nome) / sizeof(wchar_t), stdin);

   wchar_t * ptr = wcschr(aluno.nome, L'\n'); //ponteiro wchar_t para a 1° aparição do '\n'

   if (ptr)
   {
        *ptr = L'\0'; //substituindo o '\n' por '\0'
   }

   wprintf("Digite seu período aqui: ");
   wscanf("%d", &aluno.periodo);
   getwchar();
   
   //validacao do nome 
   if (!validation_string(aluno)) {
       wprintf("Há caracteres não alfabéticos no seu nome!\n");
       return 1;
   }

   //decomposicao do nome e soma de cada um
   wprintf("Decomposição do nome, soma e resto");
   name_process(aluno, resto);

   printf("\n");

   //matricula do aluno e grade curricular
   matricula(aluno);

   return 0;
}