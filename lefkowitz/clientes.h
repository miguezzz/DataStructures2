#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

typedef struct cliente {
    int cod_cliente;
    char nome[50];
    int idade;
} Cliente;

Cliente *criaCliente(int cod_cliente, char *nome, int idade);
void salvaCliente(Cliente *c, FILE *out);
void imprimeCliente(Cliente *c);
void leClientes(FILE *in);
Cliente *carregaCliente(FILE *in);
void leftkowitz(FILE *in);

void A2(FILE *in);
void A3(FILE *in);
void A4(FILE *in);

int comp(const void* a, const void* b);
