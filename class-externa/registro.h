#include "clientes.h"

typedef struct registro {
    Cliente *cliente;
    int congelado;
} Registro;

int menorChave(Registro registros[], int tamanho);

void preencheVetor(FILE *in, Registro registros[], int tamanho);

int substituiRegistro(FILE *in, Registro registro[], int indice_menor);

void selecaoSubst(FILE *in, Registro registros[], FILE *out);

void descongelaRegistros(Registro registros[]);

FILE *criaParticao(int particaoAtual);