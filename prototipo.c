#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "funcoes.h"

int main(void) {
    /*Inicializar mercadinho*/
    Mercadinho m;
    /*Ponteiro para passar o mercadinho entre funções*/
    Mercadinho *ptr_m = &m;
    inicializar_mercadinho(ptr_m);


    /*buffer de comando*/
    char comando[3];

    /*Inicializando o vetor buffer de comando*/
    comando[0] = '0'; comando[1] = '0';

    /*Laço que mantém o processo rodando */
    while(strcmp(comando, "FE") != 0) {
        scanf("%s", comando);

        if (strcmp(comando, "CE") == 0)
            consulta_estoque(ptr_m);
        else if (strcmp(comando, "CS") == 0)
            consulta_saldo(ptr_m);
        else if (strcmp(comando, "IP") == 0) {
            char nome[MAX_NOME];
            int qtd;
            float preco;

            scanf("%s %d %f", nome, &qtd, &preco);
            insere_produto(ptr_m, nome, qtd, preco);           
        }
        else if(strcmp(comando, "AE") == 0) {
            int codigo;
            int qtd;

            scanf("%d %d", &codigo, &qtd);
            aumenta_estoque(ptr_m, codigo, qtd);
        }
        else if(strcmp(comando, "MP") == 0) {
            int codigo;
            float preco;

            scanf("%d %f", &codigo, &preco);
            modifica_preco(ptr_m, codigo, preco);
        }

        else if(strcmp(comando, "VE") == 0) {
            realiza_venda(ptr_m);
        }

    }
    finalizar_dia(ptr_m);
    return 0;

}