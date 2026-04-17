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
    double csv_time, temp;
    int total_linhas = 0;

    tempo_inicial = clock();
    produto *meus_produtos = lerCSV(dataset1, &total_linhas);
    tempo_final = clock();

    if (meus_produtos == NULL) {
        fclose(dataset1);
        return 1;
    }
    printf("%d / 100.004 produtos carregados\n", total_linhas);

    csv_time = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    printf("Tempo de leitura do CSV: %.10f segundos\n", csv_time);

    tempo_inicial = clock();
    busca_sequencial(meus_produtos, total_linhas, -1);
    tempo_final = clock();
    temp = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    printf("Tempo da busca valor inexistente: %.10f segundos\n", temp);

    busca_seq_esp(meus_produtos, total_linhas, 1);
    busca_seq_esp(meus_produtos, total_linhas, 50000);
    busca_seq_esp(meus_produtos, total_linhas, 100000);

    int ids_encontrados[1000];
    int count = 0;
    for (int i = 0; i < 1000 && i < total_linhas; i++) {
        int id_buscado = meus_produtos[i].id;

        int posicao = busca_sequencial(meus_produtos, total_linhas, id_buscado);

        if (posicao != -1) {
            ids_encontrados[count++] = meus_produtos[posicao].id;
        } else {
            printf("Produto com ID %d nao encontrado.\n", id_buscado);
        }
    }

    printf("\nIDs encontrados:\n[");
    for (int i = 0; i < count; i++) {
        printf("%d", ids_encontrados[i]);

        if (i < count - 1) {
            printf(", ");
        }
    }

    printf("]\n");

    free(meus_produtos);
    fclose(dataset1);

    return 0;
}

// Copilar: gcc -o main src/*.c -I include -o main.out
// Executar: ./main.out