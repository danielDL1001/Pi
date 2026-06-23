#ifndef FUNCAO_HASH_H
#define FUNCAO_HASH_H

#include "busca_sequencial.h" // Precisamos disso para a Tabela Hash conhecer a struct 'produto'

typedef struct No {
    produto prod;           // Agora o Nó guarda o produto real!
    struct No *proximo;     // O encadeamento para as colisões
} No;

typedef struct {
    No** itens;
    int tamanho;
    int colisoes;           // NOVO: Nosso contador de colisões para o relatório!
} TabelaHash;

// Assinaturas atualizadas:
TabelaHash* criarTabelaHash(int tamanho);
void destruir_TabelaHash(TabelaHash* tabela);
void hash_inserir(TabelaHash* tabela, produto p);
int hash_buscar(TabelaHash* tabela, int id_buscado);
void teste_busca_hash(TabelaHash* tabela, int *ids, int limite);

#endif