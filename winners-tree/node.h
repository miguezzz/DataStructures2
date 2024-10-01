#include "../class-externa/clientes.h"
//#include "../class-externa/clientes.c"

// #include "../class-externa/registro.h"
// #include "../class-externa/registro.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    Cliente *cliente;
    struct node *left;
    struct node *right;
} Node;

void criaFolhas(FILE *in);

Node *criaNode(Cliente *cliente);

void imprimeNode(Node *node);

void imprimeArvore(Node *node);

void salvaNode(Node *node, FILE *out);

void salvaArvore(Node *node, FILE *out);