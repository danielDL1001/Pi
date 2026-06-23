#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include "../include/busca_sequencial.h"
#include "../include/funcao_hash.h"

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
    if (ids == NULL) {
        fclose(array);
        free(meus_produtos);
        return 1;
    }

// FASE 01
    printf("================= FASE 01 =================");
    // Teste do Melhor Caso (primeiro id)
    tempo_inicial = clock();
    busca_sequencial(meus_produtos, total_linhas, 83442);
    tempo_final = clock();
    temp_pri = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    printf("Tempo da busca do melhor caso: %.10f segundos\n", temp_pri);


    // Teste do Pior Caso (ultimo id)
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

// FASE 02
    printf("\n================= FASE 02: TABELA HASH =================\n");
    
    // 1. Carregamento da Tabela Hash
    tempo_inicial = clock();
    TabelaHash* minha_hash = criarTabelaHash(total_linhas); // Tamanho m = 100.004
    
    for(int i = 0; i < total_linhas; i++) {
        hash_inserir(minha_hash, meus_produtos[i]);
    }
    tempo_final = clock();
    double hash_load_time = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    
    printf("Tabela Hash preenchida com sucesso!\n");
    printf("Tempo de preenchimento da Hash: %.10f segundos\n", hash_load_time);
    printf("Numero total de colisoes registradas: %d\n\n", minha_hash->colisoes);

    // 2. Testes de Busca Hash (Comparando com os mesmos casos da Sequencial)
    
    // SUBSTITUA A PARTIR DAQUI DANIEL ->

    // Teste do Melhor Caso da Sequencial (primeiro id: 83442)
    tempo_inicial = clock();
    hash_buscar(minha_hash, 83442);
    tempo_final = clock();
    temp_pri = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    printf("Tempo da busca Hash (id inicio - 83442): %.10f segundos\n", temp_pri);

    // Teste do Pior Caso da Sequencial (ultimo id: 38990)
    tempo_inicial = clock();
    hash_buscar(minha_hash, 38990);
    tempo_final = clock();
    temp_ult = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    printf("Tempo da busca Hash (id final - 38990): %.10f segundos\n", temp_ult);

    // Teste de ID inexistente (-1)
    tempo_inicial = clock();
    hash_buscar(minha_hash, -1);
    tempo_final = clock();
    temp = (double)(tempo_final - tempo_inicial) / CLOCKS_PER_SEC;
    printf("Tempo da busca Hash (valor inexistente): %.10f segundos\n", temp);

    // Limpeza de memória
    destruir_TabelaHash(minha_hash);
    free(meus_produtos);
    free(ids);

    // Fechamento de arquivos
    fclose(dataset1);
    fclose(array);

    return 0;
}
// ATÉ AQUI :P