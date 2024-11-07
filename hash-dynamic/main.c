#include "clientes.h"

int main() {
    HashTable *hashTable = createHashTable(M_REGISTROS);

    insertCliente(hashTable, 1, "Cliente 1");
    insertCliente(hashTable, 2, "Cliente 2");
    insertCliente(hashTable, 3, "Cliente 3");
    insertCliente(hashTable, 4, "Cliente 4");
    insertCliente(hashTable, 5, "Cliente 5");
    insertCliente(hashTable, 6, "Cliente 6");
    insertCliente(hashTable, 7, "Cliente 7");
    insertCliente(hashTable, 10, "Cliente 10");
    insertCliente(hashTable, 12, "Cliente 12");

    Cliente *cliente = searchCliente(hashTable, 2);
    if (cliente) {
        printf("Cliente encontrado: %s\n", cliente->nome);
    } else {
        printf("Cliente não encontrado\n");
    }

    // removeCliente(hashTable, 2);
    cliente = searchCliente(hashTable, 6);
    if (cliente) {
        printf("Cliente encontrado: %s\n", cliente->nome);
    } else {
        printf("Cliente não encontrado\n");
    }

    freeHashTable(hashTable);
    return 0;
}