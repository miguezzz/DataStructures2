#ifndef AGENCIA_H
#define AGENCIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_REGISTROS 6
#define LOAD_FACTOR_THRESHOLD 0.75

typedef struct cliente {
    int cod_cliente;
    char nome[100];
    struct cliente *next;
} Cliente;

typedef struct {
    Cliente **table;
    int size;
    int count;
    int l;
    int p;
} HashTable;

HashTable *createHashTable(int size);
void freeHashTable(HashTable *hashTable);
unsigned int hash(int key, int size, int l);
void insertCliente(HashTable *hashTable, int cod_cliente, char *nome);
Cliente *searchCliente(HashTable *hashTable, int cod_cliente);
void removeCliente(HashTable *hashTable, int cod_cliente);
void resizeHashTable(HashTable *hashTable);

#endif