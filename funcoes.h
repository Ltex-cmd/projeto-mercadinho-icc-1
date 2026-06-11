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
    Produto *produtos;
    int total;
    int capacidade;
    float caixa;
} Mercadinho;

void insere_produto(Mercadinho *m, char nome[], int qtd, float preco);
void aumenta_estoque(Mercadinho *m, int codigo, int qtd);
void modifica_preco(Mercadinho *m, int codigo, float preco);
void realiza_venda(Mercadinho *m);
void consulta_estoque(Mercadinho *m);
void consulta_saldo(Mercadinho *m);

#endif