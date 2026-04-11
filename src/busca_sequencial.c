#include <stdio.h>
#include <stdlib.h>
#include "../include/busca_sequencial.h"


//alterações (início) // Alocação Dinâmica
produto* lerCSV(FILE *dataset1, int *total_linhas) {
    int capacidade = 1000; //capacidade inicial
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
        if (linha >= capacidade) //quando a memória base de 1000 se encher, esse bloco executa
        {
            capacidade *= 2;
            produto *temp = (produto *)realloc(p, capacidade * sizeof(produto));
            if (temp == NULL) {
                printf("Memoria insuficiente!\n");
                free(p);
                exit(1);
            }
        p = temp; //encerra o programa se faltar memória.
        }
    }
    *total_linhas = linha; //salva a quantidade de linhas lidas
    return p;
    }
//alterações (fim) // Alocação Dinâmica CONCLUÍDA 

//alterações (início) // Busca Sequencial
int busca_sequencial(produto *p, int total_linhas, int id_buscado){
    for(int i = 0; i < total_linhas; i++){
        if (p[i].id == id_buscado) // Se o id do índice for igual ao id escolhido, retorna o índice. 
        {
            return i;
        }
        
    }
    return -1;
}