#include "clientes.h"

// Cria uma conta corrente. Lembrar de usar free();
Cliente *criaCliente(int cod_cliente, char *nome, char *data_nascimento) {

    Cliente *c = (Cliente *) malloc(sizeof(Cliente));

    c->cod_cliente = cod_cliente;
    strcpy(c->nome, nome);
    strcpy(c->data_nascimento, data_nascimento);

    return c;
}

// Salva um cliente num arquivo externo
void salvaCliente(Cliente *c, FILE *out) {
    if (fwrite(&c->cod_cliente, sizeof(int), 1, out) < 1) {
        free(c);
        exit(1);
    }
    fwrite(c->nome, sizeof(char), 50, out);
    fwrite(c->data_nascimento, sizeof(char), 20, out);
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
    fread(c->data_nascimento, sizeof(char), sizeof(c->data_nascimento), in);
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

// Função para imprimir os dados do cliente
void imprimeCliente(Cliente *c) {
    
    if (c == NULL) {
        return;
    }

    printf("**********************************************");
    printf("\nCódigo do cliente: %d", c->cod_cliente);
    printf("\nNome do cliente: %s", c->nome);
    printf("\nData de nascimento: %s", c->data_nascimento);
    printf("\n**********************************************\n\n");
}

int tamanho() {
    return sizeof(int) + // conta->cod_cliente
            sizeof(char) * 50 + // conta->nome
            sizeof(char) * 20;// conta->nasc
}