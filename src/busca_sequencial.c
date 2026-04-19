#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/busca_sequencial.h"

// Função para ler o CSV e retornar um array de produtos
produto* lerCSV(FILE *dataset1, int *total_linhas) {
    int capacidade = 1000; //Capacidade inicial
    int linha = 0;
    
    //Alocação Dinâmica inicial
    produto *p = (produto *)malloc(capacidade * sizeof(produto));
    if (p == NULL)
    {
        printf("Memoria insuficiente!\n");
        free(p);
        exit(1); //encerra o programa se faltar memória.
    }
        
    //Leitura do Arquivo
    char cabecalho[200];
    if (fgets(cabecalho, sizeof(cabecalho), dataset1) == NULL) {
        printf("Erro: Arquivo vazio!\n");
        free(p);
        return p; 
    }

    while (fscanf(dataset1, "%d,%50[^,],%30[^,],%f",
        &p[linha].id,
        p[linha].nome,
        p[linha].categoria,
        &p[linha].valor) == 4) {
        linha++;
        
        // Se encher, aumentar a capacidade
        if (linha >= capacidade) // Quando a memória base de 1000 se encher, esse bloco executa
        {
            capacidade *= 2;
            produto *temp = (produto *)realloc(p, capacidade * sizeof(produto));
            if (temp == NULL) {
                printf("Memoria insuficiente!\n");
                free(p);
                exit(1);
            }
        p = temp; // Encerra o programa se faltar memória.
        }
    }
    *total_linhas = linha; // Salva a quantidade de linhas lidas
    return p;
}
// Alocação Dinâmica e leitura do CSV concluida

// Função para ler os IDs do arquivo
int* ler_ids(FILE *arquivo, int *total_ids) {
    int capacidade = 1000;
    int count = 0;

    int *ids = malloc(capacidade * sizeof(int));
    if (!ids) {
        printf("Erro de memoria!\n");
        exit(1);
    }

    while (fscanf(arquivo, "%d", &ids[count]) == 1) {
        count++;

        if (count >= capacidade) {
            capacidade *= 2;
            int *temp = realloc(ids, capacidade * sizeof(int));
            if (!temp) {
                free(ids);
                printf("Erro de memoria!\n");
                exit(1);
            }
            ids = temp;
        }
    }

    *total_ids = count;
    return ids;
}
// Função para realizar a busca sequencial

// Busca sequencial no CSV
int busca_sequencial(produto *p, int total_linhas, int id_buscado){
    for(int i = 0; i < total_linhas; i++){
        if (p[i].id == id_buscado) // Se o id do índice for igual ao id escolhido, retorna o índice. 
        {
            return i;
        }
    }
    return -1;
}

// Função para testar a busca sequencial para um conjunto de IDs e medir o tempo gasto
void teste_busca_ids(produto *produtos, int total_linhas, int *ids, int limite) {
    clock_t inicio = clock();
    for (int i = 0; i < limite; i++) {
        busca_sequencial(produtos, total_linhas, ids[i]);
    }
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("Busca dos primeiros %d IDs -> Tempo: %.10f segundos\n", limite, tempo);
}