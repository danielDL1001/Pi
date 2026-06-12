#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/hash.h"

TabelaHash* criarTabelaHash(int tamanho) {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (tabela == NULL) exit(1);
    tabela->tamanho = tamanho;
    tabela->itens = (No**)calloc(tamanho, sizeof(No*));
    if (tabela->itens == NULL) {
        free(tabela);
        exit(1);
    }
    
    return tabela;
}

void destruir_TabelaHash(TabelaHash* tabela) {
    if (tabela == NULL) return;
    
    for (int i = 0; i < tabela->tamanho; i++) {
        No* atual = tabela->itens[i];
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp->chave);
            free(temp);
        }
    }
    
    free(tabela->itens);
    free(tabela);
}

void hash_inserir(TabelaHash* tabela, const char* chave, int valor) {
    unsigned long indice = Hash(chave, tabela->tamanho);
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) exit(1);
    
    novo_no->chave = strdup(chave);
    novo_no->valor = valor;
    novo_no->proximo = tabela->itens[indice];
    tabela->itens[indice] = novo_no;
}

int hash_buscar(TabelaHash* tabela, const char* chave) {
    unsigned long indice = Hash(chave, tabela->tamanho);
    No* atual = tabela->itens[indice];
    
    while (atual != NULL) {
        if (strcmp(atual->chave, chave) == 0) {
            printf("Valor encontrado: %d\n", atual->valor);
            return atual->valor;
        }
        atual = atual->proximo;
    }
    
    printf("Chave não encontrada.\n");
    return -1;
}

void teste_busca_hash(TabelaHash* tabela, char** chaves, int* valores) {
    for (int i = 0; i < 1000; i++) {
        hash_buscar(tabela, chaves[i]);
    }
}