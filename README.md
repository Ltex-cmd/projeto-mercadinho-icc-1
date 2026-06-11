# Sistema de Mercadinho

Um sistema de controle de estoque, vendas e caixa de um mercadinho, feito em C (padrão C99).
Ele guarda o estoque, registra vendas, deixa consultar o estoque e o saldo do caixa, e salva
tudo no fim do dia pra carregar de novo no dia seguinte.

## Disciplina

- **Disciplina:** Introdução à Ciência da Computação I (SCC0221)
- **Professor:** Rudinei Goularte
- **Instituição:** USP — ICMC, Departamento de Ciências de Computação (SCC)

## Integrantes

- Lais Pinheiro Johonson — NUSP: 17903436
- Lucas Almeida Teixeira — NUSP: 16884285
- Livia Nobre Baldochi — NUSP: 1458974

## Como compilar e rodar

Compila com o GCC no padrão C99:

```bash
gcc -std=c99 -o mercadinho main.c
```

O programa lê comandos pela entrada padrão até receber o `FE`. Pra rodar direto:

```bash
./mercadinho
```

Ou jogando um arquivo de teste na entrada:

```bash
./mercadinho < teste.txt
```

## Comandos

Cada comando são duas letras maiúsculas seguidas dos dados que ele precisa. O `_` é um espaço.

| Comando | Formato | O que faz |
|---------|---------|-----------|
| Insere produto | `IP_<nome>_<quantidade>_<preço>` | Coloca um produto novo no estoque e dá o próximo código. Não mexe no caixa. |
| Aumenta estoque | `AE_<código>_<quantidade>` | Soma quantidade ao estoque de um produto. Desconta o custo do caixa. |
| Modifica preço | `MP_<código>_<preço>` | Troca o preço de um produto. |
| Venda | `VE_<código>_<código>_..._<-1>` | Vende a sequência de códigos até chegar no `-1`. |
| Consulta estoque | `CE` | Lista código, nome e quantidade de todos os produtos. |
| Consulta saldo | `CS` | Mostra o saldo do caixa. |
| Finaliza o dia | `FE` | Salva tudo num arquivo e fecha o programa. |

## Como sai na tela

Os comandos `VE`, `CE` e `CS` imprimem coisas. Os valores saem com duas casas decimais, e
cada saída termina numa linha com cinquenta hífens.

```
Venda
<nome>_<preço>
...
Total:_<preço total>
--------------------------------------------------

Consulta estoque
<código>_<nome>_<quantidade>
...
--------------------------------------------------

Consulta saldo
Saldo:_<saldo do caixa>
--------------------------------------------------
```

## Regras

- Os códigos são inteiros que começam em 0 e vão sendo dados em ordem conforme os produtos entram.
- O caixa começa com 100 reais e pode ficar negativo.
- `IP` não gera custo; `AE` mexe no caixa.
- Ao abrir, o sistema carrega o arquivo do dia anterior. Se ele não existir, o programa
  pergunta o tamanho do estoque e aloca a memória na hora.

## Arquivos

- `main.c` — laço principal que lê e distribui os comandos.
- `funcoes.h` — onde estão as definições de estrutura e constantes do programa.
- `funcoes.c` - onde estão as funcionalidades,
- Arquivo de dados — criado pelo `FE` e lido quando o programa abre no dia seguinte.
