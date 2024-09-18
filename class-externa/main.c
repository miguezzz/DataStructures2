#include "clientes.h"

int main (void) {

    Cliente *c1 = criaCliente(29, "João da Silva", "01/01/1990");
    Cliente *c2 = criaCliente(14, "Maria dos Santos", "02/02/1985");
    Cliente *c3 = criaCliente(76, "José Oliveira", "03/03/1970");
    Cliente *c4 = criaCliente(75, "Ana Paula", "04/04/1995");
    Cliente *c5 = criaCliente(59, "Pedro Henrique", "05/05/1980");
    Cliente *c6 = criaCliente(6, "Luiza Fernandes", "06/06/1992");
    Cliente *c7 = criaCliente(7, "Ricardo Martins", "07/07/1975");
    Cliente *c8 = criaCliente(74, "Beatriz Souza", "08/08/1998");
    Cliente *c9 = criaCliente(48, "Carlos Alberto", "09/09/1965");
    Cliente *c10 = criaCliente(46, "Juliana Pereira", "10/10/1990");
    Cliente *c11 = criaCliente(10, "Marcos Vinicius", "11/11/1982");
    Cliente *c12 = criaCliente(18, "Leticia Costa", "12/12/1997");
    Cliente *c13 = criaCliente(56, "Rafael Silva", "13/01/1988");
    Cliente *c14 = criaCliente(20, "Gabriela Oliveira", "14/02/1993");
    Cliente *c15 = criaCliente(26, "Thiago Mendes", "15/03/1985");
    Cliente *c16 = criaCliente(4, "Camila Rodrigues", "16/04/1991");
    Cliente *c17 = criaCliente(21, "Lucas Ferreira", "17/05/1989");
    Cliente *c18 = criaCliente(65, "Aline Santos", "18/06/1994");
    Cliente *c19 = criaCliente(22, "Felipe Nunes", "19/07/1986");
    Cliente *c20 = criaCliente(49, "Isabella Lima", "20/08/1996");
    Cliente *c21 = criaCliente(11, "Sofia Rodrigues", "21/09/1999");
    Cliente *c22 = criaCliente(16, "Mateus Silva", "22/10/1987");
    Cliente *c23 = criaCliente(8, "Laura Oliveira", "23/11/1996");
    Cliente *c24 = criaCliente(15, "Gustavo Santos", "24/12/1983");
    Cliente *c25 = criaCliente(5, "Isabel Costa", "25/01/1992");
    Cliente *c26 = criaCliente(19, "Rafaela Martins", "26/02/1989");
    Cliente *c27 = criaCliente(50, "Pedro Paulo", "27/03/1995");
    Cliente *c28 = criaCliente(55, "Ana Luiza", "28/04/1986");
    Cliente *c29 = criaCliente(25, "João Pedro", "29/05/1998");
    Cliente *c30 = criaCliente(66, "Beatriz Lima", "02/06/1984");
    Cliente *c31 = criaCliente(57, "Luiz Felipe", "03/07/1993");
    Cliente *c32 = criaCliente(77, "Gabriela Souza", "04/08/1988");
    Cliente *c33 = criaCliente(12, "Ricardo Nunes", "05/09/1997");
    Cliente *c34 = criaCliente(30, "Aline Ferreira", "12/10/1985");
    Cliente *c35 = criaCliente(17, "Thiago Rodrigues", "14/11/1994");
    Cliente *c36 = criaCliente(9, "Camila Silva", "13/12/1982");
    Cliente *c37 = criaCliente(54, "Juliana Oliveira", "18/01/1991");
    Cliente *c38 = criaCliente(78, "Marcos Santos", "21/02/1987");
    Cliente *c39 = criaCliente(43, "Leticia Costa", "15/03/1996");
    Cliente *c40 = criaCliente(38, "Felipe Martins", "16/04/1989");
    Cliente *c41 = criaCliente(51, "Isabella Souza", "19/05/1998");
    Cliente *c42 = criaCliente(32, "Rafael Lima", "12/06/1986");
    Cliente *c43 = criaCliente(58, "Ana Paula", "05/07/1995");
    Cliente *c44 = criaCliente(13, "João da Silva", "30/08/1984");
    Cliente *c45 = criaCliente(73, "Beatriz Nunes", "10/09/1993");
    Cliente *c46 = criaCliente(79, "Luiz Felipe", "11/10/1988");
    Cliente *c47 = criaCliente(27, "Gabriela Ferreira", "22/11/1997");
    Cliente *c48 = criaCliente(1, "Ricardo Rodrigues", "09/12/1985");
    Cliente *c49 = criaCliente(3, "Aline Santos", "02/01/1992");
    Cliente *c50 = criaCliente(60, "Thiago Silva", "19/02/1989");
    Cliente *c51 = criaCliente(36, "Camila Oliveira", "06/03/1996");
    Cliente *c52 = criaCliente(47, "Juliana Martins", "25/04/1987");
    Cliente *c53 = criaCliente(31, "Marcos Souza", "24/05/1995");


    FILE *arquivo = fopen("clientes.dat", "w+b");

    salvaCliente(c1, arquivo);
    free(c1);

    salvaCliente(c2, arquivo);
    free(c2);

    salvaCliente(c3, arquivo);
    free(c3);

    salvaCliente(c4, arquivo);
    free(c4);

    salvaCliente(c5, arquivo);
    free(c5);

    salvaCliente(c6, arquivo);
    free(c6);

    salvaCliente(c7, arquivo);
    free(c7);

    salvaCliente(c8, arquivo);
    free(c8);

    salvaCliente(c9, arquivo);
    free(c9);

    salvaCliente(c10, arquivo);
    free(c10);

    salvaCliente(c11, arquivo);
    free(c11);

    salvaCliente(c12, arquivo);
    free(c12);

    salvaCliente(c13, arquivo);
    free(c13);

    salvaCliente(c14, arquivo);
    free(c14);

    salvaCliente(c15, arquivo);
    free(c15);

    salvaCliente(c16, arquivo);
    free(c16);

    salvaCliente(c17, arquivo);
    free(c17);

    salvaCliente(c18, arquivo);
    free(c18);

    salvaCliente(c19, arquivo);
    free(c19);

    salvaCliente(c20, arquivo);
    free(c20);

    salvaCliente(c21, arquivo);
    free(c21);

    salvaCliente(c22, arquivo);
    free(c22);

    salvaCliente(c23, arquivo);
    free(c23);

    salvaCliente(c24, arquivo);
    free(c24);

    salvaCliente(c25, arquivo);
    free(c25);

    salvaCliente(c26, arquivo);
    free(c26);

    salvaCliente(c27, arquivo);
    free(c27);

    salvaCliente(c28, arquivo);
    free(c28);

    salvaCliente(c29, arquivo);
    free(c29);

    salvaCliente(c30, arquivo);
    free(c30);

    salvaCliente(c31, arquivo);
    free(c31);

    salvaCliente(c32, arquivo);
    free(c32);

    salvaCliente(c33, arquivo);
    free(c33);

    salvaCliente(c34, arquivo);
    free(c34);

    salvaCliente(c35, arquivo);
    free(c35);

    salvaCliente(c36, arquivo);
    free(c36);

    salvaCliente(c37, arquivo);
    free(c37);

    salvaCliente(c38, arquivo);
    free(c38);

    salvaCliente(c39, arquivo);
    free(c39);

    salvaCliente(c40, arquivo);
    free(c40);

    salvaCliente(c41, arquivo);
    free(c41);

    salvaCliente(c42, arquivo);
    free(c42);

    salvaCliente(c43, arquivo);
    free(c43);

    salvaCliente(c44, arquivo);
    free(c44);

    salvaCliente(c45, arquivo);
    free(c45);

    salvaCliente(c46, arquivo);
    free(c46);

    salvaCliente(c47, arquivo);
    free(c47);

    salvaCliente(c48, arquivo);
    free(c48);

    salvaCliente(c49, arquivo);
    free(c49);

    salvaCliente(c50, arquivo);
    free(c50);

    salvaCliente(c51, arquivo);
    free(c51);

    salvaCliente(c52, arquivo);
    free(c52);

    salvaCliente(c53, arquivo);
    free(c53);


    fclose(arquivo);

    FILE *entrada = fopen("clientes.dat", "rb");
    if (entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

//    rewind(entrada);

//     Cliente *primeiro = carregaCliente(entrada);
//     imprimeCliente(primeiro);
//     free(primeiro);

//     //fseek(entrada, tamanho(), SEEK_SET);
//     Cliente *segundo = carregaCliente(entrada);
//     if (segundo != NULL) {
//         imprimeCliente(segundo);
//         free(segundo);
//     }

//    // fseek(entrada, tamanho() * 2, SEEK_SET);
//     Cliente *terceiro = carregaCliente(entrada);
//     if (terceiro != NULL) {
//         imprimeCliente(terceiro);
//         free(terceiro);
//     }

    leClientes(entrada);

    // selecaoSubst(entrada, saida);

    fclose(entrada);

    return 0;
}