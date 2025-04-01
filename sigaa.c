//INTEGRANTES
//Erivaldo José
//Leandro Marcio
//Guilherme Alessander
//João Victor 
//Rodrigo Oliveira

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>

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

/*
//verifica se há conflitos de horarios
int choqueHorario(const wchar_t *horario1, const wchar_t *horario2) //recebe as strings wchar que contém os horários
{
    //pega os dias e turnos do primeiro horario recebido
    int dias1[7] = {0}; //dias de aula com os valores de cada posição do array variando de 0 a 1, não ou sim, respectivamente
    wchar_t turno1 = L' '; //turno das aulas podendo o valor wchar variar entre [M/T]
    int aulas1[6] = {0}; //aulas com os valores de cada posição do array variando de 0 a 1, não ou sim, respectivamente
    
    //pega os dias e turnos do segundo horario recebido
    int dias2[7] = {0}; //dias de aula
    wchar_t turno2 = L' '; //turno das aulas
    int aulas2[6] = {0}; //aulas
    
    //->processamento do primeiro horario recebido
    int i = 0;

    //exemplo de horário: 35M234
    
    //processamento dos dias
    //enquanto horario[i] não tiver chegado ao fim da string e não tenha encontrado o wchar do turno [M/T]
    while (horario1[i] != L'\0' && !iswalpha(horario1[i]))
    { 
        int dia = horario1[i] - L'0'; //conversão de wchar para int

        if (dia >= 2 && dia <= 7) //seg até sab
        { 
            dias1[dia - 2] = 1; //2=seg, 3=ter, 4=qua......
            //há aula nesse dia
        }

        i++;
    }

    turno1 = horario1[i]; //turno1 recebe o valor em wchar do turno [M/T]
    i++;

    //enquanto horario[i] não tiver chegado ao fim da string
    while (horario1[i] != L'\0') //processamento das aulas
    {
        int aula = horario1[i] - L'0'; //conversão de wchar para int

        if (aula >= 1 && aula <= 6) 
        {
            aulas1[aula - 1] = 1;
        }

        i++;
    }
    
    //->agora para o segundo horario recebido
    i = 0;

    while (horario2[i] != L'\0' && !iswalpha(horario2[i])) 
    {
        int dia = horario2[i] - L'0';

        if (dia >= 2 && dia <= 7) 
        {
            dias2[dia - 2] = 1;
        }

        i++;
    }

    turno2 = horario2[i];
    i++;

    while (horario2[i] != L'\0') 
    {
        int aula = horario2[i] - L'0';

        if (aula >= 1 && aula <= 6) 
        {
            aulas2[aula - 1] = 1;
        }

        i++;
    }
    
    //vê se é do msm turno
    if (turno1 != turno2) //condição crucial
    {
        return 0; //se for diferente, logo não há choque de horário
    }
    
    for (int j = 0; j < 7; j++) 
    {
        //verifica quais são os dias em comuns
        if (dias1[j] && dias2[j]) //equivalente de dias1[j] == dias2[j]
        //caso haja dias em comum rodará um loop para checar os horários
        {
            //aulas em dia comum
            for (int j = 0; j < 6; j++) 
            {
                if (aulas1[j] && aulas2[j]) 
                {
                    return 1; //tem choque
                }
            }
        }
    }
    
    return 0; //sem choque aeeeee
}


void selecionarDisciplinasSemChoque(Disciplina *disciplinas, int inicio, int fim, int maxDisciplinas, Aluno *aluno, int *materiasPagas) 
{
    Disciplina selecionadas[10]; 
    int num_select = 0;
    
    //ordena por peso, maior primeiro
    for (int i = inicio; i < fim - 1; i++) 
    {
        for (int j = i + 1; j < fim; j++) 
        {
            if (disciplinas[j].peso > disciplinas[i].peso) //troca de posição com structs
            {
                Disciplina temp = disciplinas[i];
                disciplinas[i] = disciplinas[j];
                disciplinas[j] = temp;
            }
        }
    }
    
    //pega a disciplina sem choque
    for (int i = inicio; i < fim && num_select < maxDisciplinas; i++) 
    {
        if (disciplinas[i].paga == 1) continue; //pula para a próxima iteração
        
        int choque = 0;
        
        //vê se tem choque com as que já estão adicionadas
        for (int j = 0; j < num_select; j++) 
        {
            if (choqueHorario(disciplinas[i].horario_disc, selecionadas[j].horario_disc)) 
            {
                choque = 1;
                break;
            }
        }
        
        if (!choque) 
        {
            selecionadas[num_select] = disciplinas[i];
            num_select++;
            
            //marca e add no historico
            disciplinas[i].paga = 1;
            wcscpy(aluno->minhaGrade[*materiasPagas].id, disciplinas[i].id);
            wcscpy(aluno->minhaGrade[*materiasPagas].nome, disciplinas[i].nome);
            (*materiasPagas)++;
        }
    }
    
    //mostra as selecionadas
    if (num_select > 0) {
        wprintf(L"\033[4mPeriodo Atual: %d. Suas disciplinas no proximo periodo (%d°) serao:\033[0m\n", aluno->periodoAtual, aluno->periodoAtual + 1);
        
        for (int i = 0; i < num_select; i++) {
            wprintf(L"| Nome: %-40ls | Id: %-12ls | Horario: %10ls |\n", selecionadas[i].nome, selecionadas[i].id, selecionadas[i].horario_disc);
        }
    } else {
        wprintf(L"Nao foi possivel selecionar disciplinas sem choque de horario para este periodo.\n");
    }
}
*/

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
            
            /*//vai repetir todo o processo, pois não foi armazenado as posições das disciplinas do turno da tarde
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
            }*/
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
            
            /*//vai repetir todo o processo, pois não foi armazenado as posições das disciplinas do turno da manhã
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
            }*/
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
                
                /*for (int j = menorInd; j < IndperiodoSeguinte; ++j)
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
                }*/
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
                
                /*for (int j = menorInd; j < IndperiodoSeguinte; ++j)
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
                }*/
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