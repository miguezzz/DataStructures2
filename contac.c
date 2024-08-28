#include "contac.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Cria uma conta corrente. Lembrar de usar free();
ContaCorr *cria_conta(cod, cod_agencia, saldo) {
    ContaCorr *conta = (ContaCorr *) malloc(sizeof(ContaCorr));

    conta->cod = cod;
    conta->cod_agencia = cod_agencia;
    conta->saldo = saldo;

    return conta;
}

// Salva uma conta num arquivo externo
void salva_conta(ContaCorr *conta, FILE *out) {
    if (fwrite(&conta->cod, sizeof(int), 1, out) < 1) {
        free(conta);
        return NULL;
    }
    fwrite(&conta->cod_agencia, sizeof(int), 1, out);
    fwrite(&conta->saldo, sizeof(double), 1, out);
}

// Lê uma conta corrente a partir de um arquivo externo
ContaCorr *le_conta(FILE *in) {
    ContaCorr *conta = (ContaCorr *) malloc(sizeof(ContaCorr));

    if (fread(&conta->cod, sizeof(int), 1, in) < 1) {
        free(conta);
        return NULL;
    }
    fread(&conta->cod_agencia, sizeof(int), 1, in);
    fread(&conta->saldo, sizeof(double), 1, in);

    return conta;
}

// Imprime uma conta
void imprime_conta(ContaCorr *conta) {
    printf("**********************************************");
    printf("\nCódigo da conta corrente: %d", conta->cod);
    printf("\nCódigo da agência: %s", conta->cod_agencia);
    printf("\nSaldo da conta: %.2f", conta->saldo);
    printf("\n**********************************************\n\n");
}

// imprime todas as contas do arquivo in
void imprime_todas_contas(FILE *in) {
    ContaCorr *conta;
    
    while ((conta = le_conta(in)) != NULL) {
        printf("\n");
        imprime_conta(conta);
        free(conta);
    }
}

// Retorna o tamanho da conta em bytes (útil para fseek())
int tamanho() {
    return sizeof(int) + // conta->cod
            sizeof(int) + // conta->cod_agencia
            sizeof(double); // conta->saldo
}