#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "candidatos.h"
#include "eleicoes.h"
#include "uf.h"
#include "pessoas.h"
#include "votos.h"

void estados();
void pessoas();
void eleicoes();
void candidatos();
void votos();
void menu();
int main() {
    loadUFs();
    carregar_pessoas();
    carregar_eleicoes();
    carregar_candidatos();
    load_votos();
    int op;
    do {
        menu();
        scanf("%d", &op);
        faxineirojp();
        switch (op) {
            case 1:
                estados();
                break;
            case 2:
                eleicoes();
                break;
            case 3:
                pessoas();
                break;
            case 4:
                candidatos();
                break;
            case 5:
                votos();
                break;
            case 0:break;
            default:printf("Opcao invalida\n");
        }
    }while (op != 0);
    free(puf);
    free(ppe);
    free(pel);
    free(pca);
    free(pvo);
    free(pco);
    return 0;
}
void menu() {
    printf("|============================================|\n");
    printf("| 1- UF                                      |\n");
    printf("| 2- ELEICAO                                 |\n");
    printf("| 3- PESSOA                                  |\n");
    printf("| 4- CANDIDATO                               |\n");
    printf("| 5- VOTO                                    |\n");
    printf("| 6- RESULTADO                               |\n");
    printf("| 0- SAIR                                    |\n");
    printf("|============================================|\n");
};
