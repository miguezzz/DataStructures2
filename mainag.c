#include <stdio.h>
#include <stdlib.h>
#include "contac.h"
#include "agencia.h"

int main(int argc, char** argv) {
    
    // else {
    //     Agencia *ag = nova_ag(696969, "Agencia Vmigu", "Tangas");
    //     salva_ag(ag, out);
    //     imprime_ag(ag);
    //     free(ag);
    //     //fecha arquivo
    //     fclose(out);    
    // }
    int continuar = 1;
    do {
        printf("O que deseja fazer?\n");

        int op;
        printf("\n1 - Cadastrar agência |\n2 - Ler Agência |\n3 - Mostrar todas as agências |\n4 - Excluir Agência |\n0 - Sair |\n");
        scanf("%d", &op);
        if (op == 0) {continuar = 0;}
        switch (op) {
            case 1:
                //declara ponteiro para arquivo
                FILE *out;
                // tenta abrir/criaar o arquivo e encerra se nao funcionar
                if ((out = fopen("agencias.dat", "a+b")) == NULL) {
                printf("Erro ao abrir arquivo\n");
                exit(1);
                }

                char continuar_adicionando = 'n';
                do {
                    printf("\nDigite o código da agência: ");
                    int cod;
                    scanf("%d", &cod);
                    // limpeza de buffer
                    getchar();                
                    
                    printf("Digite o nome da agência: ");
                    char nome_ag[50];
                    fgets(nome_ag, sizeof(nome_ag), stdin);
                    nome_ag[strcspn(nome_ag, "\n")] = '\0';  // Remove o caractere de nova linha

                    printf("Digite o nome do gerente: ");
                    char gerente[50];
                    fgets(gerente, sizeof(gerente), stdin);
                    nome_ag[strcspn(nome_ag, "\n")] = '\0';  // Remove o caractere de nova linha

                    Agencia *ag = (Agencia *) malloc(sizeof(Agencia));
                    ag = nova_ag(cod, nome_ag, gerente);
                    salva_ag(ag, out);
                    printf("Agência criada com sucesso: \n");
                    imprime_ag(ag);

                    free(ag);
                    fclose(out);

                    printf("\n\nDeseja adicionar mais uma agência? [Y/n]: ");
                    char sim_nao;
                    scanf("%c", &sim_nao);
                    continuar_adicionando = sim_nao;
                } while (continuar_adicionando != 'n');
                
                break;

            case 2:

                break;

            case 3:
                FILE *in;
                in = fopen("agencias.dat", "rb");

                printf("Listagem de todas as agências:\n");
                rewind(in);

                le_todas_ag(in);
            
                break;

            case 4:

                break;
      
        }
    }
    while (continuar != 0);

    printf("Encerrando...");
    return 0;
}