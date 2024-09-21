#include "clientes.h"

typedef struct registro {
    Cliente *cliente;
    int congelado;
} Registro;

int menorChave(Registro registros[], int tamanho);