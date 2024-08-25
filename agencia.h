#ifndef AGENCIA_H
#define AGENCIA_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Agencia {
    int cod;
    char nome_agencia[50];
    char gerente[50];
} Agencia;

// Imprime agencia
void imprime_ag(Agencia *ag);

// Cria agencia. Lembrar de usar free(funcionario)
Agencia *nova_ag(int cod, char *nome, char *gerente);

// Salva agência no arquivo out, na posicao atual do cursor
void salva_ag(Agencia *ag, FILE *out);

// Le um agencia do arquivo in na posicao atual do cursor
// Retorna um ponteiro para agencia lida do arquivo
Agencia *le_ag(FILE *in);

// Retorna tamanho da agencia em bytes
int tamanho();

#endif