#include "clientes.h"

int main() {
    // Cria a tabela hash
    HashTable *hashTable = createHashTable();

    // Insere alguns clientes
    insertCliente(hashTable, 49, "<João>");
    insertCliente(hashTable, 51, "<Carla>");
    insertCliente(hashTable, 59, "<Maria>");
    insertCliente(hashTable, 103, "<Ana>");
    insertCliente(hashTable, 3, "<José>");
    insertCliente(hashTable, 87, "<Bia>");

    // exibe a tabela hash
    printf("Clientes na tabela hash:\n");

    printHash(hashTable);

    // busca por um cliente específico
    int cod_cliente = 3;
    Cliente *cliente = searchCliente(hashTable, cod_cliente);
    if (cliente) {
        printf("\nCliente encontrado: %s (Código: %d)\n", cliente->nome, cliente->cod_cliente);
        free(cliente);
    } else {
        printf("\nCliente com código %d não encontrado\n", cod_cliente);
    }

    // remove um cliente
    printf("\nRemovendo cliente com código %d...\n", cod_cliente);
    removeCliente(hashTable, cod_cliente);

    // exibe todos os clientes na tabela hash após a remoção
    printf("\nClientes na tabela hash após a remoção:\n");
    printHash(hashTable);

    return 0;
}