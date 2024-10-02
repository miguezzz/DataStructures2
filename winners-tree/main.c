#include "node.h"

int main(void) {

    FILE* arquivos[5];

    arquivos[0] = fopen("part1.dat", "rb");
    arquivos[1] = fopen("part2.dat", "rb");
    arquivos[2] = fopen("part3.dat", "rb");
    arquivos[3] = fopen("part4.dat", "rb");
    arquivos[4] = fopen("part5.dat", "rb");

    FILE* saida = fopen("acoplamento.dat", "wb");

    Node* nodes[5];

    for(int i = 0; i < 5; i++) {
        nodes[i] = criaFolhas(arquivos[i]);
    }

    for(int i = 0; i < 5; i++) {
        printf("Chave %d\n", nodes[i]->cliente->cod_cliente);
    }

    int numFolhas = 5;
    int arvore[2 * numFolhas - 1];
    arvoreVencedores(nodes, numFolhas, arvore, numFolhas - 1);

    int vencedorIdx = encontrarVencedor(arvore);
    printf("Menor cod_cliente: %d\n", nodes[vencedorIdx]->cliente->cod_cliente);

    salvaCliente();

    for (int i = 0; i < 5; i++) {
        fclose(arquivos[i]);
    }

    return 0;
}