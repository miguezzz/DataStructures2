#include "clientes.h"

int main() {
    HashTable *hashTable = createHashTable(M_REGISTROS);

    insertCliente(hashTable, 1, "Cliente 1");
    insertCliente(hashTable, 2, "Cliente 2");
    insertCliente(hashTable, 3, "Cliente 3");

    Cliente *cliente = searchCliente(hashTable, 2);
    if (cliente) {
        printf("Cliente encontrado: %s\n", cliente->nome);
    } else {
        printf("Cliente não encontrado\n");
    }

    // removeCliente(hashTable, 2);
    cliente = searchCliente(hashTable, 2);
    if (!cliente) {
        printf("Cliente não encontrado");
    }

    freeHashTable(hashTable);
    return 0;
}