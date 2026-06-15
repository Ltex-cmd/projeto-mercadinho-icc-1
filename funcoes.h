#ifndef FUNCOES_H
#define FUNCOES_H

#define MAX_NOME 50
#define SALDO_INICIAL 100.0f

typedef struct {
    char nome[MAX_NOME];
    float preco;
    int quantidade;
} Produto;

typedef struct {
    /*vetor de produtos*/
    Produto *produtos;
    /*total de produtos*/
    int total;
    /*capacidade de produtos no estoque*/
    int capacidade;
    /*saldo em caixa*/
    float caixa;
} Mercadinho;

void insere_produto(Mercadinho *m, char nome[], int qtd, float preco);
void aumenta_estoque(Mercadinho *m, int codigo, int qtd);
void modifica_preco(Mercadinho *m, int codigo, float preco);
void realiza_venda(Mercadinho *m);
void consulta_estoque(Mercadinho *m);
void consulta_saldo(Mercadinho *m);
void inicializar_mercadinho(Mercadinho *m);
void finalizar_dia(Mercadinho *m);

#endif