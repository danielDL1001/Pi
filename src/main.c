#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "../include/busca_sequencial.h"

int main() {
    // Variáveis
    clock_t tempo_inicial, tempo_final;
    double csv_time, temp, temp_ult, temp_pri;
    int total_linhas = 0, total_ids = 0;

    // Abre o arquivo CSV para leitura
    FILE *dataset1 = fopen("dataset/dataset1.csv", "r");
    if (dataset1 == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    // Abre o arquivo de IDs para teste de busca
    FILE *array = fopen("dataset/random_1000_ids.csv", "r");
    if (array == NULL) {
        printf("Erro ao abrir o arquivo de ids aleatorios.\n");
        return 1;
    }

    // Leitura do CSV
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

    // Leitura dos IDs
    int *ids = ler_ids(array, &total_ids);

    // Teste do melhor caso (primeiro id)
    tempo_inicial = clock();
    busca_sequencial(meus_produtos, total_linhas, 83442);
    tempo_final = clock();
    temp_pri = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    printf("Tempo da busca do melhor caso: %.10f segundos\n", temp_pri);


    // Teste do pior caso (ultimo id)
    tempo_inicial = clock();
    busca_sequencial(meus_produtos, total_linhas, 38990);
    tempo_final = clock();
    temp_ult = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    printf("Tempo da busca do pior caso: %.10f segundos\n", temp_ult);


    // Teste ids inexistente
    tempo_inicial = clock();
    busca_sequencial(meus_produtos, total_linhas, -1);
    tempo_final = clock();
    temp = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    printf("Tempo da busca valor inexistente: %.10f segundos\n", temp);

    // Busca id inicial, id do meio e id final
    teste_busca_ids(meus_produtos, total_linhas, ids, 1);
    teste_busca_ids(meus_produtos, total_linhas, ids, 500);
    teste_busca_ids(meus_produtos, total_linhas, ids, 1000);

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

    // Limpeza de memória e fechamento de arquivos
    free(meus_produtos);
    free(ids);
    fclose(dataset1);
    fclose(array);

    return 0;
}

// Copilar: gcc -o main src/*.c -I include -o programa.out
// Executar: ./programa.out