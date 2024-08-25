#include <stdio.h>
#include <stdlib.h>
#include "contac.h"
#include "agencia.h"

int main(int argc, char** argv) {
    //declara ponteiro para arquivo
    FILE *out;
    //abre arquivo
    if ((out = fopen("agencia.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {
        Agencia *ag = nova_ag(696969, "Agencia Vmigu", "Tangas");
        salva_ag(ag, out);
        imprime_ag(ag);
        free(ag);
        //fecha arquivo
        fclose(out);    
    }
}