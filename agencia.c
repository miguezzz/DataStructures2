#include "agencia.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime agencia
void imprime_ag(Agencia *ag) {
    printf("**********************************************");
    printf("\nCódigo da agência: %d", ag->cod);
    printf("\nNome da agência: %s", ag->nome_agencia);
    printf("\nNome do gerente: %s", ag->gerente);
    printf("\n**********************************************\n\n");
}

// Cria agência. Lembrar de usar free(ag)
Agencia *nova_ag(int cod, char *nome, char *gerente) {
    Agencia *ag = (Agencia *) malloc(sizeof(Agencia));

    ag->cod = cod;
    strcpy(ag->nome_agencia, nome);
    strcpy(ag->gerente, gerente);

    return ag;
}

// Salva agência no arquivo out, na posicao atual do cursor
void salva_ag(Agencia *ag, FILE *out) {
    fwrite(&ag->cod, sizeof(int), 1, out);
    fwrite(ag->nome_agencia, sizeof(char), sizeof(ag->nome_agencia), out);
    fwrite(ag->gerente, sizeof(char), sizeof(ag->gerente), out);
}

Agencia *le_ag(FILE *in) {
    Agencia *ag = (Agencia *) malloc(sizeof(Agencia));

    if (fread(&ag->cod, sizeof(int), 1, in) < 1) {
        free(ag);
        return NULL;
    }
    fread(ag->nome_agencia, sizeof(char), sizeof(ag->nome_agencia), in);
    fread(ag->gerente, sizeof(char), sizeof(ag->gerente), in);
    
    return ag;
}