#include "clientes.h"

int main(void) {
    Cliente *joao = criaCliente(1, "Joao", 21);
    Cliente *maria = criaCliente(2, "Maria", 19);
    Cliente *jose = criaCliente(3, "Jose", 21);
    Cliente *ana = criaCliente(4, "Ana", 77);
    Cliente *pedro = criaCliente(5, "Pedro", 55);
    Cliente *paulo = criaCliente(6, "Paulo", 24);
    Cliente *lucas = criaCliente(7, "Lucas", 21);
    Cliente *marcos = criaCliente(8, "Marcos", 19);
    Cliente *lucia = criaCliente(9, "Lucia", 24);
    Cliente *marta = criaCliente(10, "Marta", 77);

    FILE *clientes = fopen("A1.dat", "w+b");

    salvaCliente(joao, clientes);
    free(joao);

    salvaCliente(maria, clientes);
    free(maria);

    salvaCliente(jose, clientes);
    free(jose);

    salvaCliente(ana, clientes);
    free(ana);

    salvaCliente(pedro, clientes);
    free(pedro);

    salvaCliente(paulo, clientes);
    free(paulo);

    salvaCliente(lucas, clientes);
    free(lucas);

    salvaCliente(marcos, clientes);
    free(marcos);

    salvaCliente(lucia, clientes);
    free(lucia);

    salvaCliente(marta, clientes);
    free(marta);

    fclose(clientes);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////

    FILE *A1 = fopen("A1.dat", "rb");
    rewind(A1);

    leftkowitz(A1);

    printf("Fim do programa.\n");

    fclose(A1);
    
    return 0;
}