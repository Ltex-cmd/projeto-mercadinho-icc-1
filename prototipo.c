#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "funcoes.h"

int main(void) {
    /*buffer de comando*/
    char *comando;
    comando = malloc(2*sizeof(char));

    /*Inicializando o vetor buffer de comando*/
    comando[0] = '0'; comando[1] = '0';

    while(comando[0] != 'F' || comando[1] != 'E')
        scanf("%c%c", comando, comando+1);
    return 0;

}