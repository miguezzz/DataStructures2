#ifndef AGENCIA_H
#define AGENCIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define M_REGISTROS 7
#define LOAD_FACTOR 1

typedef struct cliente {
    int cod_cliente;
    char nome[100];
    long next_offset; // Offset do próximo cliente no arquivo
    // Cliente *next; // Ponteiro para o próximo cliente na memória
} Cliente;

typedef struct {
    Cliente **table; // array de ponteiros para clientes
    int size; // tamanho da tabela
    int clientCount; // quantidade de clientes
    int l; // vezes expandidas
    int p; // compartimento atual para expansão
} HashTable;

HashTable *createHashTable();
void printHash(HashTable *hashTable);
int hash(int key, int l, int p);
void insertCliente(HashTable *hashTable, int cod_cliente, char *nome);
void salvaCliente(Cliente *c, FILE *out);
Cliente *searchCliente(HashTable *hashTable, int cod_cliente);
void removeCliente(HashTable *hashTable, int cod_cliente);
void expandTable(HashTable *hashTable);
Cliente *carregaCliente(FILE *in, long offset);
void imprimeCliente(Cliente *c);

#endif