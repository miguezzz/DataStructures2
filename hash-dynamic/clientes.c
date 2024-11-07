#include "clientes.h"

HashTable *createHashTable(int size) {
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->table = (Cliente **)malloc(size * sizeof(Cliente *));
    for (int i = 0; i < size; i++) {
        hashTable->table[i] = NULL;
    }
    hashTable->size = size;
    hashTable->count = 0;
    hashTable->l = 0;
    hashTable->p = 0;
    return hashTable;
}

void freeHashTable(HashTable *hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        Cliente *cliente = hashTable->table[i];
        while (cliente) {
            Cliente *temp = cliente;
            cliente = cliente->next;
            free(temp);
        }
    }
    free(hashTable->table);
    free(hashTable);
}

unsigned int hash(int key, int size, int l) {
    return key % (size * (1 << l));
}

void insertCliente(HashTable *hashTable, int cod_cliente, char *nome) {
    if ((float)hashTable->count / hashTable->size > LOAD_FACTOR_THRESHOLD) {
        resizeHashTable(hashTable);
    }

    unsigned int index = hash(cod_cliente, hashTable->size, hashTable->l);
    Cliente *newCliente = (Cliente *)malloc(sizeof(Cliente));
    newCliente->cod_cliente = cod_cliente;
    strcpy(newCliente->nome, nome);
    newCliente->next = hashTable->table[index];
    hashTable->table[index] = newCliente;
    hashTable->count++;
}

Cliente *searchCliente(HashTable *hashTable, int cod_cliente) {
    unsigned int index = hash(cod_cliente, hashTable->size, hashTable->l);
    Cliente *cliente = hashTable->table[index];
    while (cliente) {
        if (cliente->cod_cliente == cod_cliente) {
            return cliente;
        }
        cliente = cliente->next;
    }
    return NULL;
}

void removeCliente(HashTable *hashTable, int cod_cliente) {
    unsigned int index = hash(cod_cliente, hashTable->size, hashTable->l);
    Cliente *cliente = hashTable->table[index];
    Cliente *prev = NULL;
    while (cliente) {
        if (cliente->cod_cliente == cod_cliente) {
            if (prev) {
                prev->next = cliente->next;
            } else {
                hashTable->table[index] = cliente->next;
            }
            free(cliente);
            hashTable->count--;
            return;
        }
        prev = cliente;
        cliente = cliente->next;
    }
}

void resizeHashTable(HashTable *hashTable) {
    int newSize = hashTable->size * 2;
    Cliente **newTable = (Cliente **)malloc(newSize * sizeof(Cliente *));
    for (int i = 0; i < newSize; i++) {
        newTable[i] = NULL;
    }

    for (int i = 0; i < hashTable->size; i++) {
        Cliente *cliente = hashTable->table[i];
        while (cliente) {
            Cliente *next = cliente->next;
            unsigned int index = hash(cliente->cod_cliente, newSize, hashTable->l + 1);
            cliente->next = newTable[index];
            newTable[index] = cliente;
            cliente = next;
        }
    }

    free(hashTable->table);
    hashTable->table = newTable;
    hashTable->size = newSize;
    hashTable->l++;
}