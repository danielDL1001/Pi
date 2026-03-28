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
int busca_sequencial(produto *p, int total_linhas, int id_buscado);

#endif