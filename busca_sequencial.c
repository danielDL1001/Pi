#include <stdio.h>

int busca(FILE *arquivo, int n, int valor, int *array) {
    if (n-1 < 0) { // Caso base: se n-1 for menor que 0, o valor não foi encontrado
        fprintf(arquivo, "O valor %d não foi encontrado no array.\n", valor);
        return 0;
        
    } else if (valor == array[n-1]) { // Se o valor for encontrado na posição n-1
        fprintf(arquivo, "O valor %d foi encontrado na posição %d.\n", valor, n-1);
        return 0;

    } else { // Chamada recursiva para verificar o próximo elemento
        return busca(arquivo, n-1, valor, array);
    }
}

int main() {
    FILE *arquivo = fopen("busca_sequencial.txt", "w+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    int n, valor, array[100]; // Supondo um tamanho máximo de 100 elementos
    printf("Digite o número de elementos: ");
    if (scanf("%d", &n) != 1) { 
        printf("Entrada inválida para o número de elementos.\n");
        return 1;
    }
    for (int i = 0; i < n; i++) { // Registro dos elementos do array
        printf("Digite o elemento %d: ", i + 1);
        if (scanf("%d", &array[i]) != 1) {
            printf("Entrada inválida para o elemento %d.\n", i + 1);
            return 1;
        }
    }
    printf("Digite o valor a ser buscado: ");
    if (scanf("%d", &valor) != 1) {
        printf("Entrada inválida para o valor a ser buscado.\n");
        return 1;
    }
    busca(arquivo, n, valor, array);
    fclose(arquivo);

    return 0;
}