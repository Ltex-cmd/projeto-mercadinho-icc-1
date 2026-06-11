#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "funcoes.h"
#include "funcoes.c"

int main(void) {
    /*buffer de comando*/
    char *comando;
    comando = malloc(3*sizeof(char));

    /*Inicializando o vetor buffer de comando*/
    comando[0] = '0'; comando[1] = '0';

    /*Laço que mantém o processo rodando*/
    while(strcmp(comando, "FE") != 0)
        scanf("%s", comando);

    free(comando);

    return 0;

}