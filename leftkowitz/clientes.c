#include "clientes.h"

// Cria uma conta corrente. Lembrar de usar free();
Cliente *criaCliente(int cod_cliente, char *nome, int idade) {

    Cliente *c = (Cliente *) malloc(sizeof(Cliente));

    c->cod_cliente = cod_cliente;
    strcpy(c->nome, nome);
    strcpy(c->idade, idade);

    return c;
}

// Salva um cliente num arquivo externo
void salvaCliente(Cliente *c, FILE *out) {
    if (fwrite(&c->cod_cliente, sizeof(int), 1, out) < 1) {
        free(c);
        exit(1);
    }
    fwrite(c->nome, sizeof(char), 50, out);
    fwrite(c->idade, sizeof(int), 1, out);
}

// Função para carregar clientes em memória
Cliente *carregaCliente(FILE *in) {

    Cliente *c = (Cliente *) malloc(sizeof(Cliente));
    if (c == NULL) {
        free(c);
        return NULL; // falha ao puxar cliente (fim do arquivo)
    }

    if (fread(&c->cod_cliente, sizeof(int), 1, in) != 1) {
        // printf("\nFim do arquivo...\n");
        free(c);
        return NULL; // Falha na leitura do cod_cliente
    }
    //printf("-------%d", sizeof(char) * sizeof(c->nome));
    fread(c->nome, sizeof(char), sizeof(c->nome), in);
    fread(c->idade, sizeof(int), sizeof(c->idade), in);
    return c;
}

void leClientes(FILE *in) {
    printf("\n\nLendo clientes do arquivo...\n\n");
    //rewind(in);
    int contador = 0;
    Cliente *c;
    while ((c = carregaCliente(in)) != NULL) {
        printf("%d\n", ++contador);
        imprimeCliente(c);
        free(c);
    }
}

void leftkowitz() {
    //função 1
    // passo 1: cria arquivo 2 e chama A2() passando o A1 e o novo A2

    //função 2
    // passo 2: cria arquivo 3 e chama A3() passando o A2 e o novo A3_idade
    // passo 3: ordena o arquivo 3 por idade gerando o A4

    //função 3
    // gerar A5 e A6
    // ordenar A6 por cod_cliente, gerando A7
    // juntar A1 com A7 e gerar A8
}

void A2() {
    
}

