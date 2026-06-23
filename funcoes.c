#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

void inicializar_mercadinho(Mercadinho *m) {
    FILE *fp;
    
    if ((fp = fopen("dia_anterior.txt", "r")) == NULL) {
        int capacidade;
        scanf("%d", &capacidade);

        /*Inicializando cada variável da struct do mercadinho*/
        m->produtos = malloc(capacidade*sizeof(Produto));   
        m->capacidade = capacidade;
        m->total = 0;
        m->caixa = SALDO_INICIAL;
    }
    else {} /*a fazer leitura e escrita dos arquivos!!*/
}

void printa_separador() {
    int i = 0;

    while (i < 50) {
        printf("-");
        i++;
    }

    printf("\n");
}

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
    printa_separador();
}
/*funções vazias para que consiga compilar!! quando terminar a função, tirá-la daqui*/

void insere_produto(Mercadinho *m, char nome[], int qtd, float preco) {
    
}
void aumenta_estoque(Mercadinho *m, int codigo, int qtd) {

}
void modifica_preco(Mercadinho *m, int codigo, float preco) {

}

void consulta_estoque(Mercadinho *m) {

}
void consulta_saldo(Mercadinho *m) {

}
void finalizar_dia(Mercadinho *m) {

}
