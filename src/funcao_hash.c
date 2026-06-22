#include <stdio.h>
#include <stdlib.h>
#include "../include/funcao_hash.h"

TabelaHash* criarTabelaHash(int tamanho) {
    TabelaHash* tabela = (TabelaHash*)malloc(sizeof(TabelaHash));
    if (tabela == NULL) exit(1);
    
    tabela->tamanho = tamanho;
    tabela->colisoes = 0; // Inicia sem nenhuma colisão
    tabela->itens = (No**)calloc(tamanho, sizeof(No*)); // calloc já deixa todas as gavetas como NULL
    if (tabela->itens == NULL) exit(1);
    
    return tabela;
}

void hash_inserir(TabelaHash* tabela, produto p) {
    // A função hash exigida pelo professor: h(x) = x % m
    int indice = p.id % tabela->tamanho; 
    
    // Cria o novo "No" para guardar o produto
    No* novo_no = (No*)malloc(sizeof(No));
    if (novo_no == NULL) exit(1);
    
    novo_no->prod = p;
    novo_no->proximo = NULL;

    // LÓGICA DE COLISÃO E ENCADEAMENTO:
    if (tabela->itens[indice] != NULL) {
        // Se a gaveta NÃO está vazia, bateu! Colisão detectada!
        tabela->colisoes++;
        
        // O novo produto aponta para quem já estava na gaveta
        novo_no->proximo = tabela->itens[indice]; 
    }
    
    // O novo produto assume a frente da gaveta
    tabela->itens[indice] = novo_no;
}

// A busca agora recebe o ID inteiro
int hash_buscar(TabelaHash* tabela, int id_buscado) {
    // Vai direto na gaveta certa usando a matemática
    int indice = id_buscado % tabela->tamanho;
    
    No* atual = tabela->itens[indice];
    
    // Percorre a lista encadeada daquela gaveta (caso tenha havido colisões)
    while (atual != NULL) {
        if (atual->prod.id == id_buscado) {
            return atual->prod.id; // Achou!
        }
        atual = atual->proximo;
    }
    
    return -1; // Não achou
}

void destruir_TabelaHash(TabelaHash* tabela) {
    if (tabela == NULL) return;
    
    // Percorre todas as gavetas da tabela
    for (int i = 0; i < tabela->tamanho; i++) {
        No* atual = tabela->itens[i];
        
        // Se houver uma lista encadeada (colisões) nesta gaveta, libera nó por nó
        while (atual != NULL) {
            No* temp = atual;
            atual = atual->proximo;
            free(temp); // Libera o bloco inteiro de memória do Nó (que já contém o produto)
        }
    }
    
    // Libera o vetor de gavetas e, por fim, a própria tabela
    free(tabela->itens);
    free(tabela);
}