//INTEGRANTES
//Erivaldo José
//Leandro Marcio
//Guilherme Alessander
//João Victor 
//nome referencia ab1: Erivaldo

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

#define MAX_OBRIG 24
#define MAX_ELETIVAS 30
#define MAXR 4

typedef struct {
    int paga; // 1 - sim, 0 - não
    int peso; //preferência
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
    wchar_t pre_requisitos[25];
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

//função para começarmos inicializando as eletivas. 
void inicializarEletivas(Eletiva eletivas[], int *quant, FILE *arquivo) {
    int i = 0;
    while (fwscanf(arquivo, L"Nome: %59l[^,], Id: %9l[^,], CH: %d, Requisito: %99l[^,], Horario: %7l[^\n]\n",
        eletivas[i].nome, eletivas[i].id, &eletivas[i].carga,
        eletivas[i].pre_requisitos, eletivas[i].horario_ele) != EOF) {
        ++i;
    }
    *quant = i;
}

//aqui verificar se a disciplina obrigatoria e a eletiva estão tendo choque de horario 
int temChoqueHorarioComObrigatoria(Disciplina d, Eletiva e) {
    if (wcscmp(e.horario_ele, L"NULL") == 0 || wcscmp(d.horario_disc, L"NULL") == 0)
        return 0;

    int diasD[7] = {0}, aulasD[6] = {0};
    int diasE[7] = {0}, aulasE[6] = {0};
    wchar_t turnoD = L' ', turnoE = L' ';
    int i = 0;

    // Processa dias e turno da Disciplina d
    while (d.horario_disc[i] && !iswalpha(d.horario_disc[i])) {
        int dia_idx = d.horario_disc[i] - L'2';
        if (dia_idx >= 0 && dia_idx < 7)
            diasD[dia_idx] = 1;
        else
            wprintf(L"WARNING: Dia inválido na disciplina: %lc (índice %d)\n", d.horario_disc[i], dia_idx);
        i++;
    }
    turnoD = d.horario_disc[i++];

    while (d.horario_disc[i]) {
        int aula_idx = d.horario_disc[i] - L'1';
        if (aula_idx >= 0 && aula_idx < 6)
            aulasD[aula_idx] = 1;
        else
            wprintf(L"WARNING: Aula inválida na disciplina: %lc (índice %d)\n", d.horario_disc[i], aula_idx);
        i++;
    }

    i = 0;

    // Processa dias e turno da Eletiva e
    while (e.horario_ele[i] && !iswalpha(e.horario_ele[i])) {
        int dia_idx = e.horario_ele[i] - L'2';
        if (dia_idx >= 0 && dia_idx < 7)
            diasE[dia_idx] = 1;
        else
            wprintf(L"WARNING: Dia inválido na eletiva: %lc (índice %d)\n", e.horario_ele[i], dia_idx);
        i++;
    }
    turnoE = e.horario_ele[i++];

    while (e.horario_ele[i]) {
        int aula_idx = e.horario_ele[i] - L'1';
        if (aula_idx >= 0 && aula_idx < 6)
            aulasE[aula_idx] = 1;
        else
            wprintf(L"WARNING: Aula inválida na eletiva: %lc (índice %d)\n", e.horario_ele[i], aula_idx);
        i++;
    }

    // Verifica se há choque de horário
    if (turnoD == turnoE) {
        for (int d = 0; d < 7; d++) {
            if (diasD[d] && diasE[d]) {
                for (int a = 0; a < 6; a++) {
                    if (aulasD[a] && aulasE[a]) {
                        return 1; // Há choque de horário
                    }
                }
            }
        }
    }

    return 0; // Não há choque
}
//verificar se o aluno pode adicionar a eletiva a sua grade
//note que vai levar em conta também o choque de horario que nao pode 
int podeAdicionarEletiva(Eletiva e, Aluno *aluno, Disciplina obrigatorias[], int qtdOb) {
    for (int i = 0; i < 29; i++)
        if (wcscmp(aluno->minhaGrade[i].id, e.id) == 0) return 0;
    if (wcscmp(e.pre_requisitos, L"Nenhum") != 0) {
        int achou = 0;
        for (int i = 0; i < 29; i++)
            if (wcscmp(aluno->minhaGrade[i].id, e.pre_requisitos) == 0) {
                achou = 1;
                break;
            }
        if (!achou) return 0;
    }
    for (int i = 0; i < qtdOb; i++)
        if (obrigatorias[i].paga && temChoqueHorarioComObrigatoria(obrigatorias[i], e))
            return 0;
    return 1;
}

//verifica se há conflitos de horarios
void choqueHorario(Disciplina obrigatorias[], int indPos[], int maxPos, Aluno * aluno)
//struct Disciplina obrigatorias[], int indPosT[], int maxPosT, Aluno * aluno
{
    for (int k = 0; k < maxPos - 1; ++k) //vai pegar o horário da 1° disciplina e comparar com os demais
    {
        //pega os dias e turnos do primeiro horario recebido
        int dias1[7] = {0}; //dias de aula com os valores de cada posição do array variando de 0 a 1, não ou sim, respectivamente
        wchar_t turno1 = L' '; //turno das aulas podendo o valor wchar variar entre [M/T]
        int aulas1[6] = {0}; //aulas com os valores de cada posição do array variando de 0 a 1, não ou sim, respectivamente
        
        //pega os dias e turnos do segundo horario recebido
        int dias2[7] = {0}; //dias de aula
        wchar_t turno2 = L' '; //turno das aulas
        int aulas2[6] = {0}; //aulas
    
        int choque = 0; //dirá se houve ou não choque de horário

        int auxP = indPos[k]; //auxiliar principal
        //indPos tem 10 elementos que são o máximo de matérias por semestre
        //cada elemento desse array pode armazenar um valor inteiro entre 0 a 23, sem repetir
        int auxS = 0; //auxiliar secundária

        for (int j = k + 1; j < maxPos; ++j) //horários seguintes
        {
            int auxS = indPos[j];
            
            //->processamento do primeiro horario recebido
            int i = 0;

            //exemplo de horário: 35M234
            
            //processamento dos dias
            //enquanto horario[i] não tiver chegado ao fim da string e não tenha encontrado o wchar do turno [M/T]
            while (obrigatorias[auxP].horario_disc[i] != L'\0' && !iswalpha(obrigatorias[auxP].horario_disc[i]))
            { 
                int dia = obrigatorias[auxP].horario_disc[i] - L'0'; //conversão de wchar para int

                if (dia >= 2 && dia <= 7) //seg até sab
                { 
                    dias1[dia - 2] = 1; //2=seg, 3=ter, 4=qua......
                    //há aula nesse dia
                }

                i++;
            }

            turno1 = obrigatorias[auxP].horario_disc[i]; //turno1 recebe o valor em wchar do turno [M/T]
            i++;

            //enquanto horario[i] não tiver chegado ao fim da string
            while (obrigatorias[auxP].horario_disc[i] != L'\0') //processamento das aulas
            {
                int aula = obrigatorias[auxP].horario_disc[i] - L'0'; //conversão de wchar para int

                if (aula >= 1 && aula <= 6) 
                {
                    aulas1[aula - 1] = 1;
                }

                i++;
            }
            
            //->agora para o segundo horario recebido
            i = 0;
            while (obrigatorias[auxS].horario_disc[i] != L'\0' && !iswalpha(obrigatorias[auxS].horario_disc[i])) 
            {
                int dia = obrigatorias[auxS].horario_disc[i] - L'0';

                if (dia >= 2 && dia <= 7) 
                {
                    dias2[dia - 2] = 1;
                }

                i++;
            }

            turno2 = obrigatorias[auxS].horario_disc[i];
            i++;

            while (obrigatorias[auxS].horario_disc[i] != L'\0') 
            {
                int aula = obrigatorias[auxS].horario_disc[i] - L'0';

                if (aula >= 1 && aula <= 6) 
                {
                    aulas2[aula - 1] = 1;
                }

                i++;
            }

            for (int j = 0; j < 7; j++) //loop para os dias
            {
                //verifica quais são os dias em comuns
                if (dias1[j] && dias2[j]) //equivalente de dias1[j] == dias2[j]
                //caso haja dias em comum rodará um loop para checar os horários
                {
                    //aulas em dia comum
                    for (int j = 0; j < 6; j++)  //loop para as aulas
                    {
                        if (aulas1[j] && aulas2[j]) 
                        {
                            choque = 1; //tem choque

                            wprintf(L"A disciplina %ls (horário: %ls) está tendo choque de horário com a disciplina %ls (horário: %ls)\n", obrigatorias[auxP].nome, obrigatorias[auxP].horario_disc, obrigatorias[auxS].nome, obrigatorias[auxS].horario_disc);
                        }
                    }
                }
            }    
        }
    }
}

//vai entregar a distribuição das matérias ainda não pagas de todos os períodos, ou seja, aconselhar o aluno
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
    //wprintf(L"%d\n", aluno->periodoAtual);

    while (materiasNaoPagas > 0 && (aluno->periodoAtual < aluno->tempo_curso)) 
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

        //o mudar recebe 1 por causa de uma situação excepcional
        int mudar = 1; //0 = não mudar, 1 = mudar
        //wprintf(L"Antes\nmenorPeriodo: %d, menorInd: %d, IndperiodoSeguinte: %d\n", menorPeriodo, menorInd, IndperiodoSeguinte);

        for (int j = menorInd; j < IndperiodoSeguinte; ++j) //vai do menor indice até o indice anterior ao indice que começa o próximo período
        {
            if (obrigatorias[j].paga != 1) //se houver alguma disciplina ainda não paga, o código continua normalmente
            {
                mudar = 0;
                break;
            }
            else //caso contrário mudamos o menor índice
            {
                mudar = 1;
            }
        }

        if (mudar == 1) //positivo para a mudança
        {
            menorInd = IndperiodoSeguinte; //a variável menorInd vai receber o indice de onde começa o próximo período
            menorPeriodo = obrigatorias[menorInd].periodo; //a partir do novo menor indice o valor do menor periodo também vai mudar

            for (int m = menorInd; m < max; ++m)
            {
                if (obrigatorias[m].periodo >= menorPeriodo) // >= porque só há disciplinas até o 7° período
                {
                    IndperiodoSeguinte = m + 1;
                    break; //agora temos o índice de onde irá comecar o seguinte período após o menor período
                }
            }
            //wprintf(L"Depois\nmenorPeriodo: %d, menorInd: %d, IndperiodoSeguinte: %d\n", menorPeriodo, menorInd, IndperiodoSeguinte);
        }

        int requisitos = 0; //0 = não pagos, 1 = pagos
        int manha = 0; //qtd de disciplinas no turno da manhã que podem ser escolhidas
        int tarde = 0; //qtd de disciplinas no turno da tarde que podem ser escolhidas
        int pesoManha = 0; //maior peso das matérias da manhã
        int pesoTarde = 0; //maior peso das matérias da tarde
        
        int indPosM[10] = {0}; //vai armazenar todas os índices que determinarão as posições das disciplinas de cada turno 
        int indPosT[10] = {0}; //10 elementos pois é o max de disciplinas que podem ser pagas pelo usuário
        int maxPosM = 0; //vai guardar a qtd de elementos
        int maxPosT = 0;

        wchar_t letras[] = L"MT"; //letras de interesse a serem analisadas
        wchar_t * ptr; //ponteiro para a 1° ocorrência de determinada letra
        //wprintf(L"Peso tarde: %d\nPeso manha: %d\nTarde: %d\nManha: %d\n", pesoTarde, pesoManha, tarde, manha);

        for (int j = menorInd; j < IndperiodoSeguinte; ++j) //verifica todas as disciplinas não pagas no menor período
        {
            //faz a checagem dos pré requisitos
            if ((wcscmp(obrigatorias[j].pre_requisitos, L"COMP555") == 0) && obrigatorias[j].paga != 1) //caso excepcional
            //Periodo: 6, Nome: Projeto e Desenvolvimento de Sistemas, Id: COMP382, Peso: 0, CH: 288, Requisito: COMP555, Horario: 26T1234
            {
                requisitos = 1; //se pressupõem que ele já pagou todas as matérias do 1° ao 5° semestre

                int cont = 0;

                while (obrigatorias[cont].periodo < 6) //loop que percorre todas as matérias até o período de uma delas ser 6, ou maior
                //as disciplinas obrigatórias estão em ordem crescente por período e id da disciplina
                {
                    if (obrigatorias[cont].paga != 1)
                    {
                        requisitos = 0; //alguma matéria não foi paga dos períodos anteriores
                        break;
                    }

                    cont++;
                }
            }
            else
            {
                //->checagem dos requisitos das disciplinas que serão pagas
                
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
            }

            //letras[i] = "MT"
            for (int i = 0; letras[i] != L'\0'; ++i) //loop para quantificar a qtd de disciplinas em cada turno
            {
                ptr = wcschr(obrigatorias[j].horario_disc, letras[i]); //ponteiro que retorna a 1° ocorrência de determinada letra

                if (ptr != NULL)
                {
                    if ((letras[i] == L'M') && (obrigatorias[j].paga != 1) && (requisitos == 1))
                    //o turno da disciplina deve ser de manhã
                    //ela ainda não deve ter sido paga
                    //e o aluno deve cumprir com todos os seus requisitos
                    {
                        indPosM[maxPosM] = j; //armazena a posição do elemento do array obrigatorias
                        maxPosM++;
                        
                        manha++;

                        if (obrigatorias[j].peso >= pesoManha) //vai armazenar o maior peso entre as disciplinas da manhã
                        {
                            pesoManha = obrigatorias[j].peso;
                        }
                    }
                    else if ((letras[i] == L'T') && (obrigatorias[j].paga != 1) && (requisitos == 1))
                    //o turno da disciplina deve ser de tarde
                    //ela ainda não deve ter sido paga
                    //e o aluno deve cumprir com todos os seus requisitos
                    {
                        indPosT[maxPosT] = j; //armazena a posição do elemento do array obrigatorias
                        maxPosT++;
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


        //wprintf(L"Peso tarde: %d\nPeso manha: %d\nTarde: %d\nManha: %d\n", pesoTarde, pesoManha, tarde, manha);


        if (pesoTarde > pesoManha)
        {
            wprintf(L"\033[4mPeríodo Atual: %d. Suas disciplinas no próximo período (%d°) serão a tarde. São elas: \033[0m\n", aluno->periodoAtual, aluno->periodoAtual + 1);
            
            //choqueHorario(obrigatorias, indPosT, maxPosT, aluno);
            //wprintf(L"\n");
            
            for (int j = 0; j < maxPosT; ++j)
            {
                int aux = indPosT[j]; //recebe a posição da disciplina 
                
                wprintf(L"|\033[4mNome: %-40ls| Id: %-12ls| Horário: %10ls\033[0m|\n", obrigatorias[aux].nome, obrigatorias[aux].id, obrigatorias[aux].horario_disc);
                obrigatorias[aux].paga = 1;

                //inferimos que o aluno passou nessas matérias para que possamos construir o restante do aconselhamento
                wcscpy(aluno->minhaGrade[materiasPagas].id, obrigatorias[aux].id); 
                wcscpy(aluno->minhaGrade[materiasPagas].nome, obrigatorias[aux].nome);
                materiasPagas++;
            }
        }
        else if (pesoTarde < pesoManha)
        {
            wprintf(L"\033[4mPeríodo Atual: %d. Suas disciplinas no próximo período (%d°) serão de manhã. São elas: \033[0m\n", aluno->periodoAtual, aluno->periodoAtual + 1);
            
            for (int j = 0; j < maxPosM; ++j)
            {
                int aux = indPosM[j]; //recebe a posição da disciplina 
                
                wprintf(L"|\033[4mNome: %-40ls| Id: %-12ls| Horário: %10ls\033[0m|\n", obrigatorias[aux].nome, obrigatorias[aux].id, obrigatorias[aux].horario_disc);
                obrigatorias[aux].paga = 1;

                //inferimos que o aluno passou nessas matérias para que possamos construir o restante do aconselhamento
                wcscpy(aluno->minhaGrade[materiasPagas].id, obrigatorias[aux].id); 
                wcscpy(aluno->minhaGrade[materiasPagas].nome, obrigatorias[aux].nome);
                materiasPagas++;
            }
        }
        else //agora o critério de escolhas se dará pela qtd de disciplinas
        {
            if (tarde > manha)
            {
                wprintf(L"\033[4mPeríodo Atual: %d. Suas disciplinas no próximo período (%d°) serão a tarde. São elas: \033[0m\n", aluno->periodoAtual, aluno->periodoAtual + 1);
        
                for (int j = 0; j < maxPosT; ++j)
                {
                    int aux = indPosT[j]; //recebe a posição da disciplina 
                    
                    wprintf(L"|\033[4mNome: %-40ls| Id: %-12ls| Horário: %10ls\033[0m|\n", obrigatorias[aux].nome, obrigatorias[aux].id, obrigatorias[aux].horario_disc);
                    obrigatorias[aux].paga = 1;

                    //inferimos que o aluno passou nessas matérias para que possamos construir o restante do aconselhamento
                    wcscpy(aluno->minhaGrade[materiasPagas].id, obrigatorias[aux].id); 
                    wcscpy(aluno->minhaGrade[materiasPagas].nome, obrigatorias[aux].nome);
                    materiasPagas++;
                }
            }
            else //manha <= tarde
            {
                wprintf(L"\033[4mPeríodo Atual: %d. Suas disciplinas no próximo período (%d°) serão de manhã. São elas: \033[0m\n", aluno->periodoAtual, aluno->periodoAtual + 1);
            
                    for (int j = 0; j < maxPosM; ++j)
                    {
                        int aux = indPosM[j]; //recebe a posição da disciplina 
                        
                        wprintf(L"|\033[4mNome: %-40ls| Id: %-12ls| Horário: %10ls\033[0m|\n", obrigatorias[aux].nome, obrigatorias[aux].id, obrigatorias[aux].horario_disc);
                        obrigatorias[aux].paga = 1;

                        //inferimos que o aluno passou nessas matérias para que possamos construir o restante do aconselhamento
                        wcscpy(aluno->minhaGrade[materiasPagas].id, obrigatorias[aux].id); 
                        wcscpy(aluno->minhaGrade[materiasPagas].nome, obrigatorias[aux].nome);
                        materiasPagas++;
                    }
            }
        }

        for (int j = 0; j < max; ++j) //um loop para saber a qtd de matérias que ainda não foram pagas
        {
            if (obrigatorias[j].paga != 1)
            {
                //wprintf(L"%ls[%d]\n", obrigatorias[j].nome, j);
                materiasNaoPagas++;
            }
        }

        wprintf(L"Lembre-se! Você está no %d° período, ou seja, você tem de terminar o curso em %d períodos\n", aluno->periodoAtual, aluno->tempo_curso - aluno->periodoAtual);
        wprintf(L"Lhe resta %d disciplinas a serem pagas!\n\n", materiasNaoPagas);

        aluno->periodoAtual++;
        menorPeriodo++;
    }
    /*wprintf(L"%d\n", aluno->periodoAtual);
    wprintf(L"acabou\n");*/

    if (materiasNaoPagas <= 0)
    {
        wprintf(L"Parabéns você conseguiu!\n");
        wprintf(L"Você está no %d° período, e terminou o curso faltando %d períodos\n", aluno->periodoAtual, aluno->tempo_curso - aluno->periodoAtual);
    }

    return;
}

void inicializarObrigatorias(Disciplina obrigatorias[], int max, FILE * arquivo) //função para inserir as matérias na struct
{
    int i = 0;
    
    //Periodo: 1, Nome: Programacao 1, Id: COMP359, Peso: 1, CH: 72, Requisito: 0, Horario: 6M3456
    //M = manha, T = Tarde, antes da letra sao os dias da semana e depois as aulas
    while ((i < max) && fwscanf(arquivo, L"Periodo: %d, Nome: %69l[^,], Id: %9l[^,], Peso: %d, CH: %d, Requisito: %24l[^,], Horario: %7l[^\n]\n", &obrigatorias[i].periodo, obrigatorias[i].nome, obrigatorias[i].id, &obrigatorias[i].peso, &obrigatorias[i].carga, obrigatorias[i].pre_requisitos, obrigatorias[i].horario_disc) != EOF)
    {
        //wprintf(L"Periodo: %d, Nome: %ls, Id: %ls, Peso: %d, CH: %d, Requisito: %ls, Horario: %ls\n", obrigatorias[i].periodo, obrigatorias[i].nome, obrigatorias[i].id, obrigatorias[i].peso, obrigatorias[i].carga, obrigatorias[i].pre_requisitos, obrigatorias[i].horario_disc);
        
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
        
        if (aluno->minhaGrade[i].nota >= 7) //caso a nota do aluno seja menor que sete isso indicará que ele trancou a matéria, ou reprovou nela
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

int main() 
{
   setlocale(LC_ALL, "");
    fwide(stdout, 1);

    Aluno aluno = {.nome = L"Erivaldo Jose Silva Santos"};
    Disciplina obrigatorias[MAX_OBRIG] = {0};
    int resto[MAXR], materiasPagas = 0;
    FILE *disciplinasObrigatorias = fopen("obrigatorias.txt", "r");
    FILE *historico = fopen("entrada.txt", "r");
    if (!disciplinasObrigatorias || !historico) {
        wprintf(L"Erro ao abrir arquivo!"); return 1;
    }

    inicializarObrigatorias(obrigatorias, MAX_OBRIG, disciplinasObrigatorias);
    materiasPagas = inicializarMateriasPagas(&aluno, historico);

    for (int i = 0; i < materiasPagas; ++i)
        for (int j = 0; j < MAX_OBRIG; ++j)
            if (wcscmp(aluno.minhaGrade[i].id, obrigatorias[j].id) == 0)
                obrigatorias[j].paga = 1;

    name_process(aluno, resto);
    suaSituacao(resto, &aluno);
    aconselhamentoPedagogico(obrigatorias, MAX_OBRIG, &aluno, materiasPagas);

    FILE *arquivoEletivas = fopen("eletivas.txt", "r");
    if (!arquivoEletivas) {
        wprintf(L"Erro ao abrir eletivas.txt\n"); return 1;
    }

    Eletiva eletivas[MAX_ELETIVAS] = {0};
    int totalEletivas = 0;
    inicializarEletivas(eletivas, &totalEletivas, arquivoEletivas);

    wprintf(L"\n=======================SUGESTÃO DE ELETIVAS========================\n");

    int adicionadas = 0;
    for (int i = 0; i < totalEletivas; i++) {
        if (podeAdicionarEletiva(eletivas[i], &aluno, obrigatorias, MAX_OBRIG)) {
            if (wcschr(eletivas[i].horario_ele, aluno.turno_disciplina) != NULL) {
                wprintf(L"|\033[4mNome: %-40ls| Id: %-12ls| Horário: %10ls\033[0m|\n",
                    eletivas[i].nome, eletivas[i].id, eletivas[i].horario_ele);

                wcscpy(aluno.minhaGrade[materiasPagas].id, eletivas[i].id);
                wcscpy(aluno.minhaGrade[materiasPagas].nome, eletivas[i].nome);
                materiasPagas++;
                adicionadas++;

                if (adicionadas >= 2) break;
            }
        }
    }

    if (adicionadas == 0)
        wprintf(L"Nenhuma eletiva disponível compatível.\n");

    fclose(disciplinasObrigatorias);
    fclose(historico);
    fclose(arquivoEletivas);
    
   return 0;
}

//link do segundo projeto: https://github.com/johnUFAL/Projeto_ED_2.git
