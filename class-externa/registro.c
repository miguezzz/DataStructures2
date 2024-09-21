#include "registro.h"
#include "clientes.h"

// fazer um gerador de partições usando o menorChave e gravaMenor

Registro *carregaRegistro(FILE *in) {

    Registro *r = (Registro *) malloc(sizeof(Registro));
    if (r == NULL) {
        return NULL; // Falha ao alocar memória
    }

    if (fread(&r->cliente->cod_cliente, sizeof(int), 1, in) < 1) {
        free(r);
        return NULL;
    }
    fread(r->cliente->nome, sizeof(char), sizeof(r->cliente->nome), in);
    fread(r->cliente->data_nascimento, sizeof(char), sizeof(r->cliente->data_nascimento), in);

    fread(&r->congelado, sizeof(int), 1, in);

    return r;
}

void imprimeRegistro(Registro *r) {

    if (r == NULL) {
        return;
    }

    printf("**********************************************");
    printf("\nCódigo do cliente: %d", r->cliente->cod_cliente);
    printf("\nNome do cliente: %s", r->cliente->nome);
    printf("\nData de nascimento: %s", r->cliente->data_nascimento);
    printf("\nCongelado: %d", r->congelado);
    printf("\n**********************************************\n\n");
}

void leRegistros(FILE *in) {

    printf("\n\nLendo registros do arquivo...\n\n");
    //rewind(in);
    int contador = 0;
    Registro *r;
    while ((r = carregaRegistro(in)) != NULL) {
        printf("%d\n", ++contador);
        imprimeRegistro(r);
        free(r);
    }
}

// Função para encontrar o índice do menor cliente não congelado
int menorChave(Registro registros[], int tamanho) {

    int menor = INT_MAX; // tem um numero gigante definido. usamos como base pra achar numeros menores
    int indice = -1;

    for (int i = 0; i < tamanho; i++) {
        // se o registro não estiver congelado e seu cod_cliente for menor do que o menor número atual,
        if (!registros[i].congelado && registros[i].cliente->cod_cliente < menor) {
            // menor cod_cliente vira o cod_cliente atual
            menor = registros[i].cliente->cod_cliente;
            // e o indice a ser retornado vira o atual
            indice = i;
        }
    }
    return indice;
}

// grava o registro na partição de saída
void gravaMenor(Registro *registro, FILE *out) {
    if ((fwrite(&registro->cliente->cod_cliente, sizeof(int), 1, out)) != 1) {
        printf("Erro ao gravar registro no arquivo de saída\n");
        free(registro);
        exit(1);
    }
    fwrite(registro->cliente->nome, sizeof(char), 50, out);
    fwrite(registro->cliente->data_nascimento, sizeof(char), 20, out);
    fwrite(&registro->congelado, sizeof(int), 1, out);   
}