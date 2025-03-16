#include <stdio.h>

//Passando um ponteiro para uma posição específica do array de structs

// Definição de uma struct
struct Pessoa {
    char nome[50];
    int idade;
};

// Função que recebe um ponteiro para a struct e solicita a entrada do usuário
void atualizarPessoa(struct Pessoa *p) {
    // Solicitando ao usuário um novo nome e idade
    printf("Digite o novo nome: ");
    scanf("%49s", p->nome);  // Lê o nome, limitando a 49 caracteres para garantir o '\0' no final
    
    printf("Digite a nova idade: ");
    scanf("%d", &p->idade);  // Lê a nova idade
}

int main() {
    // Criando um array de structs
    struct Pessoa pessoas[3] = {{"João", 25}, {"Maria", 30}, {"Carlos", 28}};

    // Exibindo os valores originais
    printf("Antes da atualização:\n");
    for (int i = 0; i < 3; i++) {
        printf("Pessoa %d: Nome: %s, Idade: %d\n", i + 1, pessoas[i].nome, pessoas[i].idade);
    }

    // Passando o ponteiro para o elemento do array que queremos atualizar (por exemplo, o segundo)
    printf("\nAtualizando dados da segunda pessoa (índice 1):\n");
    atualizarPessoa(&pessoas[1]);  // Passa o ponteiro para o segundo elemento do array

    // Exibindo os valores após a atualização
    printf("\nDepois da atualização:\n");
    for (int i = 0; i < 3; i++) {
        printf("Pessoa %d: Nome: %s, Idade: %d\n", i + 1, pessoas[i].nome, pessoas[i].idade);
    }

    return 0;
}
