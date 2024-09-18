#ifndef AGENCIA_H
#define AGENCIA_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct cliente {
    int cod_cliente;
    char nome[50];
    char data_nascimento[20]; // DD/MM/AAAA
} Cliente;

typedef struct registro {
    Cliente *cliente;
    int congelado;
} Registro;

Cliente *criaCliente(int cod_cliente, char *nome, char *data_nascimento);

void salvaCliente(Cliente *c, FILE *out);

void leClientes(FILE *in);

//int menor_chave(Registro registros[], int tamanho);

void selecaoSubst(FILE *in, FILE *out);

Cliente *carregaCliente(FILE *in);

// void carrega_m_clientes(FILE *in);

void imprimeCliente();

int tamanho();

#endif