#include "clientes.h"

int main (void) {

    Cliente clientes[53] = {
        {29, "João da Silva", "01/01/1990"},
        {14, "Maria dos Santos", "02/02/1985"},
        {76, "José Oliveira", "03/03/1970"},
        {75, "Ana Paula", "04/04/1995"},
        {59, "Pedro Henrique", "05/05/1980"},
        {6, "Luiza Fernandes", "06/06/1992"},
        {7, "Ricardo Martins", "07/07/1975"},
        {74, "Beatriz Souza", "08/08/1998"},
        {48, "Carlos Alberto", "09/09/1965"},
        {46, "Juliana Pereira", "10/10/1990"},
        {10, "Marcos Vinicius", "11/11/1982"},
        {18, "Leticia Costa", "12/12/1997"},
        {56, "Rafael Silva", "13/01/1988"},
        {20, "Gabriela Oliveira", "14/02/1993"},
        {26, "Thiago Mendes", "15/03/1985"},
        {4, "Camila Rodrigues", "16/04/1991"},
        {21, "Lucas Ferreira", "17/05/1989"},
        {65, "Aline Santos", "18/06/1994"},
        {22, "Felipe Nunes", "19/07/1986"},
        {49, "Isabella Lima", "20/08/1996"},
        {11, "Sofia Rodrigues", "21/09/1999"},
        {16, "Mateus Silva", "22/10/1987"},
        {8, "Laura Oliveira", "23/11/1996"},
        {15, "Gustavo Santos", "24/12/1983"},
        {5, "Isabel Costa", "25/01/1992"},
        {19, "Rafaela Martins", "26/02/1989"},
        {50, "Pedro Paulo", "27/03/1995"},
        {55, "Ana Luiza", "28/04/1986"},
        {25, "João Pedro", "29/05/1998"},
        {66, "Beatriz Lima", "02/06/1984"},
        {57, "Luiz Felipe", "03/07/1993"},
        {77, "Gabriela Souza", "04/08/1988"},
        {12, "Ricardo Nunes", "05/09/1997"},
        {30, "Aline Ferreira", "12/10/1985"},
        {17, "Thiago Rodrigues", "14/11/1994"},
        {9, "Camila Silva", "13/12/1982"},
        {54, "Juliana Oliveira", "18/01/1991"},
        {78, "Marcos Santos", "21/02/1987"},
        {43, "Leticia Costa", "15/03/1996"},
        {38, "Felipe Martins", "16/04/1989"},
        {51, "Isabella Souza", "19/05/1998"},
        {32, "Rafael Lima", "12/06/1986"},
        {58, "Ana Paula", "05/07/1995"},
        {13, "João da Silva", "30/08/1984"},
        {73, "Beatriz Nunes", "10/09/1993"},
        {79, "Luiz Felipe", "11/10/1988"},
        {27, "Gabriela Ferreira", "22/11/1997"},
        {1, "Ricardo Rodrigues", "09/12/1985"},
        {3, "Aline Santos", "02/01/1992"},
        {60, "Thiago Silva", "19/02/1989"},
        {36, "Camila Oliveira", "06/03/1996"},
        {47, "Juliana Martins", "25/04/1987"},
        {31, "Marcos Souza", "24/05/1995"}
    };

    FILE *arquivo = fopen("clientes.dat", "w+b");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return 1;
    }

    if (fwrite(clientes, sizeof(Cliente), 53, arquivo) != 53) {
        printf("Erro ao escrever os dados no arquivo!\n");
        fclose(arquivo);
        return 1;
    }
    
    rewind(arquivo);
    carrega_m_clientes(arquivo);

    fclose(arquivo);

    return 0;
}

int main() {
    FILE *entrada = fopen("clientes.dat", "rb");
    if (!entrada) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    FILE *saida = fopen("particao_1.dat", "wb");
    if (!saida) {
        printf("Erro ao criar o arquivo de saída.\n");
        fclose(entrada);
        return 1;
    }

    selecaoSubst(entrada, saida);

    fclose(entrada);
    return 0;
}