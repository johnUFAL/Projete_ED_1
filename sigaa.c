#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#define MAXR 4 //n° max de restos
 
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

void suaSituacao (int resto[]) //essa função descreve os critérios estabelecidos pela professora
{
    wprintf(L"=============================CRITÉRIOS=============================\n");
    
    wprintf(L"-> Seu máximo de disciplinas nesse semestre será de ");
    
    switch (resto[0])
    {
        case 0:
            wprintf(L"10 disciplinas\n");
            break;

        case 1:
            wprintf(L"8 disciplinas\n");    
            break;

        case 2:
            wprintf(L"6 disciplinas\n");
            break;

        default:
            wprintf(L"#\nERRO! Valor fora do intervalo esperado!\n");
    }

    wprintf(L"-> Você terminará o curso ");

    switch (resto[1])
    {
        case 0:
            wprintf(L"no menor tempo possível\n");
            break;

        case 1:
            wprintf(L"no maior tempo possível\n");    
            break;

        case 2:
            wprintf(L"no tempo médio possível\n");
            break;

        default:
            wprintf(L"#\nERRO! Valor fora do intervalo esperado!\n");
    }

    wprintf(L"-> O critério de escolha de suas ênfases será ");

    switch (resto[2])
    {
        case 0:
            wprintf(L"a de sua escolha\n");
            break;

        case 1:
            wprintf(L"a que diminui o tempo de conclusão do curso\n");    
            break;

        case 2:
            wprintf(L"nenhuma. Você não irá pegar nenhuma ênfase\n");
            break;

        default:
            wprintf(L"#\nERRO! Valor fora do intervalo esperado!\n");
    }

    wprintf(L"-> A escolha das disciplinas se dará ");

    switch (resto[3])
    { 
        case 0:
            wprintf(L"por aquelas que ocuparem o menor número de dias possíveis\n");
            break;

        case 1:
            wprintf(L"por pertencerem ao mesmo turno\n");    
            break;

        case 2:
            wprintf(L"por um limite de 3 disciplinas no máximo por dia, e que o aluno deva ir todos os dias a ufal\n");
            break;

        default:
            wprintf(L"#\nERRO! Valor fora do intervalo esperado!\n");
    }

        return;
}

//função para checar se todos os valores digitados na string são letras
int validation_string(Aluno aluno) {
    for (int i = 0; aluno.nome[i] != L'\0'; ++i)
    {
        if (!(iswalpha(aluno.nome[i]) || iswspace(aluno.nome[i]))) //validacao de tipo string
        {
            return 0;
        }
    }

   return 1;
}

int value_string(wchar_t letra) { 
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

    wchar_t copiaNome[50];
    wchar_t * ultimaParada; //ponteiro que guarda a posição de onde a função wcstok parou
    wchar_t * delimitadores = L" "; //delimitador = espaço

    wcscpy(copiaNome, aluno.nome); //apesar de aluno.nome ser uma cópia iremos criar mais uma cópia por prevenção

    wchar_t * token = wcstok(aluno.nome, delimitadores, &ultimaParada); //como aluno.nome é uma cópia iremos utiliza-la

    int j = 0; //indice para o array de inteiros
    int soma = 0; //guardará a soma das letras 

    while (token != NULL) //vai separar e ler cada partição, ou palavra, do nome
    {
        if (j > 3) //para caso o nome da pessoa seja muito extenso
        {
            break;
        }

        if (wcslen(token) > 3) //caso o tamanho da palavra for <= 3 a condição irá ignorar essa palavra e vai pular para a próxima
        {
            soma = name_sum(token);
            resto[j] = (soma % 3);
            j++;
            wprintf(L"%d° palavra do nome: %ls, tem %ld letras e a soma das suas letras eh: %d\n", j + 1, token, wcslen(token), soma);
            
        }

        token = wcstok(NULL, delimitadores, &ultimaParada);
    }

    if (j < 3) //caso o nome não seja grande o suficiente iremos refazer o processo de particionamento
    {
        //resetando os ponteiros
        token = NULL;
        ultimaParada = NULL;
        
        token = wcstok(copiaNome, delimitadores, &ultimaParada); //é aqui onde iremos utilizar nossa cópia de segurança

        while (token != NULL)
        {
            if (j > 3) //para caso o nome já tenha ultrapassado o necessário
            {
                break;
            }

            if (wcslen(token) > 3) //caso o tamanho da palavra for <= 3 a condição irá ignorar essa palavra e vai pular para a próxima
            {
                soma = name_sum(token);
                resto[j] = (soma % 3);
                j++;
                wprintf(L"%d° palavra do nome: %ls, tem %ld letras e a soma das suas letras eh: %d\n", j + 1, token, wcslen(token), soma);
            }

            token = wcstok(NULL, delimitadores, &ultimaParada);
        }
    }

    return;
}

int main() {
   setlocale(LC_ALL, "");

   fwide(stdout, 1); //força stdout a operar no modo wide-character, reduzindo problemas com wprintf

   Aluno aluno;
   int resto[MAXR]; //guardará o resto das divisões das particões do nome

   wprintf(L"Digite seu nome completo aqui: ");
   fgetws(aluno.nome, sizeof(aluno.nome) / sizeof(wchar_t), stdin);

   wchar_t * ptr = wcschr(aluno.nome, L'\n'); //ponteiro wchar_t para a 1° aparição do '\n'

   if (ptr)
   {
        *ptr = L'\0'; //substituindo o '\n' por '\0'
   }

   wprintf(L"Digite seu período aqui: ");
   wscanf(L"%d", &aluno.periodo);
   getwchar();
   
   //validacao do nome 
   if (!validation_string(aluno)) {
       wprintf(L"Existe caracteres não alfabéticos no seu nome!\n");
       return 1;
   }

   //decomposicao do nome, soma e divisão para obtenção do seu resto
   wprintf(L"Decomposição do nome, soma e resto\n");
   name_process(aluno, resto);

   wprintf(L"Restos:\n");
   
   for (int i = 0; i < 4; ++i)
   {
        wprintf(L"resto[%d] = %d\n", i + 1, resto[i]);
   }

   suaSituacao(resto);

   //matricula do aluno e grade curricular
   //matricula(aluno);

   return 0;
}