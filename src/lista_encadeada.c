#include <stdio.h>
#include <stdlib.h>
#include "../include/lista_encadeada.h"

// Função essencial para resolver conflitos na Tabela Hash
ListaEncadeada *criar() { // Cria uma lista encadeada
    ListaEncadeada *lista = (ListaEncadeada *)malloc(sizeof(ListaEncadeada));
    if (lista != NULL)
    {
        lista->primeiro = NULL;
        lista->ultimo = NULL;
        lista->quantidade = 0;
    }
    return lista;
}

void lista_destruir(ListaEncadeada *lista) { // Destruir a lista encadeada
    free(lista);
}

int lista_vazia(ListaEncadeada *lista) { // Verificar se a lista esta vazia
    return lista != NULL && lista->primeiro == NULL;
}

void adicionar_final(ListaEncadeada *lista, int valor) { // Adcionar dado ao final da lista
    No *no = (No *)malloc(sizeof(No));
    if (no == NULL) return;

    no->dado = valor;
    no->proximo = NULL;

    if (lista_vazia(lista)) {
        lista->primeiro = no;
    }
    else {
        lista->ultimo->proximo = no;
    }

    lista->ultimo = no;
    lista->quantidade++;
}

No *buscar(ListaEncadeada *lista, int valor) { // Busca um valor na lista
    if (lista_vazia(lista))
        return NULL;
    No *no = lista->primeiro;
    while (no != NULL)
    {
        if (no->dado == valor)
            return no;
        no = no->proximo;
    }
    return NULL;
}

void remover(ListaEncadeada *lista, int valor) { //Remove um valor da lista
    if (lista_vazia(lista)) return;

    // Remover primeiro
    No *no = lista->primeiro;
    if (no->dado == valor) {
        lista->primeiro = no->proximo;
        lista->quantidade--;
        free(no);
        return;
    }
    
    // Remover meio
    No *anterior = no;    
    while (no->proximo != NULL) {
        anterior = no;
        no = no->proximo;
    if (no->dado == valor) {
        anterior->proximo = no->proximo;
        lista->quantidade--;
        break;
        }
    }
    
    // Remover ultimo
    if (no->proximo == NULL && no->dado == valor) {
        lista->ultimo = anterior;
    }

    free(no); // Remover o Nó
}

void lista_exibir(ListaEncadeada *lista) { // Exibir lista completa
    No *no = lista->primeiro;
    while (no != NULL) {
        printf("%i ", no->dado);
        no = no->proximo;
        if (no->proximo != NULL) printf(",");
    }
    printf("]\n");
}