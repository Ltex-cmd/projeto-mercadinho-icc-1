Sistema de Mercadinho

Integrantes:
Lais Pinheiro Johonson - NUSP: 17903436
Lucas Almeida Teixeira - NUSP: 16884285
Livia Nobre Baldochi - NUSP: 1458974

Compilacao:
gcc -std=c99 -Wall -Wextra main.c funcoes.c -o mercadinho

Execucao:
./mercadinho

O programa le comandos pela entrada padrao ate receber FE. Se nao houver
arquivo estoque.txt do dia anterior, a primeira entrada deve ser a capacidade
inicial do estoque. Ao finalizar, o estado do caixa e dos produtos e salvo em
estoque.txt para a proxima execucao.
