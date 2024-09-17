#include "clientes.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <limits.h>

#define M_REGISTROS 6

// Cria uma conta corrente. Lembrar de usar free();
Cliente *criaCliente(int cod_cliente, char *nome, char *data_nascimento, int congelado) {

    Cliente *c = (Cliente *) malloc(sizeof(Cliente));

    c->cod_cliente = cod_cliente;
    strcpy(c->nome, nome);
    strcpy(c->data_nascimento, data_nascimento);
    c->congelado = congelado;

    return c;
}

// Salva uma conta num arquivo externo
void salvaCliente(Cliente *c, FILE *out) {
    if (fwrite(&c->cod_cliente, sizeof(int), 1, out) < 1) {
        free(c);
        exit(1);
    }
    fwrite(c->nome, sizeof(char), 50, out);
    fwrite(c->data_nascimento, sizeof(char), 20, out);
    fwrite(&c->congelado, sizeof(int), 1, out);
}

// Função para carregar clientes em memória
Cliente *carregaCliente(FILE *in) {
    Cliente *c = (Cliente *) malloc(sizeof(Cliente));
    if (c == NULL) {
        return NULL; // Falha ao alocar memória
    }

    if (fread(&c->cod_cliente, sizeof(int), 1, in) != 1) {
        free(c);
        return NULL; // Falha na leitura do cod_cliente
    }
    if (fread(c->nome, sizeof(char), sizeof(c->nome), in) != sizeof(c->nome)) {
        free(c);
        return NULL; // Falha na leitura do nome
    }
    if (fread(c->data_nascimento, sizeof(char), sizeof(c->data_nascimento), in) != sizeof(c->data_nascimento)) {
        free(c);
        return NULL; // Falha na leitura da data de nascimento
    }

    return c;
}

void leClientes(FILE *in) {
    printf("\n\nLendo funcionários do arquivo...\n\n");
    rewind(in);
    Cliente *c;
    while ((c = carregaCliente(in)) != NULL) {
        imprimeCliente(c);
        free(c);
    }
}

// Função para imprimir os dados do cliente
void imprimeCliente(Cliente *c) {
    
    if (c == NULL) {
        return;
    }

    printf("**********************************************");
    printf("\nCódigo do cliente: %d", c->cod_cliente);
    printf("\nNome do cliente: %s", c->nome);
    printf("\nData de nascimento: %s", c->data_nascimento);
    printf("\n**********************************************\n\n");
}

// Função para encontrar o índice do menor cliente não congelado
// int menor_chave(Registro registros[], int tamanho) {

//     int menor = INT_MAX;
//     int indice = -1;

//     for (int i = 0; i < tamanho; i++) {
//         if (!registros[i].congelado && registros[i].cliente->cod_cliente < menor) {
//             menor = registros[i].cliente->cod_cliente;
//             indice = i;
//         }
//     }
//     return indice;
// }

// Implementação da seleção com substituição
// void selecaoSubst(FILE *in, FILE *out) {

//     Registro registros[M_REGISTROS];
//     int numParticao = 1;

//     // Passo 1: Carrega os primeiros M_REGISTROS clientes para a memória
//     for (int i = 0; i < M_REGISTROS; i++) {
//         Cliente *cliente = carregaCliente(in);
//         if (cliente != NULL) {
//             registros[i].cliente = cliente;
//             registros[i].congelado = 0;
//         } else {
//             registros[i].cliente = NULL;
//             registros[i].congelado = 1; // Marca como congelado se não houver mais clientes
//         }
//     }

//     while (1) {

//         // Passo 2: Selecionar o registro com a menor chave
//         int indiceMenor = menor_chave(registros, M_REGISTROS);
        
//         // Se todos os registros estiverem congelados ou vazios, abre uma nova partição
//         if (indiceMenor == -1) {
//             printf("Iniciando nova partição: %d\n", ++numParticao);
//             for (int i = 0; i < M_REGISTROS; i++) {
//                 registros[i].congelado = 0; // Descongela todos os registros
//             }
//             continue;
//         }

//         // Passo 3: Gravar o cliente com a menor chave no arquivo de saída
//         Cliente *cliente = registros[indiceMenor].cliente;
//         if (cliente != NULL) {
//             imprimeCliente(cliente);
//             // escrever no arquivo de saída (out) o cliente
//             fwrite(cliente, sizeof(Cliente), 1, out);
//         }

//         // Passo 4: Substituir o registro r pelo próximo cliente do arquivo
//         Cliente *proximoCliente = carregaCliente(in);
//         registros[indiceMenor].cliente = proximoCliente;

//         // Passo 5: Congelar o registro se a chave for menor que a última gravada
//         if (proximoCliente != NULL && proximoCliente->cod_cliente < cliente->cod_cliente) {
//             registros[indiceMenor].congelado = 1;
//         }

//         // Passo 6: Verifica se há mais registros não congelados
//         if (menor_chave(registros, M_REGISTROS) == -1 && feof(in)) {
//             // Se todos os registros estiverem congelados e o arquivo de entrada acabou, fim do algoritmo
//             break;
//         }
//     }

//     // Fechamento de arquivos
//     fclose(out);
// }

int tamanho() {
    return sizeof(int) + // conta->cod_cliente
            sizeof(char) * 50 + // conta->nome
            sizeof(char) * 20 + // conta->nasc
            sizeof(int);
}