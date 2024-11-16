#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

typedef struct A1 {
    int cod_cliente;
    char nome[50];
    int idade;
} Cliente;

Cliente *criaCliente(int cod_cliente, char *nome, int idade);

void salvaCliente(Cliente *c, FILE *out);

void leClientes(FILE *in);

Cliente *carregaCliente(FILE *in);









