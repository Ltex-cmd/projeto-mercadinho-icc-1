#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

void inicializar_mercadinho(Mercadinho *m) {
    FILE *fp;
    
    if ((fp = fopen("dia_anterior.dat", "r")) == NULL) {
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

/*funções vazias para que consiga compilar!! quando terminar a função, tirá-la daqui*/

void insere_produto(Mercadinho *m, char nome[], int qtd, float preco) {
    
}
void aumenta_estoque(Mercadinho *m, int codigo, int qtd) {

}
void modifica_preco(Mercadinho *m, int codigo, float preco) {

}
void realiza_venda(Mercadinho *m) {

}
void consulta_estoque(Mercadinho *m) {

}
void consulta_saldo(Mercadinho *m) {

}
void finalizar_dia(Mercadinho *m) {

}
