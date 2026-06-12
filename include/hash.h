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

TabelaHash* criarTabelaHash(int tamanho);
void destruir_TabelaHash(TabelaHash* tabela);
unsigned long Hash(const char* chave, int tamanho);
/* Função hash:
Resto da divisão simples:

h(x) = x % m;
*/
void hash_inserir(TabelaHash* tabela, const char* chave, int valor);
int hash_buscar(TabelaHash* tabela, const char* chave);
void teste_busca_hash(TabelaHash* tabela, char** chaves, int* valores);

#endif // HASH_H