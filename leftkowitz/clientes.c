#ifndef CLIENTES_H
#define CLIENTES_H

#include "clientes.h"

// Cria uma conta corrente. Lembrar de usar free();
Cliente *criaCliente(int cod_cliente, char *nome, int idade) {

    Cliente *c = (Cliente *) malloc(sizeof(Cliente));

    c->cod_cliente = cod_cliente;
    strcpy(c->nome, nome);
    c->idade = idade;

    return c;
}

// Salva um cliente num arquivo externo
void salvaCliente(Cliente *c, FILE *out) {
    if (fwrite(&c->cod_cliente, sizeof(int), 1, out) < 1) {
        // free(c);
        exit(1);
    }
    fwrite(c->nome, sizeof(char), 50, out);
    fwrite(&c->idade, sizeof(int), 1, out);
}

// Função para carregar clientes em memória
Cliente *carregaCliente(FILE *in) {

    Cliente *c = (Cliente *) malloc(sizeof(Cliente));
    if (c == NULL) {
        return NULL; // falha ao puxar cliente (fim do arquivo)
    }

    if (fread(&c->cod_cliente, sizeof(int), 1, in) != 1) {
        printf("\nFim do arquivo...\n");
        free(c);
        return NULL; // Falha na leitura do cod_cliente
    }
    //printf("-------%d", sizeof(char) * sizeof(c->nome));
    fread(c->nome, sizeof(char), 50, in);
    fread(&c->idade, sizeof(int), 1, in);

    printf("Cliente carregado: %s\n", c->nome);
    
    return c;
}

void leClientes(FILE *in) {
    printf("\n\nLendo clientes do arquivo...\n\n");

    rewind(in);

    int contador = 0;
    Cliente *c;

    while ((c = carregaCliente(in)) != NULL) {
        printf("%d\n", ++contador);
        imprimeCliente(c);
        //free(c);
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
    printf("\nIdade: %d", c->idade);
    printf("\n**********************************************\n\n");
}

void leftkowitz(FILE *in) {
    
    A2(in);

    A3(in);

    A4(in);

    //função 3
    // gerar A5 e A6
    // ordenar A6 por cod_cliente, gerando A7
    // juntar A1 com A7 e gerar A8
}

void A2(FILE *in) {

    //criando A2
    const char *A2 = "A2.dat";

    FILE *out = fopen(A2, "w+b");
    if (!out) {
        printf("Erro ao criar o arquivo A2.\n");
        exit(1);
    }

    int ED = 1; // ED = endereço de disco
    Cliente *c;
    rewind(in);
    while ((c = carregaCliente(in)) != NULL) {
        if (fwrite(&ED, sizeof(int), 1, out) != 1) {
            printf("Erro ao escrever ED no arquivo A2.\n");
            free(c);
            break;
        }
        printf("ED: %d\n", ED);
        fwrite(&c->cod_cliente, sizeof(int), 1, out);
        fwrite(&c->idade, sizeof(int), 1, out);

        ED++;
    }
}

void A3(FILE *in) {

    //criando A2
    const char *A3 = "A3.dat";

    FILE *out = fopen(A3, "w+b");
    if (!out) {
        printf("Erro ao criar o arquivo A2.\n");
        exit(1);
    }

    int ED = 1; // ED = endereço de disco
    Cliente *c;
    rewind(in);
    while ((c = carregaCliente(in)) != NULL) {
        if (fwrite(&ED, sizeof(int), 1, out) != 1) {
            printf("Erro ao escrever ED no arquivo A2.\n");
            free(c);
            break;
        }
        printf("ED: %d\n", ED);
        fwrite(&c->cod_cliente, sizeof(int), 1, out);
        fwrite(&c->idade, sizeof(int), 1, out);

        ED++;
    }
}

void A4(FILE *in) {
    const char *A4 = "A4.dat";

    FILE *out = fopen(A4, "w+b");

    if (!out) {
        printf("Erro ao criar o arquivo A4.\n");
        exit(1);
    }

    int numClientes = 0;
    Cliente *clientes[100]; // Assuming a maximum of 100 clients

    rewind(in);
    Cliente *c;
    while ((c = carregaCliente(in)) != NULL) {
        clientes[numClientes++] = c;
    }

    qsort(clientes, numClientes, sizeof(Cliente *), comp);

    for (int i = 0; i < numClientes; i++) {
        fwrite(&clientes[i]->cod_cliente, sizeof(int), 1, out);
        fwrite(clientes[i]->nome, sizeof(char), 50, out);
        fwrite(&clientes[i]->idade, sizeof(int), 1, out);
        free(clientes[i]);
    }

    imprimeCliente(c);

    fclose(out);
}

// comparador pra idade (vai ser passado para a função qsort no A4)
int comp(const void* a, const void* b) {
    Cliente *clienteA = *(Cliente **)a;
    Cliente *clienteB = *(Cliente **)b;

    return (clienteA->idade - clienteB->idade);
}

#endif