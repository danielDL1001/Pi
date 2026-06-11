#ifndef HASH_H
#define HASH_H

typedef struct No { // Estrutura para armazenar os nos da Tabela Hash
    char *chave;
    int valor;
    struct No *proximo;
} No;


typedef struct { // Estrutura principal da Tabela Hash
    No** itens;
    int tamanho;
} TabelaHash;

// Futuras funções
#endif