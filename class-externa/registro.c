#include "registro.h"
#include "clientes.h"

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