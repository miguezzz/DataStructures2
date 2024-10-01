#include "node.h"

int main(void) {

    FILE* arquivos[5];

    arquivos[0] = fopen("part1.dat", "rb");
    arquivos[1] = fopen("part2.dat", "rb");
    arquivos[2] = fopen("part3.dat", "rb");
    arquivos[3] = fopen("part4.dat", "rb");
    arquivos[4] = fopen("part5.dat", "rb");

    FILE* saida = fopen("acoplamento.dat", "wb");

    for(int i = 0; i < 5; i++) {
        criaFolhas(arquivos[i]);
    }

    // for(int i = 0; i < 5; i++) {
    //     leClientes(arquivos[i]);
    // }
}