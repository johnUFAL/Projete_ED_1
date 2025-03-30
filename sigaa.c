#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

typedef struct {
    int paga; // 1 - sim, 0 - não
    int peso;
    int carga;
    int periodo;
    wchar_t id[10];
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
    wchar_t pre_requisitos[24];
} Disciplina;

typedef struct {
    double nota;
    wchar_t id[10];
    wchar_t nome[60];
} MateriasPagas;

typedef struct {
    int enfase; //enfase escolhida
    int tempo_curso; //tempo de curso
    int periodoAtual; //periodo em que se encontra o aluno
    int max_disciplina; //max de disciplinas que ele irá pagar por semestre
    wchar_t nome[60];
    wchar_t turno_disciplina; //turno em que pagará as disciplinas
    MateriasPagas minhaGrade[29]; //variavel que guardará as disciplinas pagas pelo usuário
} Aluno;

typedef struct {
    int carga;
    wchar_t id[10];
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

//vai dá a distribuição das matérias ainda não pagas de todos os períodos
void aconselhamentoPedagogico (Disciplina obrigatorias[], int max, Aluno * aluno, int materiasPagas)
{
    int turnos[8][2] = {0};
    int t = 0; //posição do indice no array obrigatorias

    for (int i = 0; i < max; ++i)
    {
        if (obrigatorias[i].paga != 1)
        {
            t = obrigatorias[i].periodo - 1;
            
            //wprintf(L"Periodo: %d: ", obrigatorias[i].periodo);

            for (int j = 0; obrigatorias[i].horario_disc[j] != L'\0'; ++j)
            {
                if (obrigatorias[i].horario_disc[j] == L'M')
                {
                    //wprintf(L"M\n");
                    turnos[t][0]++;
                    break;
                }
                else if (obrigatorias[i].horario_disc[j] == L'T')
                {
                    //wprintf(L"T\n");
                    turnos[t][1]++;
                    break;
                }
            }
        }
    }

    int manha = 0;
    int tarde = 0;

    for (int i = 0; i < 8; ++i) //soma o total de disciplinas por turno
    {
        manha += turnos[i][0];
        tarde += turnos[i][1];
    }

    wprintf(L"============================INFORMAÇÕES============================\n");

    for (int m = 0; m < 8; ++m)
    {
        wprintf(L"%d° periodo -> Matérias Manhã: %d, Matérias Tarde: %d\n", m + 1, turnos[m][0], turnos[m][1]);
    }

    wprintf(L"Ou seja, você tem %d disciplinas de manhã e %d disciplinas a tarde não pagas\n", manha, tarde);
    wprintf(L"Lembre-se! Você está no %d° período, ou seja, você tem de terminar o curso em %d períodos\n", aluno->periodoAtual, aluno->tempo_curso - aluno->periodoAtual);
    
    int totalPeriodos = ((manha % aluno->max_disciplina) + (manha / aluno->max_disciplina)) + ((tarde / aluno->max_disciplina) + tarde % aluno->max_disciplina); //isso é uma soma bem grosseira, não sendo levado em conta os horários das aulas
    
    wprintf(L"Na sua situação atual você consegue terminar o curso em no mínimo %d períodos. Lhe restando %d períodos\n", totalPeriodos, aluno->tempo_curso - (totalPeriodos + aluno->periodoAtual));

    wprintf(L"====================================================================\n");
    
    
    int  materiasNaoPagas = 0;
    
    for (int j = 0; j < max; ++j) //um loop para saber a qtd de matérias que ainda não foram pagas
    {
       if (obrigatorias[j].paga != 1)
       {
           materiasNaoPagas++;
       }
    }

    int menorPeriodo = 999; //guardará o menor período entre todas as matérias que não foram pagas em seus respectivos períodos
    int menorInd = 0; //guardará o índice do menor período
    int IndperiodoSeguinte = 0; //armazenará o índice de onde começa o próximo período

    wprintf(L"%d\n", aluno->periodoAtual);

    int z = 4;
    while (z > 0 || (aluno->periodoAtual < aluno->tempo_curso)) //materiasNaoPagas > 0
    {
        materiasNaoPagas = 0;
        
        for (int j = menorInd; j < max; ++j) //o loop vai das matérias do primeiro período até encontrar a disciplina no menor período que ainda não foi paga
        {
            if ((obrigatorias[j].paga == 0) && (obrigatorias[j].periodo < menorPeriodo)) //se a disciplina não foi paga e se seu período é menor que o menorPeríodo
            {
                menorPeriodo = obrigatorias[j].periodo;
                menorInd = j;
                //temos a disciplina não paga no menor período e a sua posição 
            }
    
            if (obrigatorias[j].periodo > menorPeriodo)
            {
                IndperiodoSeguinte = j;
                break; //agora temos o índice de onde irá comecar o seguinte período após o menor período
            }
        }

        int requisitos = 0; //0 = não pagos, 1 = pagos
        int manha = 0; //qtd de disciplinas no turno da manhã que podem ser escolhidas
        int tarde = 0; //qtd de disciplinas no turno da tarde que podem ser escolhidas
        int pesoManha = 0; //maior peso das matérias da manhã
        int pesoTarde = 0; //maior peso das matérias da tarde

        wchar_t letras[] = L"MT"; //letras de interesse a serem analisadas
        wchar_t * ptr; //ponteiro para a 1° ocorrência de determinada letra

        //wprintf(L"Peso tarde: %d\nPeso manha: %d\nTarde: %d\nManha: %d\n", pesoTarde, pesoManha, tarde, manha);

        for (int j = menorInd; j < IndperiodoSeguinte; ++j) //verifica todas as disciplinas não pagas no menor período
        {
            //faz a checagem dos pré requisitos
            wchar_t copiaID[10];
            wchar_t * ultimaParada; //ponteiro que guarda a posição de onde a função wcstok parou
            wchar_t * delimitadores = L"_"; //ponteiro que armazena os delimitadores da função wcstok que nesse caso é somente o underline

            wcscpy(copiaID, obrigatorias[j].pre_requisitos); //função para fazer um cópia do obrigatorias[j].pre_requisitos
                
            //retorna uma substring da string obrigatorias[j].pre_requisitos
            //recebe uma string, seus delimitadores e a última posição do ponteiro que é inicialmente NULL
            wchar_t * token = wcstok(copiaID, delimitadores, &ultimaParada); 

            while (token != NULL) //vai separar e ler cada partição, ou palavra, do copiaID
            {
                requisitos = 0; //para caso haja mais de um requisito a variável reseta para que caso o aluno já tenha pagado essa disciplina
                //a variável "requisitos" receberá 1 como valor, caso não, o aluno não cumpre com todas as exigências
                
                for (int k = 0; k < materiasPagas; ++k) //vai checar todos os id's das matérias pagas pelo usuário
                {
                    if ((wcscmp(aluno->minhaGrade[k].id, token) == 0) || (wcscmp(token, L"0") == 0)) //comparando as matérias pagas com os requisitos dessa posterior matéria
                    {
                        requisitos = 1;
                    }
                }
                
                token = wcstok(NULL, delimitadores, &ultimaParada); //esse NULL é para dizer para ela continuar o processo
            }        

            for (int i = 0; letras[i] != L'\0'; ++i) //loop para quantificar a qtd de disciplinas em cada turno
            {
                ptr = wcschr(obrigatorias[j].horario_disc, letras[i]); //ponteiro que retorna a 1° ocorrência de determinada letra

                if (ptr != NULL)
                {
                    if ((letras[i] == L'M') && (obrigatorias[j].paga != 1) && (requisitos == 1))
                    //o turno da disciplina deve ser de manhã
                    //ele ainda não deve ter sido paga
                    //e o aluno deve cumprir com todos os seus requisitos
                    {
                        manha++;

                        if (obrigatorias[j].peso >= pesoManha) //vai armazenar o maior peso entre as disciplinas da manhã
                        {
                            pesoManha = obrigatorias[j].peso;
                        }
                    }
                    else if ((letras[i] == L'T') && (obrigatorias[j].paga != 1) && (requisitos == 1))
                    //o turno da disciplina deve ser de manhã
                    //ele ainda não deve ter sido paga
                    //e o aluno deve cumprir com todos os seus requisitos
                    {
                        tarde++;

                        if (obrigatorias[j].peso >= pesoTarde) //vai armazenar o maior peso entre as disciplinas da tarde
                        {
                            pesoTarde = obrigatorias[j].peso;
                        }
                    }
                }
            }
        }

        ptr = NULL;

        wprintf(L"Peso tarde: %d\nPeso manha: %d\nTarde: %d\nManha: %d\n", pesoTarde, pesoManha, tarde, manha);

        if (pesoTarde > pesoManha)
        {
             wprintf(L"\033[4mPeríodo Atual: %d. Suas disciplinas no próximo período (%d°) serão a tarde. São elas:\033[0m\n", aluno->periodoAtual, aluno->periodoAtual + 1);
         
             for (int j = menorInd; j < IndperiodoSeguinte; ++j)
             {
                for (int i = 0; letras[i] != L'\0'; ++i) 
                {
                    ptr = wcschr(obrigatorias[j].horario_disc, letras[i]); //ponteiro que retorna a 1° ocorrência de determinada letra

                    if (ptr != NULL)
                    {
                        if ((letras[i] == L'T') && (obrigatorias[j].paga != 1)) //vai imprimir somente se a matéria for do turno da tarde e se ele ainda não foi paga
                        {
                            wprintf(L"|\033[4mNome: %-40ls| Id: %-12ls| Horário: %10ls\033[0m|\n", obrigatorias[j].nome, obrigatorias[j].id, obrigatorias[j].horario_disc);
                            obrigatorias[j].paga = 1;

                            //inferimos que o aluno passou nessas matérias para que possamos construir o restante do aconselhamento
                            wcscpy(aluno->minhaGrade[materiasPagas].id, obrigatorias[j].id); 
                            wcscpy(aluno->minhaGrade[materiasPagas].nome, obrigatorias[j].nome);
                            materiasPagas++;
                        }
                    }
                }
             }
        }
        else if (pesoTarde <= pesoManha)
        {
            wprintf(L"\033[4mPeríodo Atual: %d. Suas disciplinas no próximo período (%d°) serão de manhã. São elas:\033[0m\n", aluno->periodoAtual, aluno->periodoAtual + 1);
            
            for (int j = menorInd; j < IndperiodoSeguinte; ++j)
            {
                for (int i = 0; letras[i] != L'\0'; ++i) 
                {
                    ptr = wcschr(obrigatorias[j].horario_disc, letras[i]); //ponteiro que retorna a 1° ocorrência de determinada letra

                    if (ptr != NULL)
                    {
                        if ((letras[i] == L'M') && (obrigatorias[j].paga != 1)) //vai imprimir somente se a matéria for do turno da tarde e se ele ainda não foi paga
                        {
                            wprintf(L"|\033[4mNome: %-40ls| Id: %-12ls| Horário: %10ls\033[0m|\n", obrigatorias[j].nome, obrigatorias[j].id, obrigatorias[j].horario_disc);
                            obrigatorias[j].paga = 1;

                            //inferimos que o aluno passou nessas matérias para que possamos construir o restante do aconselhamento
                            wcscpy(aluno->minhaGrade[materiasPagas].id, obrigatorias[j].id); 
                            wcscpy(aluno->minhaGrade[materiasPagas].nome, obrigatorias[j].nome);
                            materiasPagas++;
                        }
                    }
                }
            }
        }
        else
        {

        }

        for (int j = 0; j < max; ++j) //um loop para saber a qtd de matérias que ainda não foram pagas
        {
            if (obrigatorias[j].paga != 1)
            {
                materiasNaoPagas++;
            }
        }

        wprintf(L"Lembre-se! Você está no %d° período, ou seja, você tem de terminar o curso em %d períodos\n", aluno->periodoAtual, aluno->tempo_curso - aluno->periodoAtual);
        wprintf(L"Lhe resta %d disciplinas a serem pagas!\n\n", materiasNaoPagas);

        aluno->periodoAtual++;
        menorPeriodo++;

        z--;

    }


    wprintf(L"%d\n", aluno->periodoAtual);
    wprintf(L"acabou\n");

    return;
}

void inicializarObrigatorias(Disciplina obrigatorias[], int max, FILE * arquivo) //função para inserir as matérias na struct
{
    int i = 0;
    
    //Periodo: 1, Nome: Programacao 1, Id: COMP359, Peso: 1, CH: 72, Requisito: 0, Horario: 6M3456
    //M = manha, T = Tarde, antes da letra sao os dias da semana e depois as aulas
    while ((i < max) && fwscanf(arquivo, L"Periodo: %d, Nome: %69l[^,], Id: %9l[^,], Peso: %d, CH: %d, Requisito: %109l[^,], Horario: %7l[^\n]\n", &obrigatorias[i].periodo, obrigatorias[i].nome, obrigatorias[i].id, &obrigatorias[i].peso, &obrigatorias[i].carga, obrigatorias[i].pre_requisitos, obrigatorias[i].horario_disc) != EOF)
    {
        wprintf(L"Periodo: %d, Nome: %ls, Id: %ls, Peso: %d, CH: %d, Requisito: %ls, Horario: %ls\n", obrigatorias[i].periodo, obrigatorias[i].nome, obrigatorias[i].id, obrigatorias[i].peso, obrigatorias[i].carga, obrigatorias[i].pre_requisitos, obrigatorias[i].horario_disc);
        
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
    
    //Id: COMP359, Nome: Programacao 1, Nota: 7.8
    while (fwscanf(arquivo, L"Id: %9l[^,], Nome: %59l[^,], Nota: %lf\n", aluno->minhaGrade[i].id, aluno->minhaGrade[i].nome, &aluno->minhaGrade[i].nota) != EOF)
    {
        //wprintf(L"Nome: %ls, Id: %d, CH: %d, Requisito: %ls, Horario: %ls\n", obrigatorias[i].periodo, obrigatorias[i]);
        //wprintf(L"Id: %ls, Nome: %ls, Nota: %lf\n", aluno->minhaGrade[i].id, aluno->minhaGrade[i].nome, aluno->minhaGrade[i].nota);
        
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
int validation_string(Aluno aluno) 
{
    for (int i = 0; aluno.nome[i] != L'\0'; ++i)
    {
        if (!(iswalpha(aluno.nome[i]) || iswspace(aluno.nome[i]))) //validacao de tipo string
        {
            return 0;
        }
    }

   return 1;
}

int value_string(wchar_t letra) //retorna o valor de cada letra do nome
{ 
   switch (letra) 
   {
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

int name_sum(wchar_t *nome) //soma os valores das letras
{
   int soma = 0;

   for (int i = 0; nome[i] != L'\0'; ++i)
   {
        soma += value_string(towlower(nome[i]));
   }
   
   return soma;
}

//função para separação do nome em partes para fazer a divisão
void name_process(Aluno aluno, int resto[]) 
{
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

int main() 
{
   setlocale(LC_ALL, "");

   fwide(stdout, 1); //força stdout a operar no modo wide-character, reduzindo problemas com wprintf

   //structs
   Aluno aluno = {.nome = L"Erivaldo Jose Silva Santos"};
   Disciplina obrigatorias[MAX_OBRIG] = {0}; //array de structs que irá conter as matérias obrigatórias, 24 obrigatórias fora as da ênfases
   //ints
   int resto[MAXR]; //guardará o resto das divisões das particões do nome
   int materiasPagas = 0; //guardará um indice de controle sobre as disciplinas pagas
   //ponteiros FILE
   FILE * disciplinasObrigatorias;
   FILE * historico;
   //atribuindo o endereço dos arquivos externos aos ponteiros FILE
   disciplinasObrigatorias = fopen("obrigatorias.txt", "r, ccs=UTF-8"); //abre no formato Unicode
   historico = fopen("entrada.txt", "r, ccs=UTF-8");

   if (disciplinasObrigatorias == NULL || historico == NULL) //checagem para caso tenha havido erro na abertura de um dos arquivos
   {
        wprintf(L"Erro ao abrir o arquivo externo!\n");
        return 1;
   }

   //funções para passar os dados dos arquivos externos para as structs
   inicializarObrigatorias(obrigatorias, MAX_OBRIG, disciplinasObrigatorias); //irá inserir todas as disciplinas obrigatórias do arquivo externo para a struct
   materiasPagas = inicializarMateriasPagas(&aluno, historico); //função para receber o histórico do usuário e em seguida no array obrigatorias irá indicar quais matérias já foram pagas

   if (materiasPagas == -1) //prevenção de erros para caso a função tenha lido uma qtd de linhas não esperadas
   {
        wprintf(L"Erro na leitura da entrada\n");
   }

   wprintf(L"==========================MATÉRIAS PAGAS===========================\n");

   //loop para informar no array obrigatorias quais materias ele já pagou
   for (int i = 0; i < materiasPagas; ++i) //vai comparando até achar a matéria correspondente
   {
        //o loop externo roda a struct aluno
        //e a interna roda a struct obrigatorias    

        for (int j = 0; j < MAX_OBRIG; ++j) //vai analisar todas as matérias obrigatórias
        {
            if (wcscmp(aluno.minhaGrade[i].id, obrigatorias[j].id) == 0) //caso haja um correspondente entre a que ele pagou que consta no histórico
            //e a da struct obrigatorias 
            {
                wprintf(L"%ls\n", aluno.minhaGrade[i].nome);
                
                obrigatorias[j].paga = 1; //o aluno já pagou essa matéria
                break;
            }
        }
   }

   wprintf(L"===================================================================\n");

   wprintf(L"Digite o nome modelo completo a seguir: %ls\n", aluno.nome);

   /*while (1) //loop para evitar erros na inserção do nome modelo
   {
       wprintf(L"Digite o nome modelo completo a seguir: ");
       fgetws(aluno.nome, sizeof(aluno.nome) / sizeof(wchar_t), stdin);
    
       wchar_t * ptr = wcschr(aluno.nome, L'\n'); //ponteiro wchar_t para a 1° aparição do '\n' que será retornado pela função wcschar
    
       if (ptr) //caso ptr for != de NULL quer dizer que ele encontrou a última posição do '\n'
       {
            *ptr = L'\0'; //substituindo o '\n' por '\0'
       }
    
       //validacao do nome 
       if (!validation_string(aluno)) 
       {
           wprintf(L"Existe caracteres não alfabéticos no seu nome! Vamos recomeçar!\n");
       }
       else
       {
            break;
       }
   }*/
   
   name_process(aluno, resto); //decomposicao do nome, soma e divisão para obtenção do seu resto que nos ajudará no conhecimento das condições do projeto

   suaSituacao(resto, &aluno); //será passado o endereço da variável aluno para que seu valor seja integralmente alterado

   aconselhamentoPedagogico(obrigatorias, MAX_OBRIG, &aluno, materiasPagas); //vai dá a distribuição das matérias ainda não pagas de todos os períodos
   
   
   //fechamento dos ponteiros
   fclose(disciplinasObrigatorias); 
   fclose(historico);

   return 0;
}