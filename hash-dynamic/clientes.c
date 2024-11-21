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
                perror("Erro ao abrir arquivo");
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
    if (h0 < p) { // algoritmo (ultimo slide de acesso direto)
        return key % (int)(M_REGISTROS * pow(2, l));
    }
    
    return h0;
}

// insere um cliente na tabela hash
void insertCliente(HashTable *hashTable, int cod_cliente, char *nome) {
    
    int index = hash(cod_cliente, hashTable->l, hashTable->p); // calcula o índice do novo cliente

    if(hashTable->clientCount / hashTable->size >= LOAD_FACTOR) {
        printf("vai ter que expandir. clientCount = %d\n", hashTable->clientCount);
        expandTable(hashTable);
        index = hash(cod_cliente, hashTable->l, hashTable->p); // recalcula index depois da expansão
    }

    char filename[20];
    sprintf(filename, "storage_%d.dat", index); // nome do arquivo para o compartimento (de acordo com a hash)

    FILE *file = fopen(filename, "ab+");
    if (!file) {
        perror("Erro ao abrir arquivo");
        exit(1);
    }

    // aloca memória para o novo cliente e preenche os campos com os argumentos
    Cliente *newCliente = (Cliente *)malloc(sizeof(Cliente));
    newCliente->cod_cliente = cod_cliente;
    strcpy(newCliente->nome, nome);
    newCliente->next_offset = -1;

    fseek(file, 0, SEEK_END); // move o ponteiro para o final do arquivo
    long offset = ftell(file); // calcula a posição inicial do novo cliente (que também é o final atual do arquivo)
    // escreve o novo cliente no arquivo com os campos cod_cliente, nome e next_offset
    fwrite(&newCliente->cod_cliente, sizeof(int), 1, file);
    fwrite(newCliente->nome, sizeof(char), 100, file);
    fwrite(&newCliente->next_offset, sizeof(long), 1, file);
    fclose(file); // fecha o arquivo

    if (hashTable->table[index] == NULL) { // se o compartimento estiver vazio
        hashTable->table[index] = (Cliente *)offset; // apenas aponta para o novo cliente
    } else { // se colidir
        
        file = fopen(filename, "rb+"); // abre o arquivo para atualização de ponteiros
        if (!file) {
            perror("Falha ao abrir arquivo");
            exit(1);
        }

        long current_offset = (long)hashTable->table[index]; // pega o offset do primeiro cliente para iniciar a busca pelo final antigo e atualizar o ponteiro para o próximo cliente
        Cliente *current = carregaCliente(file, current_offset);
        while (current->next_offset != -1) { // enquanto houver clientes no compartimento
            current_offset = current->next_offset; // pega o offset do próximo cliente
            current = carregaCliente(file, current_offset); // e carrega o próximo cliente
        }
        // quando chegar ao antigo final do arquivo, atualiza o ponteiro para o próximo cliente
        current->next_offset = offset; // aponta o último cliente para o novo cliente
        fseek(file, current_offset + sizeof(int) + sizeof(char) * 100, SEEK_SET); // move o ponteiro para o final do último cliente (antes do next_offset)
        fwrite(&offset, sizeof(long), 1, file); // escreve o novo offset
        fclose(file); // fecha o arquivo
    }

    free(newCliente); // libera a memória alocada para o novo cliente
    hashTable->clientCount++; // incrementa a quantidade de clientes na tabela para gerência de expansão (load factor)
}

// expande a tabela hash
void expandTable(HashTable *hashTable) {

    int newSize = hashTable->size + 1; // novo tamanho da tabela

    Cliente **newTable = (Cliente **)malloc(newSize * sizeof(Cliente *)); // aloca memória para a nova tabela com tamanho atualizado

    for (int i = 0; i < newSize; i++) { // inicializa a nova tabela com NULL
        newTable[i] = NULL;
    }

    // refaz a hash para os clientes da tabela antiga
    for (int i = 0; i < hashTable->size; i++) { // para cada compartimento da tabela antiga
        if (hashTable->table[i] != NULL) { // se for nulo não há clientes nesse compartimento
            
            char oldFilename[20]; // nome do arquivo do compartimento antigo
            sprintf(oldFilename, "storage_%d.dat", i);
            FILE *oldFile = fopen(oldFilename, "rb");

            if (!oldFile) {
                perror("Erro ao abrir arquivo");
                exit(1);
            }

            long current_offset = (long)hashTable->table[i]; // pega o offset do primeiro cliente do compartimento

            Cliente *current_cliente = carregaCliente(oldFile, current_offset); // carrega o primeiro cliente; lembrar de carregar o próximo cliente com o next_offset dentro do loop

            int flag = 0;

            do { // enquanto houver clientes no compartimento
                
                if (current_cliente->next_offset == -1) { // se não houver mais clientes no compartimento
                    flag = -1;
                }

                printf("lendo compartimento %d; cliente %d\n", i, current_cliente->cod_cliente);

                int newIndex = hash(current_cliente->cod_cliente, ((hashTable->l) + 1), (hashTable->p) + 1); // calcula o novo índice
                printf("novo índice para cód %d: %d\n", current_cliente->cod_cliente, newIndex);

                char newFilename[20]; // nome do arquivo do novo compartimento (de acordo com a hash)
                sprintf(newFilename, "storage_%d.dat", newIndex);
                FILE *newFile = fopen(newFilename, "ab+");
                
                if (!newFile) {
                    perror("Erro ao abrir arquivo");
                    exit(1);
                }

                fseek(newFile, 0, SEEK_END); // move o ponteiro para o final do arquivo
                long newOffset = ftell(newFile); // pega o offset do novo cliente

                // criando uma cópia para nao alterar os valores de current_cliente
                Cliente *copia = (Cliente *)malloc(sizeof(Cliente));
                // Copia os valores dos campos da estrutura original para a nova estrutura
                copia->cod_cliente = current_cliente->cod_cliente;
                strcpy(copia->nome, current_cliente->nome);
                copia->next_offset = -1;

                // escreve o novo cliente no arquivo
                fwrite(&copia->cod_cliente, sizeof(int), 1, newFile);
                fwrite(copia->nome, sizeof(char), 100, newFile);
                copia->next_offset = -1; // reseta o next_offset para o novo cliente pois será calculado no próximo loop
                fwrite(&copia->next_offset, sizeof(long), 1, newFile);
                fclose(newFile);

                if (newTable[newIndex] == NULL) { // se o novo índice estiver vazio
                    newTable[newIndex] = (Cliente *)newOffset; // apenas aponta para o novo cliente
                    printf("Compartimento vazio. Aponta para o novo Cliente\n");
                } else {
                    printf("Entrei no else. tinha gente no index %d!\n", i);
                    
                    FILE *updateFile = fopen(newFilename, "rb+"); // abre arquivo para atualização de ponteiros next_offset

                    if (!updateFile) {
                        perror("Erro ao abrir arquivo");
                        exit(1);
                    }

                    long current_offset_loop = (long)newTable[newIndex]; // pega o offset do primeiro cliente do novo compartimento
                    Cliente *current = carregaCliente(updateFile, current_offset_loop); // carrega o primeiro cliente
                    while (current->next_offset != -1) { // enquanto houver clientes no compartimento
                        current_offset_loop = current->next_offset; // pega o offset do próximo cliente
                        current = carregaCliente(updateFile, current_offset_loop); // carrega o próximo cliente
                    }
                    current->next_offset = newOffset; // aponta o último cliente para o novo cliente
                    fseek(updateFile, current_offset_loop + sizeof(int) + sizeof(char) * 100, SEEK_SET); // move o ponteiro para o final do último cliente (antes do next_offset)
                    fwrite(&newOffset, sizeof(long), 1, updateFile); // escreve o novo offset
                    fclose(updateFile); // fecha o arquivo
                }

                printf("testando offset: %ld, next: %ld\n", current_offset, current_cliente->next_offset);

                // carrega novo cliente
                current_offset = current_cliente->next_offset; // pega o offset do próximo cliente
                printf("next_offset oficial: %ld\n", current_offset);
                current_cliente = carregaCliente(oldFile, current_offset); // carrega o próximo cliente
            } while (flag != -1); // enquanto houver clientes no compartimento

            fclose(oldFile);
        }

        printf("Cheguei no final do compartimento %d\n", i);
    }

    free(hashTable->table); // libera a memória da tabela antiga
    hashTable->table = newTable; // atualiza a tabela para a que foi criada
    hashTable->size = newSize; // atualiza o tamanho da tabela

    // Atualiza os parâmetros l e p
    if (newSize == pow(2, hashTable->l + 1) * M_REGISTROS) {
        hashTable->l++;
        hashTable->p = 0;
    } else {
        printf("atualizei o p\n");
        hashTable->p++;
    }
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

    long offset = (long)hashTable->table[index]; // busca a posição inicial do cliente
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