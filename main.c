#include <stdio.h>
#include <string.h>
#include "funcoes.h"

/*
 * funcao principal do programa
 * nao recebe parametros porque os comandos vem todos pela entrada padrao
 * o int no retorno e o jeito normal da main avisar que terminou sem erro
 * aqui o mercadinho e iniciado e cada comando chama sua funcao
 */
int main(void) {
    Mercadinho mercadinho;
    char comando[3];

    inicializar_mercadinho(&mercadinho);

    while (scanf("%2s", comando) == 1) {
        if (strcmp(comando, "IP") == 0) {
            char nome[MAX_NOME];
            int qtd;
            float preco;

            scanf("%49s %d %f", nome, &qtd, &preco);
            insere_produto(&mercadinho, nome, qtd, preco);
        } else if (strcmp(comando, "AE") == 0) {
            int codigo;
            int qtd;

            scanf("%d %d", &codigo, &qtd);
            aumenta_estoque(&mercadinho, codigo, qtd);
        } else if (strcmp(comando, "MP") == 0) {
            int codigo;
            float preco;

            scanf("%d %f", &codigo, &preco);
            modifica_preco(&mercadinho, codigo, preco);
        } else if (strcmp(comando, "VE") == 0) {
            realiza_venda(&mercadinho);
        } else if (strcmp(comando, "CE") == 0) {
            consulta_estoque(&mercadinho);
        } else if (strcmp(comando, "CS") == 0) {
            consulta_saldo(&mercadinho);
        } else if (strcmp(comando, "FE") == 0) {
            finalizar_dia(&mercadinho);
            break;
        }
    }

    return 0;
}
