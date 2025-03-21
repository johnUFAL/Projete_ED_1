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
    int materias_pagas[29]; //matérias já realizadas, ou pagas, pelo aluno
    int horas_pagas; //com as possíveis matérias já pagas, logo o aluno também cumpriu com suas horas obrigatórias
    int periodo; //periodo em que se encontra o aluno
    int max_disciplina; //max de disciplinas que ele irá pagar por semestre
    int tempo_curso; //tempo de curso
    int enfase; //enfase escolhida
    int turno_disciplina; //turno em que pagará as disciplinas
} Aluno;

/*typedef struct {
    char hora_inicial[6]; //usar o horário militar (Ex: 1130 = 11:30) 
    //OBS.: seria interessante mudar para o estilo de horário do sigaa que eh: 35T56 (
    //os dois primeiros números dizem os dias
    //  2 = segunda, 3 = terça, 4 = quarta, e 5 = quinta
    //      a letra do meio é o turno
    //          T = tarde, M = manhã
    //              e os dois últimos dígitos as aulas
    //                  1 = 1° aula, 2 = 2° aula, ..., 6 = 6° aula
    char hora_final[6];
    char dias[20];
} Horario; */

typedef struct {
    char nome[60];
    int id;
    int carga;
    int periodo;
    char pre_requisitos[100];
    char horario_disc[7];
} Disciplina;

typedef struct {
    char nome[60];
    int carga;
    char pre_requisitos[100];
    char horario_ele[7];
} Eletiva;


/*void escolha_eletiva(Aluno aluno) {
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
    wprintf(L"Seu periodo: %d\n", aluno.periodo);

    if (aluno.periodo != 1) //se o aluno não está no 1° período, logo eles já pagou algumas matérias e já cumpriu certa quantidade de horas
    {
        for (int i = 0; i < aluno.periodo; ++i)
        {
            //aluno.materias_pagas += disciplinas
        }
    }
    if (aluno.periodo == 1) {
        Disciplina disciplinas[] = {
            {"Programacao 1", 359, 72, "Nenhum", {"15:20", "18:50", "Sex"}},
            {"Matematica Discreta", 362, 72, "Nenhum", {"13:30", "15:10", "Ter, Qui"}},
            {"Calculo Diferencial e Integral", 363, 144, "Nenhum", {"15:20", "18:50", "Ter, Qui"}},
            {"Logica para Programacao", 360, 72, "Nenhum", {"14:20", "17:00", "Seg, Qua"}},
            {"Computacao, Sociedade e Etica", 361, 72, "Nenhum", {"17:10", "18:50", "Seg, Qua"}}
        };

        wprintf(L"Sua grade eh:\n");
        for (int i = 0; i < 5; i++) {
            wprintf(L"-> %s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                   disciplinas[i].nome, disciplinas[i].carga, 
                   disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                   disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        wprintf(L"\n");
    } else if (aluno.periodo == 2) {
        Disciplina disciplinas[] = {
            {"Banco de dados", 365, 72, "Nenhum", {"13:30", "15:20", "Seg, Qua"}},
            {"Geometria Analitica", 367, 72, "Nenhum", {"15:20", "17:10", "Seg, Qua"}},
            {"Org. E arq. de Computadores", 366, 72, "Nenhum", {"9:20", "11:00", "Ter, Qui"}},
            {"Estrutra de Dados", 364, 72, "Programacao 1", {"11:10", "12:50", "Ter, Qui"}},
    };
    
        wprintf(L"Sua grade eh:\n");
        for (int i = 0; i < 4; i++) {
            wprintf(L"-> %s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                    disciplinas[i].nome, disciplinas[i].carga, 
                    disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                    disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        wprintf(L"\n");
    } else if (aluno.periodo == 3) {
        Disciplina disciplinas[] = {
            {"Redes de Computadores", 368, 72, "Programacao 1", {"15:20", "17:00", "Seg, Qui"}},
            {"Teoria dos Grafos", 369, 72,  "Estrutra de Dados e Matematica Discreta", {"13:30", "15:10","Seg, Qui"}},
            {"Probabilidade e Estastistica", 370, 72, "Calculo Diferencial e Integral", {"11:10", "12:50", "Seg, Qua"}},
            {"Algebra Linear", 371, 72, "Geometria Analitica", {"9:20", "11:00", "Seg, Qua"}},
    };
    
        wprintf(L"Sua grade eh:\n");
        for (int i = 0; i < 4; i++) {
            wprintf(L"-> %s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                disciplinas[i].nome, disciplinas[i].carga, 
                disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        wprintf(L"\n");
    } else if (aluno.periodo == 4) {
        Disciplina disciplinas[] = {
            {"Programacao 2", 372, 72, "Estrutura de Dados, Banco de dados e Redes de Computadores", {"15:20", "17:00", "Qua"}},
            {"Programacao 3", 373, 72, "Estrutura de Dados, Banco de dados e Redes de Computadores", {"15:20", "17:00", "Ter, QUi"}},
            {"Projeto de Analise de Algoritmos", 374, 72, "Estrutura de Dados e Teoria dos Grafos", {"17:10", "18:50", "Seg, Qui"}},
            {"Teoria da Computacao", 376, 72, "Nenhum", {"13:30", "15:10", "Seg, Qua"}},
    };
    
        wprintf(L"Sua grade eh:\n");
        for (int i = 0; i < 4; i++) {
            wprintf(L"-> %s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                disciplinas[i].nome, disciplinas[i].carga, 
                disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        wprintf(L"\n");
    } else if (aluno.periodo == 5) {
        Disciplina disciplinas[] = {
            {"Sistemas Operacionais", 378, 72, "Org. E arq. de Computadores", {"13:30", "15:20", "Seg, Qua"}},
            {"Compiladores", 379, 72,  "Estrutura de Dados e Logica para Computacao", {"15:20", "17:00", "Seg, Qua"}},
            {"Inteligencia Artificial", 380, 72, "Estrutura de Dados e Logica para Computacao", {"15:20", "17:00", "Ter, Qui"}},
            {"Computacao Grafica", 381, 72, "Nenhum", {"17:10", "18:50", "Ter, Qui"}},
    };
    
        wprintf(L"Sua grade eh:\n");
        for (int i = 0; i < 4; i++) {
            wprintf(L"-> %s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                disciplinas[i].nome, disciplinas[i].carga, 
                disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        wprintf(L"\n");
    } else if (aluno.periodo == 6) {
        Disciplina disciplinas[] = {
            {"Projeto e Desenvolvimento de Sistemas", 382, 288, "Todas as diciplinas de 1º ao 5º semestre", {"9:20", "15:10", "Seg, Qua, Qui"}},
    };
    
        wprintf(L"Sua grade eh:\n");
        for (int i = 0; i < 1; i++) {
            wprintf(L"-> %s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                disciplinas[i].nome, disciplinas[i].carga, 
                disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        wprintf(L"\n");
    } else if (aluno.periodo == 7) {
        Disciplina disciplinas[] = {
            {"Metodologias de Pesquisa e Trabalhos Individual", 386, 72, "Nenhum", {"13:30", "15:10", "Ter, Qui"}},
            {"Nocoes de Direito", 387, 72, "Nenhum", {"15:20", "18:50", "Ter"}},

    };
    
        wprintf(L"Sua grade eh:\n");
        for (int i = 0; i < 2; i++) {
            wprintf(L"-> %s - Carga: %d, Horario: %s - %s, Pre-requisitos: %s, Dias: %s\n",
                disciplinas[i].nome, disciplinas[i].carga, 
                disciplinas[i].horario.hora_inicial, disciplinas[i].horario.hora_final, 
                disciplinas[i].pre_requisitos, disciplinas[i].horario.dias);
        }
        wprintf(L"\n");
    }

    return;
}*/

/*

typedef struct {
    char hora_inicial[6]; //usar o horário militar (Ex: 1130 = 11:30)
    char hora_final[6];
    char dias[20];
} Horario;

typedef struct {
    char nome[60];
    int id;
    int carga;
    char pre_requisitos[100];
    Horario horario;
} Disciplina;
*/

void inicializarObrigatorias(Disciplina obrigatorias[], int max, FILE * arquivo)
{
    int i = 0;
    
    //Periodo: 1, Nome: Programacao 1, Id: 359, CH: 72, Requisito: Nenhum, Horario: M = manha, T = Tarde, antes da letra sao os dias da semana e depois as aulas
    while (fwscanf(arquivo, L"Periodo: %d, Nome: %59[^,], Id: %d, CH: %d, Requisito: %99[^,], Horario: %7[^,]\n", &obrigatorias[i].periodo, obrigatorias[i].nome, &obrigatorias[i].id, &obrigatorias[i].carga, obrigatorias[i].pre_requisitos, obrigatorias[i].horario_disc != EOF))
    {
        wprintf(L"Periodo: %d, Nome: %ls, Id: %d, CH: %d, Requisito: %ls, Horario: %ls\n", obrigatorias[i].periodo, obrigatorias[i].nome, obrigatorias[i].id, obrigatorias[i].carga, obrigatorias[i].pre_requisitos, obrigatorias[i].horario_disc);
        
        ++i;
        
        if (i >= max)
        {
            wprintf(L"Algo deu errado na leitura!");
            return;
        }
    }

    return;
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

/*
 wchar_t nome[50];
    int materias_pagas[29]; //matérias já realizadas, ou pagas, pelo aluno
    int horas_pagas; //com as possíveis matérias já pagas, logo o aluno também cumpriu com suas horas obrigatórias
    int periodo; //periodo em que se encontra o aluno
    int max_disciplina; //max de disciplinas que ele irá pagar por semestre
    int tempo_curso; //tempo de curso
    int enfase; //enfase escolhida
    int turno_disciplina; //turno em que pagará as disciplinas
    */

#define MAX_OBRIG 24

int main() {
   setlocale(LC_ALL, "");

   fwide(stdout, 1); //força stdout a operar no modo wide-character, reduzindo problemas com wprintf

   Aluno aluno = {.materias_pagas = {0}, .horas_pagas = 0}; //inicializando algumas variáveis
   Disciplina obrigatorias[MAX_OBRIG]; //array de structs que irá conter as matérias obrigatórias, 24 obrigatórias fora as da ênfases
   int resto[MAXR]; //guardará o resto das divisões das particões do nome

   FILE * disciplinasObrigatorias;

   disciplinasObrigatorias = wfopen(L"obrigatorias.txt", L"r");

   if (disciplinasObrigatorias == NULL)
   {
        wprintf(L"Erro ao abrir o arquivo externo!\n"); //mostra o erro ao sistema
        return 1;
   }

   inicializarObrigatorias(obrigatorias, MAX_OBRIG, disciplinasObrigatorias); //irá inserir as disciplinas obrigatórias do arquivo externo para a struct

   while (1) //loop para dar mais uma chance do usuário consertar seu erro
   {
       wprintf(L"Digite seu nome completo aqui: ");
       fgetws(aluno.nome, sizeof(aluno.nome) / sizeof(wchar_t), stdin);
    
       wchar_t * ptr = wcschr(aluno.nome, L'\n'); //ponteiro wchar_t para a 1° aparição do '\n'
    
       if (ptr)
       {
            *ptr = L'\0'; //substituindo o '\n' por '\0'
       }
    
       //validacao do nome 
       if (!validation_string(aluno)) {
           wprintf(L"Existe caracteres não alfabéticos no seu nome! Vamos recomeçar!\n");
       }
       else{
            break;
       }
   }

   while (1) //loop para dar mais uma chance do usuário consertar seu erro
   {
       wprintf(L"Digite seu período aqui: ");
       wscanf(L"%d", &aluno.periodo);
       getwchar();
    
       if (aluno.periodo < 1 || aluno.periodo > 8)
       {
            wprintf(L"Uepa! Valor inserido fora do intervalo! Vamos recomeçar!\n");
       }
       else{
            break;
       }
    }
    
    wprintf(L"%d\n", aluno.periodo);

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
   
   fclose(disciplinasObrigatorias);

   return 0;
}