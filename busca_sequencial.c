#include <stdio.h>
#include <string.h>

#define MAX_LINHAS 1000
#define MAX_COLS 4 // Número de colunas no dataset (Código, Nome, Tipo, Valor)
#define TAM 50

typedef struct {
    char codigo[TAM];
    char nome[TAM];
    char tipo[TAM];
    char valor[TAM];
} Produto;

Produto p[MAX_LINHAS]; // Matriz para armazenar os dados do CSV

int lerCSV(FILE *arquivo) { // Leitura do arquivo CSV e armazenamento dos dados em uma matriz
    int linha = 0;
    while (linha < MAX_LINHAS &&
        fscanf(arquivo,"%99[^,],%99[^,],%99[^,],%99[^\n]",
        p[linha].codigo,
        p[linha].nome,
        p[linha].tipo,
        p[linha].valor) == 4) {

        linha++;
        fgetc(arquivo);
    }

    return linha;
}

void search(int atual, int total, int coluna, char valor[]) { // Busca sequencial
    int contador = 0;
    for (int i = 0; i < MAX_LINHAS; i++) {
        if (strcmp(matriz[i][coluna], busca) == 0) {
            busca[i] = 1; // Marca a posição onde o valor foi encontrado
        } else {
            busca[i] = 0; // Marca a posição onde o valor não foi encontrado
        }
    }
}

int choice(FILE *arquivo) { // Escolha do usuário para o tipo de valor a ser procurado
    int num;
    printf("======================\n");
    printf("Buscar o produto por:\n");
    printf("\n1 - Código do produto;\n");
    printf("2 - Nome do produto;\n");
    printf("3 - tipo do produto;\n");
    printf("4 - Valor do produto;\n");
    printf("======================\n");
    scanf("%d", &num);
    switch (num) {
        case 1: // Código
            fprintf(arquivo, "Você escolheu procurar pelo Código do produto.\n");
            return 0;
            break;
        case 2: // Nome
            fprintf(arquivo, "Você escolheu procurar pelo Nome do produto.\n");
            return 1;
            break;
        case 3: // Tipo
            fprintf(arquivo, "Você escolheu procurar pelo Tipo do produto.\n");
            return 2;
            break;
        case 4: // Valor
            fprintf(arquivo, "Você escolheu procurar pelo Valor do produto.\n");
            return 3;
            break;
        default:
            printf("Opção inválida. Por favor, escolha um número entre 1 e 4.\n");
            return -1;
    }
}

int main() {
    FILE *arquivo = fopen("dataset.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    int linhas = lerCSV(arquivo);
    int coluna = choice(arquivo);
    if(coluna == -1){
        printf("Encerrando programa...\n");
        return 1;
    }
    char busca[100];
    printf("Digite o valor: ");
    scanf("%s", busca);
    search(linhas, coluna, busca);
    
    fclose(arquivo);

    return 0;
}