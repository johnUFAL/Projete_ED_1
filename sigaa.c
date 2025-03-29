#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

typedef struct {
    int id;
    int paga; // 1 - sim, 0 - não
    int carga;
    int periodo;
    wchar_t nome[70];
    wchar_t horario_disc[8];
    //OBS.: estilo de horário do sigaa: 35T56
    //os digítos antes da letra são os dias da semana que haverá aula
    //  2 = segunda, 3 = terça, 4 = quarta ...
    //      a letra representa o turno
    //          T = tarde, M = manhã
    //              e os últimos dígitos são as aulas
    //                  1 = 1° aula, 2 = 2° aula, ..., 6 = 6° aula
    int preRequisitos[3];
    wchar_t pre_requisitos[12];
} Disciplina;

typedef struct {
    int id;
    int carga;
    wchar_t requisito[80];
    double nota;
    wchar_t nome[60];
} MateriasPagas;

typedef struct {
    int enfase; //enfase escolhida
    int tempo_curso; //tempo de curso
    int periodoAtual; //periodo em que se encontra o aluno
    wchar_t nome[60];
    int max_disciplina; //max de disciplinas que ele irá pagar por semestre
    wchar_t turno_disciplina; //turno em que pagará as disciplinas
    MateriasPagas minhaGrade[29]; //variavel que guardará as disciplinas pagas pelo usuário
} Aluno;

typedef struct {
    int carga;
    wchar_t nome[60];
    wchar_t horario_ele[8];
    wchar_t pre_requisitos[100];
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
*/

void aconselhamentoPedagogico (Disciplina obrigatorias[], int max, int periodoAtual)
{
    int turnos[8][2] = {0};
    int p = -1; //periodo
    int t = 0; //posição do indice no array obrigatorias
    
    wchar_t string[8];

    for (int i = 0; i < max; ++i)
    {
        if (obrigatorias[i].paga != 1)
        {
            t = obrigatorias[i].periodo - 1;
            
            //wprintf(L"Periodo: %d: ", obrigatorias[i].periodo);

            wcscpy(string, obrigatorias[i].horario_disc);

            for (int j = 0; string[j] != L'\0'; ++j)
            {
                if (string[j] == 'M')
                {
                    //wprintf(L"M\n");
                    turnos[t][0]++;
                    break;
                }
                else if (string[j] == 'T')
                {
                    //wprintf(L"T\n");
                    turnos[t][1]++;
                    break;
                }
            }
        }
    }

    for (int m = 0; m < 8; ++m)
    {
        wprintf(L"%d° periodo -> Matérias Manhã: %d, Matérias Tarde: %d\n", m + 1, turnos[m][0], turnos[m][1]);
    }

    wprintf(L"Lembre-se! Você está no %d° período, ou seja, você tem de terminar o curso em %d períodos\n", periodoAtual, 12 - periodoAtual);

    return;
}

void inicializarObrigatorias(Disciplina obrigatorias[], int max, FILE * arquivo) //função para inserir as matérias na struct
{
    int i = 0;
    
    //Periodo: 1, Nome: Programacao 1, Id: 359, CH: 72, Requisito: Nenhum, Horario: 6M3456
    //M = manha, T = Tarde, antes da letra sao os dias da semana e depois as aulas
    while ((i < max) && fwscanf(arquivo, L"Periodo: %d, Nome: %69l[^,], Id: %d, CH: %d, Requisito: %109l[^,], Horario: %7l[^\n]\n", &obrigatorias[i].periodo, obrigatorias[i].nome, &obrigatorias[i].id, &obrigatorias[i].carga, obrigatorias[i].pre_requisitos, obrigatorias[i].horario_disc) != EOF)
    {
        //wprintf(L"Periodo: %d, Nome: %ls, Id: %d, CH: %d, Requisito: %ls, Horario: %ls\n", obrigatorias[i].periodo, obrigatorias[i].nome, obrigatorias[i].id, obrigatorias[i].carga, obrigatorias[i].pre_requisitos, obrigatorias[i].horario_disc);
        
        ++i;
        
        if (i > max)
        {
            wprintf(L"Algo deu errado na leitura!");
            return;
        }
    }

    return;
}

int inicializarMateriasPagas(Aluno * aluno, FILE * arquivo) //função para inserir as matérias pagas na struct
{
    int i = 0;
    int max = 29;
    
    //Nome: Joao Victor Duarte do Nascimento, Periodo: 2
    fwscanf(arquivo, L"Nome: %59l[^,], Periodo: %d\n", aluno->nome, &aluno->periodoAtual);

    wprintf(L"Nome: %ls, Periodo: %d\n", aluno->nome, aluno->periodoAtual);
    
    //Nome: Logica para Programacao, Id: 360, CH: 72, Nota: 7.8
    while (fwscanf(arquivo, L"Nome: %59l[^,], Id: %d, CH: %d, Requisito: %79l[^,], Nota: %lf\n", aluno->minhaGrade[i].nome, &aluno->minhaGrade[i].id, &aluno->minhaGrade[i].carga, aluno->minhaGrade[i].requisito, &aluno->minhaGrade[i].nota) != EOF)
    {
        //wprintf(L"Nome: %ls, Id: %d, CH: %d, Requisito: %ls, Horario: %ls\n", obrigatorias[i].periodo, obrigatorias[i]);
        wprintf(L"Nome: %ls, Id: %d, CH: %d, Requisito: %ls, Nota: %lf\n", aluno->minhaGrade[i].nome, aluno->minhaGrade[i].id, aluno->minhaGrade[i].carga, aluno->minhaGrade[i].requisito, aluno->minhaGrade[i].nota);
        
        if (aluno->minhaGrade[i].nota > 7) //caso a nota do aluno seja menor que sete isso indicará que ele trancou a matéria, ou reprovou nela
        {
            ++i;
        }
        
        if (i > max)
        {
            wprintf(L"Algo deu errado na leitura!");
            return -1;
        }
    }

    //wprintf(L"%d\n", i);

    return i;
}

void suaSituacao (int resto[], Aluno * ptr) //essa função descreve os critérios estabelecidos pela professora
{
    wprintf(L"=============================CRITÉRIOS=============================\n");
    
    wprintf(L"-> Seu máximo de disciplinas nesse semestre será de ");
    
    switch (resto[0])
    {
        case 0:
            wprintf(L"10 disciplinas\n");
            ptr->max_disciplina = 10;
            break;

        case 1:
            wprintf(L"8 disciplinas\n");    
            ptr->max_disciplina = 8; 
            break;

        case 2:
            wprintf(L"6 disciplinas\n");
            ptr->max_disciplina = 6;
            break;

        default:
            wprintf(L"#\nERRO! Valor fora do intervalo esperado!\n");
    }

    wprintf(L"-> Você terminará o curso ");

    switch (resto[1])
    {
        case 0:
            wprintf(L"no menor tempo possível\n");
            ptr->tempo_curso = 8;
            break;

        case 1:
            wprintf(L"no maior tempo possível\n");  
            ptr->tempo_curso = 12;     
            break;

        case 2:
            wprintf(L"no tempo médio possível\n");
            ptr->tempo_curso = 10;
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

    wchar_t copiaNome[60];
    wchar_t * ultimaParada; //ponteiro que guarda a posição de onde a função wcstok parou
    wchar_t * delimitadores = L" "; //ponteiro que armazena os delimitadores da função wcstok que nesse caso é somente o espaço

    int j = 0; //indice para o array de inteiros e limitador de palavras
    int soma = 0; //guardará a soma das letras 
    
    while (j < 4) //loop para caso o nome seja pequeno e não consiga suprir os requisitos
    {
        wcscpy(copiaNome, aluno.nome); //apesar de aluno.nome ser uma cópia iremos criar mais uma cópia por prevenção
        
        //retorna uma substring da string nome
        //recebe uma string, seus delimitadores e a última posição do ponteiro que é inicialmente NULL
        wchar_t * token = wcstok(copiaNome, delimitadores, &ultimaParada); 

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
                //wprintf(L"%d° palavra do nome: %ls, tem %ld letras e a soma das suas letras eh: %d\n", j + 1, token, wcslen(token), soma);
                j++;
            }
    
            token = wcstok(NULL, delimitadores, &ultimaParada); //esse NULL é para dizer para ela continuar o processo
        }        
    }
    
    return;
}

#define MAX_OBRIG 24 //n° max de matérias obrigatórias fora as das ênfases
#define MAXR 4 //n° max de restos
 
//nome completo: Erivaldo Jose Da Silva Santos Junior
//nome modelo: erivaldo jose silva santos

int main() {
   setlocale(LC_ALL, "");

   fwide(stdout, 1); //força stdout a operar no modo wide-character, reduzindo problemas com wprintf

   Aluno aluno;
   Disciplina obrigatorias[MAX_OBRIG] = {0}; //array de structs que irá conter as matérias obrigatórias, 24 obrigatórias fora as da ênfases
   int resto[MAXR]; //guardará o resto das divisões das particões do nome
   int materiasPagas = 0; //guardará um indice de controle sobre as disciplinas pagas

   FILE * disciplinasObrigatorias;
   FILE * historico;

   disciplinasObrigatorias = fopen("obrigatorias.txt", "r, ccs=UTF-8"); //abre no formato Unicode
   historico = fopen("entrada.txt", "r, ccs=UTF-8");

   if (disciplinasObrigatorias == NULL || historico == NULL)
   {
        wprintf(L"Erro ao abrir o arquivo externo!\n"); //para caso tenha havido erro na abertura do arquivo
        return 1;
   }

   inicializarObrigatorias(obrigatorias, MAX_OBRIG, disciplinasObrigatorias); //irá inserir todas as disciplinas obrigatórias do arquivo externo para a struct
   materiasPagas = inicializarMateriasPagas(&aluno, historico); //função para receber o histórico do usuário e em seguida no array obrigatorias irá indicar quais matérias já foram pagas

   if (materiasPagas == -1) //prevenção de erros
   {
        wprintf(L"Erro na leitura da entrada\n");
   }

   for (int i = 0; i < materiasPagas; ++i) //loop para informar no array obrigatorias quais materias ele já pagou
   //vai comparando até achar a matéria correspondente
   {
        for (int j = 0; j < MAX_OBRIG; ++j)
        {
            if (aluno.minhaGrade[i].id == obrigatorias[j].id)
            {
                wprintf(L"%d e %d\n", aluno.minhaGrade[i].id, obrigatorias[j].id);
                
                obrigatorias[j].paga = 1; //o aluno já pagou essa matéria
                break;
            }
        }
   }

   while (1) //loop para evitar erros na inserção do nome modelo
   {
       wprintf(L"Digite o nome modelo completo a seguir: ");
       fgetws(aluno.nome, sizeof(aluno.nome) / sizeof(wchar_t), stdin);
    
       wchar_t * ptr = wcschr(aluno.nome, L'\n'); //ponteiro wchar_t para a 1° aparição do '\n' que será retornado pela função wcschar
    
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

   //decomposicao do nome, soma e divisão para obtenção do seu resto
   name_process(aluno, resto);

   /*wprintf(L"Restos:\n");
   
   for (int i = 0; i < 4; ++i)
   {
        wprintf(L"resto[%d] = %d\n", i + 1, resto[i]);
   }*/

   suaSituacao(resto, &aluno); //será passado o endereço da variável aluno para que seu valor seja integralmente alterado

   aconselhamentoPedagogico(obrigatorias, MAX_OBRIG, aluno.periodoAtual);
   
   fclose(disciplinasObrigatorias); //fechamento do ponteiro
   fclose(historico);

   return 0;
}