#ifndef AGENCIA_H
#define AGENCIA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct cliente {
    int cod_cliente;
    char nome[100];
    char data_nascimento[10]; // DD/MM/AAAA
    int congelado;
} Cliente;

void selecaoSubst(FILE *in, FILE *out);

Cliente *carregaCliente(FILE *in);

void carrega_m_clientes(FILE *in);

void imprimeCliente();

#endif