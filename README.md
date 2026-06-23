# 🔎 Estruturas de Dados e Algoritmos em C: Busca Sequencial vs. Tabela Hash

Implementação e análise comparativa de desempenho entre o algoritmo de **Busca Sequencial** e uma **Tabela Hash com tratamento de colisões por encadeamento**, utilizando leitura de dados reais a partir de arquivos CSV.

---

## 📌 Objetivo

Este projeto tem como objetivo:
- Praticar a manipulação e parsing de arquivos CSV em C.
- Trabalhar com alocação dinâmica de memória (`malloc`, `calloc` e `realloc`) e gerenciamento manual de ponteiros.
- Implementar e comparar as complexidades de tempo da Busca Sequencial ($O(n)$) e da Tabela Hash ($O(1)$ no caso médio).
- Medir o desempenho empírico de algoritmos usando a biblioteca `<time.h>`.
- Tratar colisões em tabelas hash utilizando o método de encadeamento (Lista Encadeada).

---

## 📁 Estrutura do Projeto

```text
├── src/
│   ├── main.c
│   ├── busca_sequencial.c
│   ├── funcao_hash.c
│   └── lista_encadeada.c
│
├── include/
│   ├── busca_sequencial.h
│   ├── funcao_hash.h
│   └── lista_encadeada.h
│
├── dataset/
│   ├── dataset1.csv
│   └── random_1000_ids.csv
│
└── README.md