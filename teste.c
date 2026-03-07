#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_BUSCAS 1000 // Mínimo exigido pelo protocolo
#define NUM_REPETICOES 3

typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} Produto;

// --- c) Implementação da busca sequencial ---
int buscaSequencial(Produto *vetor, int tamanho, int id_alvo) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i].id == id_alvo) {
            return i; // Retorna o índice onde encontrou
        }
    }
    return -1; // Retorna -1 se não encontrar (Inexistente)
}

// --- a) e b) Leitura do CSV e Vetor Dinâmico ---
Produto* carregarDados(const char *nomeArquivo, int *totalRegistros) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (!arquivo) {
        printf("ERRO: Nao foi possivel abrir o arquivo '%s'. Verifique se ele existe.\n", nomeArquivo);
        return NULL;
    }

    int capacidade = 100; // Capacidade inicial do vetor dinâmico
    Produto *vetor = (Produto *)malloc(capacidade * sizeof(Produto));
    int contador = 0;
    char linha[256];

    // Ignorar cabeçalho (descomente a linha abaixo se seu CSV tiver cabeçalho)
    // fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo)) {
        // Remover quebra de linha
        linha[strcspn(linha, "\r\n")] = 0;
        if (strlen(linha) == 0) continue;

        Produto p;
        char *token = strtok(linha, ",");
        
        // Validação básica para evitar falha em linhas mal formatadas
        if (!token || sscanf(token, "%d", &p.id) != 1) continue; 

        token = strtok(NULL, ",");
        if (token) {
            strncpy(p.nome, token, 50);
            p.nome[50] = '\0';
        }

        token = strtok(NULL, ",");
        if (token) {
            strncpy(p.categoria, token, 30);
            p.categoria[30] = '\0';
        }

        token = strtok(NULL, ",");
        if (token) p.valor = atof(token);

        // Expandir vetor dinâmico se necessário
        if (contador >= capacidade) {
            capacidade *= 2;
            vetor = (Produto *)realloc(vetor, capacidade * sizeof(Produto));
        }

        vetor[contador++] = p;
    }

    fclose(arquivo);
    *totalRegistros = contador;
    return vetor;
}

// --- d) Medição de Tempo ---
double medirTempoBusca(Produto *vetor, int tamanho, int id_alvo, int num_buscas) {
    clock_t inicio = clock();
    
    // Executa as buscas consecutivas conforme protocolo
    for (int i = 0; i < num_buscas; i++) {
        buscaSequencial(vetor, tamanho, id_alvo);
    }
    
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC; // Tempo total em segundos
}

// --- e) Protocolo Experimental ---
int main() {
    int totalRegistros = 0;
    
    // 1. Carregar vetor completamente antes de medir
    printf("Carregando dados...\n");
    Produto *vetor = carregarDados("dataset.csv", &totalRegistros);

    if (!vetor || totalRegistros == 0) {
        printf("Nenhum dado carregado. Encerrando programa.\n");
        if (vetor) free(vetor);
        return 1;
    }

    printf("Sucesso! %d registros carregados.\n\n", totalRegistros);

    // 3. Selecionar IDs para os cenários de teste
    int id_inicio = vetor[0].id;
    int id_meio = vetor[totalRegistros / 2].id;
    int id_fim = vetor[totalRegistros - 1].id;
    int id_inexistente = -999; // Assumindo que IDs sao positivos

    // Variáveis para armazenar o tempo total das 3 repetições
    double tempo_total_inicio = 0, tempo_total_meio = 0, tempo_total_fim = 0, tempo_total_inexistente = 0;

    printf("Iniciando bateria de testes (Repeticoes: %d | Buscas por repeticao: %d)...\n", NUM_REPETICOES, NUM_BUSCAS);

    // 5. Repetir 3 vezes
    for (int r = 1; r <= NUM_REPETICOES; r++) {
        tempo_total_inicio += medirTempoBusca(vetor, totalRegistros, id_inicio, NUM_BUSCAS);
        tempo_total_meio += medirTempoBusca(vetor, totalRegistros, id_meio, NUM_BUSCAS);
        tempo_total_fim += medirTempoBusca(vetor, totalRegistros, id_fim, NUM_BUSCAS);
        tempo_total_inexistente += medirTempoBusca(vetor, totalRegistros, id_inexistente, NUM_BUSCAS);
    }

    // Calcular as médias finais exigidas pelo protocolo
    double media_inicio_total = tempo_total_inicio / NUM_REPETICOES;
    double media_inicio_por_busca = media_inicio_total / NUM_BUSCAS;

    double media_meio_total = tempo_total_meio / NUM_REPETICOES;
    double media_meio_por_busca = media_meio_total / NUM_BUSCAS;

    double media_fim_total = tempo_total_fim / NUM_REPETICOES;
    double media_fim_por_busca = media_fim_total / NUM_BUSCAS;

    double media_inexistente_total = tempo_total_inexistente / NUM_REPETICOES;
    double media_inexistente_por_busca = media_inexistente_total / NUM_BUSCAS;

    // Impressão da Tabela de Resultados
    printf("\n=================== RESULTADOS DA BUSCA SEQUENCIAL ===================\n");
    printf("%-15s | %-20s | %-20s\n", "Cenario", "Tempo Total Medio (s)", "Tempo por Busca (s)");
    printf("----------------------------------------------------------------------\n");
    printf("%-15s | %-20.8f | %-20.8f\n", "Inicio", media_inicio_total, media_inicio_por_busca);
    printf("%-15s | %-20.8f | %-20.8f\n", "Meio", media_meio_total, media_meio_por_busca);
    printf("%-15s | %-20.8f | %-20.8f\n", "Fim", media_fim_total, media_fim_por_busca);
    printf("%-15s | %-20.8f | %-20.8f\n", "Inexistente", media_inexistente_total, media_inexistente_por_busca);
    printf("======================================================================\n");

    free(vetor);
    return 0;
}