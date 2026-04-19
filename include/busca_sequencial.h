#ifndef BUSCA_SEQUENCIAL_H
#define BUSCA_SEQUENCIAL_H

#include <stdio.h>

typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} produto;

produto* lerCSV(FILE *dataset1, int *total_linhas);
int* ler_ids(FILE *arquivo, int *total_ids);
int busca_sequencial(produto *p, int total_linhas, int id_buscado);
void teste_busca_ids(produto *produtos, int total_linhas, int *ids, int limite);

#endif