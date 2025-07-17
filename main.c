#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "UF.h"
#include "pessoas.h"
void estados();
void menu();
int main() {
    loadUFs();
    carregar_pessoas();
    int op;
    do {
        menu();
        scanf("%d", &op);
        faxineirojp();
        switch (op) {
            case 1:estados();break;
            case 0:break;
            default:printf("Opcao invalida\n");
        }
    }while (op != 0);
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


