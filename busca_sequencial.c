#include <stdio.h>
#include <string.h>

#define MAX_LINHAS 1000
#define MAX_COLS 4 // Número de colunas no dataset (Código, Nome, Tipo, Valor)
#define TAM 100 // Tamanho máximo para cada campo

typedef struct {
    char id[TAM];
    char nome[TAM];
    char categoria[TAM];
    char valor[TAM];
} Produto;

Produto p[MAX_LINHAS]; // Matriz para armazenar os dados do CSV

int lerCSV(FILE *dataset) { // Leitura do arquivo CSV e armazenamento dos dados em uma matriz
    int linha = 0;
    while (linha < MAX_LINHAS &&
        fscanf(dataset,"%99[^,],%99[^,],%99[^,],%99[^\n]",
        p[linha].id,
        p[linha].nome,
        p[linha].categoria,
        p[linha].valor) == 4) {

        linha++;
        fgetc(dataset);
    }

    return linha;
}

void search(FILE *buscaArquivo, int atual, int total, int coluna, char valor[]) { // Busca sequencial
    // Verifica se o valor a ser buscado é maior ou igual ao total de linhas lidas
    if (atual >= total) {
        fprintf(buscaArquivo, "Produto nao encontrado.\n");
        return;
    }

    char *campo;
    switch(coluna){
        case 0: campo = p[atual].id; break;
        case 1: campo = p[atual].nome; break;
        case 2: campo = p[atual].categoria; break;
        case 3: campo = p[atual].valor; break;
        default: return;
    }
    

    if(strcmp(campo, valor) == 0){

        fprintf(buscaArquivo, "\nProduto encontrado:\n");
        fprintf(buscaArquivo, "Codigo: %s\n", p[atual].id);
        fprintf(buscaArquivo, "Nome: %s\n", p[atual].nome);
        fprintf(buscaArquivo, "Tipo: %s\n", p[atual].categoria);
        fprintf(buscaArquivo, "Valor: %s\n", p[atual].valor);

        return;
    }
    search(buscaArquivo, atual + 1, total, coluna, valor);
}

int choice(FILE *buscaArquivo) { // Escolha do usuário para o tipo de valor a ser procurado
    int num;
    printf("======================\n");
    printf("Buscar o produto por:\n");
    printf("\n1 - Id do produto;\n");
    printf("2 - Nome do produto;\n");
    printf("3 - Categoria do produto;\n");
    printf("4 - Valor do produto;\n");
    printf("======================\n");
    if (scanf("%d", &num) != 1) {
        fprintf(buscaArquivo, "Entrada inválida. Por favor, insira um número.\n");
        return -1;
    }
    switch (num) {
        case 1: // Id
            printf("Você escolheu procurar pelo Id do produto.\n");
            return 0;
        case 2: // Nome
            printf("Você escolheu procurar pelo Nome do produto.\n");
            return 1;
        case 3: // Categoria
            printf("Você escolheu procurar pela Categoria do produto.\n");
            return 2;
        case 4: // Valor
            printf("Você escolheu procurar pelo Valor do produto.\n");
            return 3;
        default:
            fprintf(buscaArquivo, "Opção inválida. Por favor, escolha um número entre 1 e 4.\n");
            return -1;
    }
}

int main() {
    // Abre o arquivo CSV para leitura
    FILE *dataset = fopen("../dataset.csv", "r");
    if (dataset == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    // Abre o arquivo de busca para escrita
    FILE *buscaArquivo = fopen("buscasequencial.txt", "w+");
    if (buscaArquivo == NULL) {
        printf("Erro ao abrir o arquivo de busca.\n");
        return 1;
    }
    // Lê o arquivo CSV e armazena os dados em uma matriz
    int linhas = lerCSV(dataset);
    fprintf(buscaArquivo, "Produtos carregados: %d\n", linhas);
    int coluna = choice(buscaArquivo);
    // Verifica se a escolha do usuário é válida
    if(coluna == -1){
        fprintf(buscaArquivo, "Encerrando programa...\n");
        return 1;
    }
    char busca[100];
    printf("\nDigite o valor: ");
    scanf(" %99[^\n]", busca);
    // Realiza a busca sequencial
    search(buscaArquivo, 0, linhas, coluna, busca);
    fclose(dataset);
    fclose(buscaArquivo);

    return 0;
}