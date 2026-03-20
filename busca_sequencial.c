#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} produto;

//alterações (início) // Alocação Dinâmica
produto* lerCSV(FILE *dataset, int *total_linhas) {
    int capacidade = 1000; //capacidade inicial
    int linha = 0;
    
    //Alocação Dinâmica inicial
    produto *p = (produto *)malloc(capacidade * sizeof(produto));
    if (p == NULL)
    {
        printf("Memoria insuficiente!\n");
        exit(1); //encerra o programa se faltar memória.
    }
        
    //Leitura do Arquivo
    char cabecalho[200];
    if (fgets(cabecalho, sizeof(cabecalho), dataset) == NULL) {
        printf("Erro: Arquivo vazio!\n");
        return p; 
    }

    while (fscanf(dataset, "%d,%50[^,],%30[^,],%f",
        &p[linha].id,
        p[linha].nome,
        p[linha].categoria,
        &p[linha].valor) == 4) {
        linha++;
        
        if (linha >= capacidade) //quando a memória base de 1000 se encher, esse bloco executa
        {
            capacidade *= 2;
            p = (produto *)realloc(p, capacidade * sizeof(produto));
            if (p == NULL)
            {
                printf("Memoria insuficiente!\n");
                exit(1); //encerra o programa se faltar memória.
            }
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
//alterações (fim) // Busca Sequencial CONCLUÍDA


int main() {
    // Abre o arquivo CSV para leitura
    FILE *dataset = fopen("../dataset.csv", "r");
    if (dataset == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    
    int total_linhas = 0;

    produto *meus_produtos = lerCSV(dataset, &total_linhas);
    printf("%d / 100.004 produtos carregados\n", total_linhas);

    return 0;
}