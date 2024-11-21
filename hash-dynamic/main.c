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
    insertCliente(hashTable, 7, "<Carlos>");

    printHash(hashTable);

    insertCliente(hashTable, 8, "<Jorge>");
    insertCliente(hashTable, 14, "<Carol>");
    // insertCliente(hashTable, 15, "<Pedro>");

    // abre os arquivos de armazenamento
    // FILE *storage0 = fopen("storage_0.dat", "rb");
    // FILE *storage1 = fopen("storage_1.dat", "rb");
    // FILE *storage2 = fopen("storage_2.dat", "rb");
    // FILE *storage3 = fopen("storage_3.dat", "rb");
    // FILE *storage4 = fopen("storage_4.dat", "rb");
    // FILE *storage5 = fopen("storage_5.dat", "rb");
    // FILE *storage6 = fopen("storage_6.dat", "rb");

    // exibe a tabela hash
    printf("Clientes na tabela hash:\n");

    // removeCliente(hashTable, 3);

    printHash(hashTable);

    // // busca por um cliente específico
    // int cod_cliente = 3;
    // Cliente *cliente = searchCliente(hashTable, cod_cliente);
    // if (cliente) {
    //     printf("\nCliente encontrado: %s (Código: %d)\n", cliente->nome, cliente->cod_cliente);
    //     free(cliente);
    // } else {
    //     printf("\nCliente com código %d não encontrado\n", cod_cliente);
    // }

    // // remove um cliente
    // printf("\nRemovendo cliente com código %d...\n", cod_cliente);
    // removeCliente(hashTable, cod_cliente);

    // // exibe todos os clientes na tabela hash após a remoção
    // printf("\nClientes na tabela hash após a remoção:\n");
    // printHash(hashTable);

    return 0;
}