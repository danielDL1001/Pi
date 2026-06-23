#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

typedef struct No {
    int dado;
    struct No *proximo;
} No;

typedef struct {
    No *primeiro;
    No *ultimo;
    int quantidade;
} ListaEncadeada;

ListaEncadeada *criar();
void lista_destruir(ListaEncadeada *lista);
void adicionar_final(ListaEncadeada *lista, int valor);
int lista_vazia(ListaEncadeada *lista);
No *buscar(ListaEncadeada *lista, int valor);
void remover(ListaEncadeada *lista, int valor);
void lista_exibir(ListaEncadeada *lista);

#endif