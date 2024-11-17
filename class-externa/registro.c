#include "registro.h"
#include "clientes.h"

// Função para encontrar o índice do menor cliente não congelado
int menorChave(Registro registros[], int tamanho) {

    int menor = INT_MAX; // tem um numero gigante definido. usamos como base pra achar numeros menores
    int indice = -1;

    for (int i = 0; i < tamanho; i++) {
        // se o registro não for nulo, não estiver congelado e seu cod_cliente for menor do que o menor número atual,
        if (registros[i].cliente!=NULL && !registros[i].congelado && registros[i].cliente->cod_cliente < menor) {
            // menor cod_cliente vira o cod_cliente atual
            menor = registros[i].cliente->cod_cliente;
            // e o indice a ser retornado vira o atual
            indice = i;
        }
    }
    return indice;
}

// preenche com os primeiros M registros no vetor
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
    
    
    // salva o cod_cliente do registro atual
    int cod_antigo = registro[indice_menor].cliente->cod_cliente;

    registro[indice_menor].cliente = carregaCliente(in);

    // se o proximo cliente for null, fim do arquivo! retorna 2.
    if (registro[indice_menor].cliente == NULL) {
        // printf("\nFim do arquivo de entrada!\n");
        return 2;
    }
    
    // se o cod do proximo for menor, o registro congela e retorna 1.
    if (registro[indice_menor].cliente->cod_cliente < cod_antigo) {
        registro[indice_menor].congelado = 1;
        return 1;
    } else { // se não for menor, retorna 0.
        registro[indice_menor].congelado = 0;
        return 0;
    }
}

// algoritmo de classificação utilizando seleção por substituição.
void selecaoSubst(FILE *in, Registro registros[], FILE *out) {

    // começamos com 0 congelados. a partição fecha quando tiverem M congelados.
    int congelados = 0;
    while (congelados < M_REGISTROS) {

        // encontra o indice da menor chave dentre os registros no vetor
        int indice_menor_chave = menorChave(registros, M_REGISTROS);
        printf("menor chave é %d\n", registros[indice_menor_chave].cliente->cod_cliente);

        // salva o cliente na partição de saida
        salvaCliente(registros[indice_menor_chave].cliente, out);


        int congelou = substituiRegistro(in, registros, indice_menor_chave);
        congelados += congelou;
        
        // verifica o fim do arquivo de entrada e para de tentar substituir caso tenha acabado. daqui pra baixo só serve pra última partição!
        if (congelou == 2) {
            congelados = 1;

            // se acabou o arquivo de clientes, sobram apenas 6 clientes no registro.
            for (int i = 0; i < M_REGISTROS - 1; i++) {
                // calcula a menor chave dentre os registros no vetor
                int indice_menor_chave = menorChave(registros, M_REGISTROS);
                printf("menor chave é %d\n", registros[indice_menor_chave].cliente->cod_cliente);

                salvaCliente(registros[indice_menor_chave].cliente, out);
                
                // Marca o registro como congelado para evitar leitura repetida
                registros[indice_menor_chave].congelado = 1;
                congelados++;
            }
        }
    }
} 

// descongela todos os registros para a próxima partição da seleção.
void descongelaRegistros(Registro registros[]) {
    for (int i = 0; i < M_REGISTROS; i++) {
        registros[i].congelado = 0;
    }
}

// cria uma partição de saida
FILE *criaParticao(int particaoAtual) {
    
    FILE *particao;

    char filename[20];
    sprintf(filename, "part%d.dat", particaoAtual);
    particao = fopen(filename, "w+b");

    return particao;
}