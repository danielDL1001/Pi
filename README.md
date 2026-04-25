# 🔎 Busca Sequencial em C

Implementação do algoritmo de **busca sequencial** em linguagem C, com leitura de dados a partir de arquivos CSV e análise de desempenho em diferentes cenários.

---

## 📌 Objetivo

Este projeto tem como objetivo:

- Praticar manipulação de arquivos em C
- Trabalhar com alocação dinâmica de memória (`malloc` / `realloc`)
- Implementar busca sequencial
- Medir desempenho de algoritmos
- Analisar complexidade computacional

---

## 📁 Estrutura do Projeto
├── src/
│ ├── main.c
│ ├── busca_sequencial.c
│
├── include/
│ ├── busca_sequencial.h
│
├── dataset/
│ ├── dataset1.csv
│ ├── random_1000_ids.csv
│
└── README.md


---

## 🧱 Estrutura de Dados

```c
typedef struct {
    int id;
    char nome[51];
    char categoria[31];
    float valor;
} produto;