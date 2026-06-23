#ifndef BUSCA_SEQUENCIAL_H
#define BUSCA_SEQUENCIAL_H

typedef struct { // Estrutura para armazenar os dados dos produtos do Dataset
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} produto;

produto* lerCSV(FILE *dataset1, int *total_linhas); // Ler o CSV e retornar um array de produtos
int* ler_ids(FILE *arquivo, int *total_ids); // Ler os IDs do arquivo e retornar um array de inteiros
int busca_sequencial(produto *p, int total_linhas, int id_buscado); // Realizar a busca sequencial e retornar o índice do produto encontrado ou -1 se não encontrado
void teste_busca_ids(produto *produtos, int total_linhas, int *ids, int limite); // Testar a busca sequencial para um conjunto de IDs e medir o tempo gasto

#endif