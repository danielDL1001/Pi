#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "../include/busca_sequencial.h"

int main() {
    // Abre o arquivo CSV para leitura
    FILE *dataset1 = fopen("dataset/dataset1.csv", "r");
    if (dataset1 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    clock_t tempo_inicial, tempo_final;
    double duracao;
    int total_linhas = 0;

    tempo_inicial = clock();
    produto *meus_produtos = lerCSV(dataset1, &total_linhas);
    tempo_final = clock();

    if (meus_produtos == NULL) {
        fclose(dataset1);
        return 1;
    }

    printf("%d / 100.004 produtos carregados\n", total_linhas);

    duracao = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %.10f segundos\n", duracao);

    int id_buscado;
    printf("\nDigite o ID para buscar: ");
    scanf("%d", &id_buscado);

    int posicao = busca_sequencial(meus_produtos, total_linhas, id_buscado);

    if (posicao != -1) {
        printf("\nProduto encontrado!\n");
        printf("ID: %d\n", meus_produtos[posicao].id);
        printf("Nome: %s\n", meus_produtos[posicao].nome);
        printf("Categoria: %s\n", meus_produtos[posicao].categoria);
        printf("Valor: %.2f\n", meus_produtos[posicao].valor);
    } else {
        printf("\nProduto com ID %d nao encontrado.\n", id_buscado);
    }

    free(meus_produtos);
    fclose(dataset1);

    return 0;
}

// Copilar: gcc -o main src/main.c src/busca_sequencial.c -I include -o main.out
// Executar: ./main.out