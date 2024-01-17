#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Produto {
    char nome[100];
    char codigoBarras[20];
    int quantidade;
    float preco;
    char dataEntrada[20];
    char fornecedor[100];
};

void adicionarProduto(struct Produto **produtos, int *totalProdutos) {
    *produtos = realloc(*produtos, (*totalProdutos + 1) * sizeof(struct Produto));
    if (*produtos == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    printf("Digite o nome do produto: ");
    scanf("%s", (*produtos)[*totalProdutos].nome);
    printf("Digite o código de barras: ");
    scanf("%s", (*produtos)[*totalProdutos].codigoBarras);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &(*produtos)[*totalProdutos].quantidade);
    printf("Digite o preço: ");
    scanf("%f", &(*produtos)[*totalProdutos].preco);
    printf("Digite a data de entrada (DD/MM/AAAA): ");
    scanf("%s", (*produtos)[*totalProdutos].dataEntrada);
    printf("Digite o fornecedor: ");
    scanf("%s", (*produtos)[*totalProdutos].fornecedor);

    (*totalProdutos)++;
    printf("Produto adicionado com sucesso!\n");
}

void listarProdutos(struct Produto *produtos, int totalProdutos) {
    if (totalProdutos > 0) {
        printf("Lista de Produtos:\n");
        for (int i = 0; i < totalProdutos; ++i) {
            printf("Nome: %s\n", produtos[i].nome);
            printf("Código de Barras: %s\n", produtos[i].codigoBarras);
            printf("Quantidade em Estoque: %d\n", produtos[i].quantidade);
            printf("Preço: %.2f\n", produtos[i].preco);
            printf("Data de Entrada: %s\n", produtos[i].dataEntrada);
            printf("Fornecedor: %s\n", produtos[i].fornecedor);
            printf("-----------\n");
        }
    } else {
        printf("Nenhum produto cadastrado.\n");
    }
}

void buscarProduto(struct Produto *produtos, int totalProdutos, char codigoBarras[]) {
    int encontrado = 0;
    for (int i = 0; i < totalProdutos; ++i) {
        if (strcmp(produtos[i].codigoBarras, codigoBarras) == 0) {
            printf("Produto encontrado:\n");
            printf("Nome: %s\n", produtos[i].nome);
            printf("Quantidade em Estoque: %d\n", produtos[i].quantidade);
            printf("Preço: %.2f\n", produtos[i].preco);
            printf("Data de Entrada: %s\n", produtos[i].dataEntrada);
            printf("Fornecedor: %s\n", produtos[i].fornecedor);
            encontrado = 1;
            break;
        }
    }
    if (!encontrado) {
        printf("Produto não encontrado.\n");
    }
}

void editarProduto(struct Produto *produtos, int totalProdutos, char codigoBarras[]) {
    for (int i = 0; i < totalProdutos; ++i) {
        if (strcmp(produtos[i].codigoBarras, codigoBarras) == 0) {
            printf("Digite o novo nome do produto: ");
            scanf("%s", produtos[i].nome);
            printf("Digite a nova quantidade em estoque: ");
            scanf("%d", &produtos[i].quantidade);
            printf("Digite o novo preço: ");
            scanf("%f", &produtos[i].preco);
            printf("Digite a nova data de entrada (DD/MM/AAAA): ");
            scanf("%s", produtos[i].dataEntrada);
            printf("Digite o novo fornecedor: ");
            scanf("%s", produtos[i].fornecedor);
            printf("Produto editado com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

void deletarProduto(struct Produto *produtos, int *totalProdutos, char codigoBarras[]) {
    for (int i = 0; i < *totalProdutos; ++i) {
        if (strcmp(produtos[i].codigoBarras, codigoBarras) == 0) {
            // Remover o produto movendo os elementos restantes uma posição para trás
            for (int j = i; j < *totalProdutos - 1; ++j) {
                produtos[j] = produtos[j + 1];
            }
            (*totalProdutos)--;
            printf("Produto deletado com sucesso!\n");
            return;
        }
    }
    printf("Produto não encontrado.\n");
}

int main() {
    struct Produto *produtos = NULL; // Inicialmente, nenhum produto na lista
    int totalProdutos = 0;
    int opcao;
    char codigoBarras[20];

    do {
        printf("Menu:\n");
        printf("1. Adicionar Produto\n");
        printf("2. Listar Produtos\n");
        printf("3. Buscar Produto\n");
        printf("4. Editar Produto\n");
        printf("5. Deletar Produto\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                adicionarProduto(&produtos, &totalProdutos);
                break;
            case 2:
                listarProdutos(produtos, totalProdutos);
                break;
            case 3:
                printf("Digite o código de barras: ");
                scanf("%s", codigoBarras);
                buscarProduto(produtos, totalProdutos, codigoBarras);
                break;
            case 4:
                printf("Digite o código de barras: ");
                scanf("%s", codigoBarras);
                editarProduto(produtos, totalProdutos, codigoBarras);
                break;
            case 5:
                printf("Digite o código de barras: ");
                scanf("%s", codigoBarras);
                deletarProduto(produtos, &totalProdutos, codigoBarras);
                break;
            case 0:
                printf("Saindo do programa. Obrigado!\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    // Liberar a memória alocada antes de sair do programa
    free(produtos);

    return 0;
}
