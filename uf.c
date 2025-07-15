#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UF.h"
void estados() {
    int opuf;
    do {
        menuuf();
        scanf("%d", &opuf);
        faxineirojp();
        switch (opuf) {
            case 1:
                inserir();
                break;
            case 4:mostraruf();break;
            case 0:break;
            default:
                printf("escolha uma opcao valida \n");
                break;
        }

    } while (opuf != 0);


}
void menuuf() {
    printf("|============================================|\n");
    printf("| 1- INSERIR                                 |\n");
    printf("| 2- ALTERAR                                 |\n");
    printf("| 3- DELETAR                                 |\n");
    printf("| 4- LISTAR ESTADOS                          |\n");
    printf("| 5- MOSTRAR ESTADO                          |\n");
    printf("| 0- SAIR                                    |\n");
    printf("|============================================|\n");
}

void inserir() {
    FILE *f = fopen("UF.data", "rb+");
    if (f == NULL) {
        f = fopen("UF.data", "wb+");
        if (f == NULL) {
            printf("Erro ao abrir arquivo UF.data\n");
            exit(-1);
        }
    }

    uf temp;
    int cod;
    printf("digite o codigo: \n");
    scanf("%d", &cod);
    faxineirojp();
    temp.codigo = cod;

    char descri[100];
    printf("insira a descriçao: \n");
    fgets(descri, 100, stdin);
    descri[strcspn(descri, "\n")] = '\0';
    strcpy(temp.descricao,descri);

    char sig[3];
    printf("insira a sigla: \n");
    fgets(sig, sizeof(sig), stdin);
    sig[strcspn(sig, "\n")] = '\0';
    strcpy(temp.sigla, sig);


    fseek(f, 0, SEEK_END);
    fwrite(&temp, sizeof(uf), 1, f);
    fclose(f);

}
void mostraruf() {
    FILE *f = fopen("UF.data", "rb+");
    if (f == NULL) {
        printf("Arquivo nao existe. \n");
        return;
    }
    uf temp;
    fseek(f, 0, SEEK_SET);
    while (fread(&temp,sizeof(uf),1,f)) {//jp disse que era mais facil
        printf("codigo :%d \n", temp.codigo);
        printf("Estado : %s \n", temp.descricao);
        printf("Sigla : %s \n", temp.sigla);

    }

}
void faxineirojp() {
    while (getchar() != '\n');
}
