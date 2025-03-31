# Aconselhamento Pedagógico - Ciência da Computação UFAL

Sistema de recomendação de disciplinas para alunos do curso de Ciência da Computação da UFAL, baseado no PPC 2019.

## 📋 Descrição

Este projeto gera um plano de disciplinas para os próximos períodos letivos, considerando:

✅ Pré-requisitos das matérias  
⏰ Conflitos de horário  
📚 Limite máximo de disciplinas por semestre  
🎓 Tempo desejado para conclusão do curso  
🔍 Ênfase escolhida  
📅 Critérios de seleção de disciplinas  

## 🚀 Como usar

1. Clone o repositório
2. Compile com `gcc main.c -o aconselhamento`
3. Execute com `./aconselhamento`

## 📂 Estrutura de arquivos

```
.
├── main.c                 # Código principal
├── obrigatorias.txt       # Lista de disciplinas obrigatórias
├── entrada.txt            # Histórico do aluno
└── README.md              # Este arquivo
```

## 🔧 Requisitos

- Compilador C (GCC recomendado)
- Sistema com suporte a UTF-8
- Arquivos de entrada no formato especificado

## 📊 Funcionamento

O sistema calcula automaticamente os critérios baseados no nome do aluno, usando:

1. Conversão de letras para valores numéricos
2. Soma dos valores de cada parte do nome
3. Resto da divisão por 3 para cada critério

## 📝 Exemplo de saída

```
============================INFORMAÇÕES============================
1° periodo -> Matérias Manhã: 2, Matérias Tarde: 1
2° periodo -> Matérias Manhã: 3, Matérias Tarde: 2
...
====================================================================

Período Atual: 3. Suas disciplinas no próximo período (4°) serão:
| Nome: Algoritmos e Estruturas de Dados | Id: COMP123 | Horário: 24T12 |
| Nome: Programação Orientada a Objetos  | Id: COMP456 | Horário: 35M34 |
```
