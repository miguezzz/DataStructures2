#include "clientes.h"

// cria uma tabela hash
HashTable *createHashTable() {

    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->table = (Cliente **)malloc(M_REGISTROS * sizeof(Cliente *));

    for (int i = 0; i < M_REGISTROS; i++) {
        hashTable->table[i] = NULL;
    }

    hashTable->size = M_REGISTROS;
    hashTable->clientCount = 0;
    hashTable->l = 0;
    hashTable->p = 0;

    return hashTable;
}

// imprime a tabela hash
void printHash(HashTable *hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        printf("Index %d: ", i);
        if (hashTable->table[i] != NULL) {
            char filename[20];
            sprintf(filename, "storage_%d.dat", i);
            FILE *file = fopen(filename, "rb");
            if (!file) {
                perror("Failed to open file");
                continue;
            }

            long offset = (long)hashTable->table[i];
            Cliente *cliente = carregaCliente(file, offset);
            while (cliente) {
                printf("%d %s -> ", cliente->cod_cliente, cliente->nome);
                if (cliente->next_offset == -1) {
                    break;
                }
                cliente = carregaCliente(file, cliente->next_offset);
            }
            fclose(file);
        }
        printf("NULL\n");
    }
}

// calcula a função de hash
int hash(int key, int l, int p) {

    int h0 = key % M_REGISTROS;
    if (h0 < p) {
        return key % M_REGISTROS * pow(2, l);
    }
    
    return h0;
}

// insere um cliente na tabela hash
void insertCliente(HashTable *hashTable, int cod_cliente, char *nome) {
    
    int index = hash(cod_cliente, hashTable->l, hashTable->p);
    char filename[20];
    sprintf(filename, "storage_%d.dat", index);

    FILE *file = fopen(filename, "ab+");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    Cliente *newCliente = (Cliente *)malloc(sizeof(Cliente));
    newCliente->cod_cliente = cod_cliente;
    strcpy(newCliente->nome, nome);
    newCliente->next_offset = -1;

    // Write the new client to the file and store the offset
    fseek(file, 0, SEEK_END);
    long offset = ftell(file);
    fwrite(&newCliente->cod_cliente, sizeof(int), 1, file);
    fwrite(newCliente->nome, sizeof(char), 100, file);
    fwrite(&newCliente->next_offset, sizeof(long), 1, file);
    fclose(file);

    // Update the hash table to point to the start of the file if it's the first entry
    if (hashTable->table[index] == NULL) {
        hashTable->table[index] = (Cliente *)offset;
    } else {
        // Update the next_offset of the last client in the list
        file = fopen(filename, "rb+");
        if (!file) {
            perror("Failed to open file");
            exit(EXIT_FAILURE);
        }
        long current_offset = (long)hashTable->table[index];
        Cliente *current = carregaCliente(file, current_offset);
        while (current->next_offset != -1) {
            current_offset = current->next_offset;
            current = carregaCliente(file, current_offset);
        }
        current->next_offset = offset;
        fseek(file, current_offset + sizeof(int) + sizeof(char) * 100, SEEK_SET);
        fwrite(&offset, sizeof(long), 1, file);
        fclose(file);
    }

    free(newCliente);
    hashTable->clientCount++;
}

// Salva um cliente num arquivo externo
void salvaCliente(Cliente *c, FILE *out) {

    Cliente *current = c;
    while (current != NULL) {
        if (fwrite(&current->cod_cliente, sizeof(int), 1, out) < 1) {
            printf("Erro ao escrever no arquivo\n");
            exit(1);
        }
        fwrite(current->nome, sizeof(char), 100, out);
        
        fseek(out, current->next_offset * sizeof(Cliente), SEEK_SET);
        if (fread(current, sizeof(Cliente), 1, out) != 1) {
            break;
        }
    }
}

// busca um cliente na tabela hash
Cliente *searchCliente(HashTable *hashTable, int cod_cliente) {
    
    int index = hash(cod_cliente, hashTable->l, hashTable->p);
    char filename[20];
    sprintf(filename, "storage_%d.dat", index);

    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    int offset = (long)hashTable->table[index];
    Cliente *cliente = carregaCliente(file, offset);

    while (cliente) {
        if (cliente->cod_cliente == cod_cliente) {
            fclose(file);
            return cliente;
        }
        if (cliente->next_offset == -1) {
            break;
        }
        cliente = carregaCliente(file, cliente->next_offset);
    }
    
    fclose(file);
    return NULL;
}

// remove um cliente da tabela hash
void removeCliente(HashTable *hashTable, int cod_cliente) {

    int index = hash(cod_cliente, hashTable->l, hashTable->p);

    char filename[20];
    sprintf(filename, "storage_%d.dat", index);

    FILE *file = fopen(filename, "rb+");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    long offset = (long)hashTable->table[index];
    Cliente *cliente = carregaCliente(file, offset);
    Cliente *prev = NULL; // ponteiro para o cliente anterior

    while (cliente) {
        if (cliente->cod_cliente == cod_cliente) {
            if (prev) {
                prev->next_offset = cliente->next_offset;
                fseek(file, (long)hashTable->table[index] + sizeof(int) + sizeof(char) * 100, SEEK_SET);
                fwrite(&prev->next_offset, sizeof(long), 1, file);
            } else {
                if (cliente->next_offset == -1) {
                    hashTable->table[index] = NULL;
                } else {
                    hashTable->table[index] = (Cliente *)cliente->next_offset;
                }
            }
            free(cliente);
            hashTable->clientCount--;
            fclose(file);
            return;
        }
        prev = cliente;
        offset = cliente->next_offset;
        cliente = carregaCliente(file, offset);
    }

    fclose(file);
}

// expande a tabela hash
void expandTable(HashTable *hashTable) {

    int newSize = hashTable->size + 1;

    Cliente **newTable = (Cliente **)malloc(newSize * sizeof(Cliente *));
    for (int i = 0; i < newSize; i++) {
        newTable[i] = NULL;
    }

    // refaz a hash para os clientes da tabela antiga
    for (int i = 0; i < hashTable->size; i++) {
        if (hashTable->table[i] != NULL) {
            char oldFilename[20];
            sprintf(oldFilename, "storage_%d.dat", i);
            FILE *oldFile = fopen(oldFilename, "rb");
            if (!oldFile) {
                perror("Failed to open old file");
                exit(EXIT_FAILURE);
            }

            long offset;
            while (fread(&offset, sizeof(long), 1, oldFile) == 1) { // lê o offset do cliente
                Cliente *cliente = carregaCliente(oldFile, offset);
                int newIndex = hash(cliente->cod_cliente, hashTable->l, hashTable->p); // calcula o novo índice

                char newFilename[20];
                sprintf(newFilename, "storage_%d.dat", newIndex);
                FILE *newFile = fopen(newFilename, "ab+");
                if (!newFile) {
                    perror("Failed to open new file");
                    exit(EXIT_FAILURE);
                }

                fseek(newFile, 0, SEEK_END); // move o ponteiro para o final do arquivo
                long newOffset = ftell(newFile); // pega o offset do novo cliente

                // escreve o novo cliente no arquivo
                fwrite(&cliente->cod_cliente, sizeof(int), 1, newFile);
                fwrite(cliente->nome, sizeof(char), 100, newFile);
                fwrite(&cliente->next_offset, sizeof(long), 1, newFile);
                fclose(newFile);

                if (newTable[newIndex] == NULL) { // se o novo índice estiver vazio
                    newTable[newIndex] = (Cliente *)newOffset; // apenas aponta para o novo cliente
                } else {
                    FILE *updateFile = fopen(newFilename, "rb+");

                    if (!updateFile) {
                        perror("Failed to open update file");
                        exit(EXIT_FAILURE);
                    }

                    long current_offset = (long)newTable[newIndex];
                    Cliente *current = carregaCliente(updateFile, current_offset);
                    while (current->next_offset != -1) {
                        current_offset = current->next_offset;
                        current = carregaCliente(updateFile, current_offset);
                    }
                    current->next_offset = newOffset;
                    fseek(updateFile, current_offset + sizeof(int) + sizeof(char) * 100, SEEK_SET);
                    fwrite(&newOffset, sizeof(long), 1, updateFile);
                    fclose(updateFile);
                }

                free(cliente);
            }

            fclose(oldFile);
        }
    }

    free(hashTable->table);
    hashTable->table = newTable;
    hashTable->size = newSize;

    // Atualiza os parâmetros l e p
    if (newSize == pow(2, hashTable->l + 1) * M_REGISTROS) {
        hashTable->l++;
        hashTable->p = 0;
    } else {
        hashTable->p++;
    }
}

// Função para carregar clientes em memória
Cliente *carregaCliente(FILE *in, long offset) {

    fseek(in, offset, SEEK_SET);

    Cliente *c = (Cliente *)malloc(sizeof(Cliente));
    if (c == NULL) {
        return NULL; // falha ao alocar memória
    }

    if (fread(&c->cod_cliente, sizeof(int), 1, in) != 1) {
        free(c);
        return NULL; // falha na leitura do cod_cliente
    }

    fread(c->nome, sizeof(char), 100, in);
    fread(&c->next_offset, sizeof(long), 1, in);

    return c;
}

// Função para imprimir os dados do cliente
void imprimeCliente(Cliente *c) {
    
    if (c == NULL) {
        return;
    }

    printf("**********************************************");
    printf("\nCódigo do cliente: %d", c->cod_cliente);
    printf("\nNome do cliente: %s", c->nome);
    printf("\nPróximo offset: %ld", c->next_offset);
    printf("\n**********************************************\n\n");
}