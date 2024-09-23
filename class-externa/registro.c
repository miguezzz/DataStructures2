#include "registro.h"
#include "clientes.h"

// void leRegistros(FILE *in) {

//     printf("\n\nLendo registros do arquivo...\n\n");
//     //rewind(in);
//     int contador = 0;
//     Registro *r;
//     while ((r = carregaRegistro(in)) != NULL) {
//         printf("%d\n", ++contador);
//         imprimeRegistro(r);
//         free(r);
//     }
// }

// Função para encontrar o índice do menor cliente não congelado
int menorChave(Registro registros[], int tamanho) {

    int menor = INT_MAX; // tem um numero gigante definido. usamos como base pra achar numeros menores
    int indice = -1;

    for (int i = 0; i < tamanho; i++) {
        // se o registro não estiver congelado e seu cod_cliente for menor do que o menor número atual,
        if (!registros[i].congelado && registros[i].cliente->cod_cliente < menor) {
            // menor cod_cliente vira o cod_cliente atual
            menor = registros[i].cliente->cod_cliente;
            // e o indice a ser retornado vira o atual
            indice = i;
        }
    }
    return indice;
}

// preenche M registros no vetor
void preencheVetor(FILE *in, Registro registros[], int tamanho) {

    for (int i = 0; i < tamanho; i++) {
        registros[i].cliente = carregaCliente(in);
        registros[i].congelado = 0;
        
        // imprimeCliente(registros[i].cliente);
    }

    printf("Vetor preenchido com %d registros\n", tamanho);
}

// substitui registro pelo próximo registro do arquivo de clientes. retorna 1 se congelar e 0 caso contrário.
int substituiRegistro(FILE *in, Registro registro[], int indice_menor) {

    int cod_antigo = registro[indice_menor].cliente->cod_cliente;

    registro[indice_menor].cliente = carregaCliente(in);

    if (registro[indice_menor].cliente == NULL) {
        printf("\nFim do arquivo de entrada!\n");
        return 2;
    }
    
    if (registro[indice_menor].cliente->cod_cliente < cod_antigo) {
        registro[indice_menor].congelado = 1;
        return 1;
    } else {
        registro[indice_menor].congelado = 0;
        return 0;
    }
}

// algoritmo de classificação utilizando seleção por substituição.
void selecaoSubst(FILE *in, Registro registros[], FILE *out) {

    int desvioDeRota = 0;
    int congelados = 0;
    while (congelados < M_REGISTROS) {

        if (desvioDeRota == 0) {

            // calcula a menor chave dentre os registros no vetor
            int indice_menor_chave = menorChave(registros, M_REGISTROS);
            printf("menor chave é %d\n", registros[indice_menor_chave].cliente->cod_cliente);

            salvaCliente(registros[indice_menor_chave].cliente, out);

            int congelou = substituiRegistro(in, registros, indice_menor_chave);
            congelados += congelou;
            
            // verifica o fim do arquivo de entrada e para de tentar substituir caso tenha acabado
            if (congelou == 2) {
                desvioDeRota = 1;
            }

        } else {

            for (int i = 0; i < M_REGISTROS; i++) {
                // calcula a menor chave dentre os registros no vetor
                int indice_menor_chave = menorChave(registros, M_REGISTROS);
                // printf("menor chave é %d", registros[indice_menor_chave].cliente->cod_cliente);

                salvaCliente(registros[indice_menor_chave].cliente, out);
            }

            // encerra o ciclo
            break;
        }
    }
}

// descongela todos os registros para a próxima partição da seleção.
void descongelaRegistros(Registro registros[]) {
    for (int i = 0; i < M_REGISTROS; i++) {
        registros[i].congelado = 0;
    }
}

FILE *criaParticao(int particaoAtual) {
    
    FILE *particao;

    char filename[20];
    sprintf(filename, "part%d.dat", particaoAtual);
    particao = fopen(filename, "w+b");

    return particao;
}