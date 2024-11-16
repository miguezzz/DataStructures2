#include "node.h"

int main(void) {
    int numParticoes = 5; // tb pode ser determinado dinamicamente
    FILE** arquivos = (FILE**) malloc(numParticoes * sizeof(FILE*));
    const char* nomesArquivos[] = {"part1.dat", "part2.dat", "part3.dat", "part4.dat", "part5.dat"};

    // Abre os arquivos de entrada. se tiver erro libera todos os arquivos
    for (int i = 0; i < numParticoes; i++) {
        arquivos[i] = fopen(nomesArquivos[i], "rb");
        if (arquivos[i] == NULL) {
            perror("Erro ao abrir o arquivo");
            for (int j = 0; j < i; j++) {
                fclose(arquivos[j]);
            }
            free(arquivos);
            return 1;
        }
    }

    // Abre o arquivo de saída
    FILE* saida = fopen("acoplamento.dat", "wb");
    if (saida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        for (int i = 0; i < numParticoes; i++) {
            fclose(arquivos[i]);
        }
        free(arquivos);
        return 1;
    }

    // Inicializa os nós folhas da árvore de vencedores
    Node** nodes = (Node**) malloc(numParticoes * sizeof(Node*));
    int* fimArquivo = (int*) calloc(numParticoes, sizeof(int)); // Array de flags para fim de arquivo

    // Cria os nós folhas iniciais
    for (int i = 0; i < numParticoes; i++) {
        nodes[i] = criaFolhas(arquivos[i]);
        if (feof(arquivos[i])) {
            fimArquivo[i] = 1; // Marca flag do fim de arquivo se já estiver no fim
        }
    }

    // Loop principal
    while (1) {
        int numFolhas = numParticoes;
        int arvore[2 * numFolhas - 1];
        arvoreVencedores(nodes, numFolhas, arvore, numFolhas - 1, fimArquivo);

        int vencedorIdx = encontrarVencedor(arvore);
        if (fimArquivo[vencedorIdx]) {
            break; // Sai do loop se o vencedor for de um arquivo que já terminou
        }

        printf("Menor cod_cliente: %d\n", nodes[vencedorIdx]->cliente->cod_cliente);

        // Salva o cliente com menor cod_cliente no arquivo de saída
        salvaCliente(nodes[vencedorIdx]->cliente, saida);

        nodes[vencedorIdx] = criaFolhas(arquivos[vencedorIdx]);
        if (feof(arquivos[vencedorIdx])) {
            fimArquivo[vencedorIdx] = 1; // Marca fim de arquivo se estiver no fim
        }
    }

    for (int i = 0; i < numParticoes; i++) {
        fclose(arquivos[i]);
        free(nodes[i]->cliente);
        free(nodes[i]);
    }
    free(arquivos);
    free(nodes);
    free(fimArquivo);
    fclose(saida);

    return 0;
}