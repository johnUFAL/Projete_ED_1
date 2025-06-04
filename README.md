# Aconselhamento Pedagógico para Alunos de Ciência da Computação - UFAL


LINK PARA O PROJETO 2, CONTINUAÇÃO: https://github.com/johnUFAL/Projeto_ED_2.git

Este projeto foi desenvolvido como parte da disciplina de Estrutura de Dados e tem como objetivo gerar um aconselhamento pedagógico personalizado para alunos do curso de Ciência da Computação do Instituto de Computação da UFAL, seguindo as diretrizes do PPC2019.

## Integrantes do Grupo
- Erivaldo José
- Leandro Marcio
- Guilherme Alessander
- João Victor

## Funcionalidades
O sistema oferece as seguintes funcionalidades:

1. **Análise Personalizada**:
   - Calcula o limite máximo de disciplinas por semestre com base no nome do aluno
   - Determina o tempo ideal para conclusão do curso
   - Define critérios para escolha de ênfase
   - Estabelece orientações para seleção de disciplinas

2. **Verificação de Requisitos**:
   - Impede matrícula em disciplinas sem pré-requisitos
   - Detecta choques de horário entre disciplinas
   - Garante matrícula em pelo menos 1 disciplina

3. **Aconselhamento Inteligente**:
   - Sugere disciplinas obrigatórias por período
   - Oferece recomendações de eletivas compatíveis
   - Considera o histórico acadêmico do aluno

## Como Executar
1. Certifique-se de ter os arquivos de entrada no mesmo diretório do executável:
   - `obrigatorias.txt` - Lista de disciplinas obrigatórias
   - `eletivas.txt` - Lista de disciplinas eletivas
   - `entrada.txt` - Histórico do aluno

2. Compile e execute o programa:
   ```bash
   gcc main.c -o aconselhamento
   ./aconselhamento
   ```

## Estrutura do Código
O projeto está organizado nas seguintes estruturas principais:

- `Disciplina`: Armazena informações sobre disciplinas obrigatórias
- `Eletiva`: Armazena informações sobre disciplinas eletivas
- `MateriasPagas`: Registra as disciplinas já cursadas pelo aluno
- `Aluno`: Contém todas as informações do aluno e suas preferências

As principais funções incluem:
- `aconselhamentoPedagogico()` - Gera o plano de estudos
- `choqueHorario()` - Verifica conflitos de horário
- `podeAdicionarEletiva()` - Valida se uma eletiva pode ser cursada
- `inicializarObrigatorias()` - Carrega as disciplinas obrigatórias
- `inicializarEletivas()` - Carrega as disciplinas eletivas

## Critérios de Seleção
O sistema utiliza um algoritmo baseado no nome do aluno (em ordem alfabética) para determinar:
1. Limite máximo de disciplinas por semestre
2. Tempo ideal para conclusão do curso
3. Critério para escolha de ênfase
4. Orientação para seleção de disciplinas

## Licença
Este projeto é destinado exclusivamente para fins acadêmicos.
