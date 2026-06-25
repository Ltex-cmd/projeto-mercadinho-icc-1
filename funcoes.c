#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

static void imprime_separador(void) {
    int i;

    for (i = 0; i < 50; i++) {
        printf("-");
    }

    printf("\n");
}

static void *aloca_memoria(size_t tamanho) {
    void *ponteiro = malloc(tamanho);

    if (ponteiro == NULL) {
        exit(1);
    }

    return ponteiro;
}

static void *realoca_memoria(void *ponteiro, size_t tamanho) {
    void *novo_ponteiro = realloc(ponteiro, tamanho);

    if (novo_ponteiro == NULL) {
        free(ponteiro);
        exit(1);
    }

    return novo_ponteiro;
}

void inicializar_mercadinho(Mercadinho *m) {
    FILE *fp = fopen("estoque.txt", "r");

    /* Inicializa do zero quando nao existe arquivo salvo do dia anterior. */
    if (fp == NULL) {
        int capacidade;

        scanf("%d", &capacidade);
        if (capacidade <= 0) {
            capacidade = 1;
        }

        /* Primeiro dia: o tamanho inicial do estoque vem da entrada. */
        m->produtos = aloca_memoria(capacidade * sizeof(Produto));
        m->capacidade = capacidade;
        m->total = 0;
        m->caixa = SALDO_INICIAL;
    } else {
        int i;

        /* Dias seguintes: reconstroi o estado salvo no fechamento anterior. */
        fscanf(fp, "%f", &m->caixa);
        fscanf(fp, "%d", &m->capacidade);
        fscanf(fp, "%d", &m->total);
        m->produtos = aloca_memoria(m->capacidade * sizeof(Produto));

        for (i = 0; i < m->total; i++) {
            fscanf(fp, "%49s %d %f",
                   m->produtos[i].nome,
                   &m->produtos[i].quantidade,
                   &m->produtos[i].preco);
        }

        fclose(fp);
    }
}

/* Registra uma venda lendo codigos ate encontrar -1. */
void realiza_venda(Mercadinho *m) {
    int codigo;
    float soma = 0;

    scanf("%d", &codigo);

    while (codigo != -1) {
        printf("%s %.2f\n", m->produtos[codigo].nome, m->produtos[codigo].preco);
        m->produtos[codigo].quantidade--;
        soma += m->produtos[codigo].preco;

        scanf("%d", &codigo);
    }

    printf("Total: %.2f\n", soma);
    m->caixa += soma;
    imprime_separador();
}

/* Insere um produto novo e aumenta a capacidade quando o vetor fica cheio. */
void insere_produto(Mercadinho *m, char nome[], int qtd, float preco) {
    if (m->total == m->capacidade) {
        m->capacidade *= 2;
        m->produtos = realoca_memoria(m->produtos, m->capacidade * sizeof(Produto));
    }

    strcpy(m->produtos[m->total].nome, nome);
    m->produtos[m->total].quantidade = qtd;
    m->produtos[m->total].preco = preco;
    m->total++;
}

/* Compra novas unidades do produto e desconta o custo do caixa. */
void aumenta_estoque(Mercadinho *m, int codigo, int qtd) {
    m->produtos[codigo].quantidade += qtd;
    m->caixa -= qtd * m->produtos[codigo].preco;
}

/* Atualiza o preco usado nas proximas vendas e compras de estoque. */
void modifica_preco(Mercadinho *m, int codigo, float preco) {
    m->produtos[codigo].preco = preco;
}

/* Lista codigo, nome e quantidade dos produtos cadastrados. */
void consulta_estoque(Mercadinho *m) {
    int i;

    for (i = 0; i < m->total; i++) {
        printf("%d %s %d\n", i, m->produtos[i].nome, m->produtos[i].quantidade);
    }

    imprime_separador();
}

/* Mostra o valor atual disponivel no caixa. */
void consulta_saldo(Mercadinho *m) {
    printf("Saldo: %.2f\n", m->caixa);
    imprime_separador();
}

/* Salva o estado atual para o proximo dia e libera a memoria alocada. */
void finalizar_dia(Mercadinho *m) {
    FILE *fp = fopen("estoque.txt", "w");
    int i;

    if (fp == NULL) {
        free(m->produtos);
        m->produtos = NULL;
        exit(1);
    }

    /* Formato do arquivo: caixa, capacidade, total e a lista de produtos. */
    fprintf(fp, "%.2f\n", m->caixa);
    fprintf(fp, "%d\n", m->capacidade);
    fprintf(fp, "%d\n", m->total);

    for (i = 0; i < m->total; i++) {
        fprintf(fp, "%s %d %.2f\n",
                m->produtos[i].nome,
                m->produtos[i].quantidade,
                m->produtos[i].preco);
    }

    fclose(fp);
    free(m->produtos);
    m->produtos = NULL;
}
