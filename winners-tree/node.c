#include "node.h"

// esta função carrega os nós folhas da árvore a partir das partições
Node *criaFolhas(FILE *in) {

    Node *n = (Node *) malloc(sizeof(Node));

    n->cliente = carregaCliente(in);
    n->left = NULL;
    n->right = NULL;

    return n;
}

// Função para carregar clientes em memória
Cliente *carregaCliente(FILE *in) {

    Cliente *c = (Cliente *) malloc(sizeof(Cliente));
    if (c == NULL) {
        free(c);
        return NULL; // falha ao puxar cliente (fim do arquivo)
    }

    if (fread(&c->cod_cliente, sizeof(int), 1, in) != 1) {
        free(c);
        return NULL; // Falha na leitura do cod_cliente
    }

    fread(c->nome, sizeof(char), sizeof(c->nome), in);
    fread(c->data_nascimento, sizeof(char), sizeof(c->data_nascimento), in);
    return c;
}

void arvoreVencedores(Node* nodes[], int numFolhas, int arvore[], int startIdx) {
    // Inicializa as folhas da árvore
    // Cada folha da árvore de vencedores é inicializada com o índice correspondente ao nó folha
    for (int i = 0; i < numFolhas; i++) {
        arvore[startIdx + i] = i;
    }

    // constrói a árvore de vencedores a partir das folhas.
    for (int i = startIdx - 1; i >= 0; i--) {
        // Índices dos filhos esquerdo e direito
        int left = arvore[2 * i + 1];
        int right = arvore[2 * i + 2];

        // Compara os cod_cliente dos filhos e armazena o índice do menor no pai
        if (nodes[left]->cliente->cod_cliente <= nodes[right]->cliente->cod_cliente) {
            arvore[i] = left;
        } else {
            arvore[i] = right;
        }
    }
}

int encontrarVencedor(int arvore[]) {
    return arvore[0];
}