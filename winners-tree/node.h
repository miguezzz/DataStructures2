#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente {
    int cod_cliente;
    char nome[50];
    char data_nascimento[20]; // DD/MM/AAAA
} Cliente;

Cliente *carregaCliente(FILE *in);

typedef struct node {
    Cliente *cliente;
    struct node *left;
    struct node *right;
} Node;

Node *criaFolhas(FILE *in);

Node *criaNode(Cliente *cliente);

void arvoreVencedores(Node* nodes[], int numFolhas, int tree[], int startIdx);

int encontrarVencedor(int tree[]);

#endif