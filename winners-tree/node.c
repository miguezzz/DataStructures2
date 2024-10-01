#include "node.h"

// esta função carrega os nós folhas da árvore a partir das partições
void criaFolhas(FILE *in) {

    Node *n = (Node *) malloc(sizeof(Node));

    n->cliente = carregaCliente(in);
    n->left = NULL;
    n->right = NULL;
}

// Node *criaNode(Cliente *cliente) {
//     Node *node = (Node *) malloc(sizeof(Node));
//     // criaFolhas(node, cliente);
//     node->left = NULL;
//     node->right = NULL;
//     return node;
// }

// void imprimeNode(Node *node) {
//     if (node->cliente != NULL) {
//         printf("Cliente: %s\n", node->cliente->nome);
//     } else {
//         printf("Cliente: NULL\n");
//     }
// }

// void imprimeArvore(Node *node) {
//     if (node != NULL) {
//         imprimeNode(node);
//         imprimeArvore(node->left);
//         imprimeArvore(node->right);
//     }
// }

// void salvaNode(Node *node, FILE *out) {
//     if (node->cliente != NULL) {
//         salvaCliente(node->cliente, out);
//     }
// }

// void salvaArvore(Node *node, FILE *out) {
//     if (node != NULL) {
//         salvaNode(node, out);
//         salvaArvore(node->left, out);
//         salvaArvore(node->right, out);
//     }
// }