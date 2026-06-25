#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

/*
 * imprime a linha de 50 hifens que aparece depois das consultas e vendas
 * nao precisa de parametro porque esse tamanho nunca muda
 * e void pois so imprime na tela
 */
static void imprime_separador(void) {
    int i;

    for (i = 0; i < 50; i++) {
        printf("-");
    }

    printf("\n");
}

/*
 * separa memoria para o vetor usado no estoque
 * recebe o tamanho em bytes porque e assim que o malloc trabalha
 * retorna void * porque esse ponteiro pode virar um vetor de produtos depois
 */
static void *aloca_memoria(size_t tamanho) {
    void *ponteiro = malloc(tamanho);

    if (ponteiro == NULL) {
        exit(1);
    }

    return ponteiro;
}

/*
 * muda o tamanho de uma memoria que ja tinha sido alocada
 * recebe o ponteiro antigo e o novo tamanho porque sao os dados pedidos pelo realloc
 * tambem retorna void * para servir para o vetor de produtos
 */
static void *realoca_memoria(void *ponteiro, size_t tamanho) {
    void *novo_ponteiro = realloc(ponteiro, tamanho);

    if (novo_ponteiro == NULL) {
        free(ponteiro);
        exit(1);
    }

    return novo_ponteiro;
}

/*
 * prepara a struct do mercadinho no comeco do programa
 * recebe Mercadinho * para mexer no mesmo mercadinho criado na main
 * nao retorna nada porque os dados ficam salvos direto nessa struct
 * se ja existir estoque.txt, le o dia anterior, senao le a capacidade inicial
 */
void inicializar_mercadinho(Mercadinho *m) {
    FILE *fp = fopen("estoque.txt", "r");

    /* se nao tiver arquivo salvo, esse e o primeiro dia */
    if (fp == NULL) {
        int capacidade;

        scanf("%d", &capacidade);
        if (capacidade <= 0) {
            capacidade = 1;
        }

        /* no primeiro dia o tamanho do estoque vem da entrada */
        m->produtos = aloca_memoria(capacidade * sizeof(Produto));
        m->capacidade = capacidade;
        m->total = 0;
        m->caixa = SALDO_INICIAL;
    } else {
        int i;

        /* nos outros dias o programa recupera o que foi salvo antes */
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

/*
 * faz uma venda lendo codigos ate chegar no -1
 * recebe Mercadinho * porque precisa olhar os produtos, diminuir o estoque e mudar o caixa
 * e void porque o resultado aparece na tela e as mudancas ficam na propria struct
 */
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

/*
 * coloca um produto novo no final do vetor
 * recebe o mercadinho para alterar o estoque, o nome para copiar, a quantidade inicial e o preco
 * nao retorna nada porque o produto fica guardado direto no vetor da struct
 */
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

/*
 * aumenta o estoque de um produto que ja existe
 * recebe o codigo para achar o produto e a qtd para saber quanto somar
 * usa Mercadinho * porque tambem precisa descontar esse custo do caixa
 * e void pois altera os campos da struct diretamente
 */
void aumenta_estoque(Mercadinho *m, int codigo, int qtd) {
    m->produtos[codigo].quantidade += qtd;
    m->caixa -= qtd * m->produtos[codigo].preco;
}

/*
 * troca o preco de um produto
 * recebe o codigo para achar qual produto mudar e o novo preco para salvar
 * retorna void porque so atualiza um campo dentro do vetor
 */
void modifica_preco(Mercadinho *m, int codigo, float preco) {
    m->produtos[codigo].preco = preco;
}

/*
 * mostra todos os produtos cadastrados
 * recebe Mercadinho * para acessar o total e o vetor de produtos
 * nao retorna nada porque a consulta e impressa direto na saida
 */
void consulta_estoque(Mercadinho *m) {
    int i;

    for (i = 0; i < m->total; i++) {
        printf("%d %s %d\n", i, m->produtos[i].nome, m->produtos[i].quantidade);
    }

    imprime_separador();
}

/*
 * mostra o saldo atual do caixa
 * recebe Mercadinho * porque o caixa fica guardado dentro dele
 * e void porque apenas imprime o valor
 */
void consulta_saldo(Mercadinho *m) {
    printf("Saldo: %.2f\n", m->caixa);
    imprime_separador();
}

/*
 * fecha o programa salvando o estado em estoque.txt
 * recebe Mercadinho * para pegar caixa, produtos e quantidade total, e tambem liberar a memoria
 * retorna void porque a funcao so grava o arquivo e limpa o que foi alocado
 */
void finalizar_dia(Mercadinho *m) {
    FILE *fp = fopen("estoque.txt", "w");
    int i;

    if (fp == NULL) {
        free(m->produtos);
        m->produtos = NULL;
        exit(1);
    }

    /* o arquivo guarda caixa, capacidade, total e depois os produtos */
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
