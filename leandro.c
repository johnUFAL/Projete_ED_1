#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define MAX_DISCIPLINAS 10 
#define MAX_DISCIPLINAS_POR_PERIODO 6


typedef struct {
    int id;
    float media_final; 
    int periodo;       
    wchar_t nome[60];   
} Disciplina;


typedef struct {
    wchar_t nome[60];
    int periodo;            
    Disciplina disciplinas[MAX_DISCIPLINAS]; 
} Aluno;


float calcular_media_periodo(Aluno *aluno, int periodo) {
    float soma = 0.0;
    int contador = 0;
    
   
    for (int i = 0; i < MAX_DISCIPLINAS; i++) {
        if (aluno->disciplinas[i].periodo == periodo) {
            soma += aluno->disciplinas[i].media_final;
            contador++;
        }
    }
    
   
    if (contador > 0) {
        return soma / contador;
    }
    
    return 0.0;
}


float calcular_IRA(Aluno *aluno) {
    float soma = 0.0;
    int contador = 0;
    
   
    for (int i = 0; i < MAX_DISCIPLINAS; i++) {
        if (aluno->disciplinas[i].media_final > 0) {
            soma += aluno->disciplinas[i].media_final;  
            contador++;
        }
    }
    
  
    if (contador > 0) {
        return soma / contador;
    }
    
    return 0.0;
}


void adicionar_disciplina(Aluno *aluno, int periodo) {
    int disciplinas_no_periodo = 0;
    
   
    for (int i = 0; i < MAX_DISCIPLINAS; i++) {
        if (aluno->disciplinas[i].periodo == periodo) {
            disciplinas_no_periodo++;
        }
    }
    
   
    if (disciplinas_no_periodo >= MAX_DISCIPLINAS_POR_PERIODO) {
        printf("Limite de %d disciplinas por período alcançado. Não é possível adicionar mais.\n", MAX_DISCIPLINAS_POR_PERIODO);
        return;
    }
    
 
    for (int i = 0; i < MAX_DISCIPLINAS; i++) {
        if (aluno->disciplinas[i].periodo == 0) {  
            aluno->disciplinas[i].id = i + 1;  
            aluno->disciplinas[i].periodo = periodo;
            
            
            printf("Digite o nome da disciplina: ");
            getchar();  // Limpar o buffer do teclado
            wscanf(L"%ls", aluno->disciplinas[i].nome);
            
         
            printf("Digite a média final da disciplina: ");
            scanf("%f", &aluno->disciplinas[i].media_final);
            
            printf("Disciplina '%ls' adicionada ao período %d.\n", aluno->disciplinas[i].nome, periodo);
            break;
        }
    }
}

int main() {
    Aluno aluno;
    
    
    for (int i = 0; i < MAX_DISCIPLINAS; i++) {
        aluno.disciplinas[i].periodo = 0;
    }
    
   
    printf("Digite o nome do aluno: ");
    wscanf(L"%ls", aluno.nome);
    
   
    printf("Digite o número de disciplinas que deseja cadastrar: ");
    int num_disciplinas;
    scanf("%d", &num_disciplinas);
    
    
    for (int i = 0; i < num_disciplinas; i++) {
        printf("\nDigite os dados da disciplina %d:\n", i + 1);
        int periodo;
        
       
        printf("Digite o período da disciplina: ");
        scanf("%d", &periodo);
        
       
        adicionar_disciplina(&aluno, periodo);
    }
    
    
    printf("\nDigite o período para cálculo da média: ");
    int periodo;
    scanf("%d", &periodo);
    
    
    float media_periodo = calcular_media_periodo(&aluno, periodo);
    printf("\nMédia do Período %d: %.2f\n", periodo, media_periodo);

    
    float ira = calcular_IRA(&aluno);
    printf("\nÍndice de Rendimento Acadêmico (IRA): %.2f\n", ira);
    
    return 0;
}
