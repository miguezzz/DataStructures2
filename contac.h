#ifndef CONTAC_H
#define CONTAC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct contacorr {
    int cod;
    int cod_agencia;
    double saldo;
} ContaCorr;

// Cria uma conta corrente. Lembrar de usar free();
ContaCorr *cria_conta(cod, cod_agencia, saldo);

// Salva uma conta num arquivo externo
void salva_conta(ContaCorr *conta, FILE *out);

// Lê uma conta corrente a partir de um arquivo externo
ContaCorr *le_conta(FILE *in);

// Imprime uma conta
void imprime_conta(ContaCorr *c);

// imprime todas as contas do arquivo in
void imprime_todas_contas(FILE *in);

// Retorna o tamanho da conta em bytes (útil para fseek())
int tamanho();

#endif