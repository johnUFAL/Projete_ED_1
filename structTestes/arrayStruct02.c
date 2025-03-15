#include <stdio.h>

//Passando o array inteiro de structs para a função

// Definição de uma struct
struct Pessoa {
    char nome[50];
    int idade;
};

// Função que recebe o array de structs e o índice da pessoa a ser atualizada
void atualizarPessoa(struct Pessoa pessoas[], int index) {
    // Solicitando ao usuário um novo nome e idade
    printf("Digite o novo nome: ");
    scanf("%49s", pessoas[index].nome);  // Lê o nome, limitando a 49 caracteres para garantir o '\0' no final
    
    printf("Digite a nova idade: ");
    scanf("%d", &pessoas[index].idade);  // Lê a nova idade
}

int main() {
    // Criando um array de structs
    struct Pessoa pessoas[3] = {{"João", 25}, {"Maria", 30}, {"Carlos", 28}};

    // Exibindo os valores originais
    printf("Antes da atualização:\n");
    for (int i = 0; i < 3; i++) {
        printf("Pessoa %d: Nome: %s, Idade: %d\n", i + 1, pessoas[i].nome, pessoas[i].idade);
    }

    // Passando o array de structs e o índice da pessoa a ser atualizada
    int indice;
    printf("\nDigite o índice da pessoa para atualizar (0 a 2): ");
    scanf("%d", &indice);

    if (indice >= 0 && indice < 3) {
        atualizarPessoa(pessoas, indice);  // Passa o array e o índice da pessoa a ser atualizada
    } else {
        printf("Índice inválido!\n");
    }

    // Exibindo os valores após a atualização
    printf("\nDepois da atualização:\n");
    for (int i = 0; i < 3; i++) {
        printf("Pessoa %d: Nome: %s, Idade: %d\n", i + 1, pessoas[i].nome, pessoas[i].idade);
    }

    return 0;
}
