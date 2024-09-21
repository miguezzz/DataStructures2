#include "clientes.h"

typedef struct registro {
    Cliente *cliente;
    int congelado;
} Registro;

// Registro *carregaRegistro(FILE *in);

// void imprimeRegistro(Registro *r);

// void leRegistros(FILE *in);

int menorChave(Registro registros[], int tamanho);

// void gravaMenor(Registro *registro, FILE *out);

void preencheVetor(FILE *in, Registro registros[], int tamanho);

void substituiRegistro(FILE *in, Registro registro[], int indice_menor);