#ifndef AGENCIA_H
#define AGENCIA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <limits.h>

#define M_REGISTROS 6

typedef struct cliente {
    int cod_cliente;
    char nome[50];
    char data_nascimento[20]; // DD/MM/AAAA
} Cliente;

Cliente *criaCliente(int cod_cliente, char *nome, char *data_nascimento);

void salvaCliente(Cliente *c, FILE *out);

void leClientes(FILE *in);

Cliente *carregaCliente(FILE *in);

void imprimeCliente();

int tamanho();

#endif