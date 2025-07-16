#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UF.h"
uf *puf = NULL;
int numufc = 0;
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
            case 2:
                alterar();break;
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
    int cod;
    do {
        printf("digite o codigo: \n");
        scanf("%d", &cod);
        faxineirojp();
        if (cod < 1 || cod > 27) {
            printf("codigo invalido! Deve estar entre 1 e 27.\n");
            return;
        }
        if (buscar_codigo(cod)>= 0)
            printf("Digite um numero que nao esta no banco de dados");
    }while (buscar_codigo(cod)>= 0 || cod < 1 || cod > 27);
    char descri[100];
    printf("insira a descriçao: \n");
    fgets(descri, 100, stdin);
    descri[strcspn(descri, "\n")] = '\0';
    char sig[3];
    do {
        printf("insira a sigla: \n");
        fgets(sig, sizeof(sig), stdin);
        sig[strcspn(sig, "\n")] = '\0';
        if (strlen(sig) != 2)
            printf("Digite uma sigla valida");
    }while (strlen(sig) != 2);
    numufc++;
    puf = reallocu(puf);
    puf[numufc - 1].codigo = cod;
    strcpy(puf[numufc - 1].descricao, descri);
    strcpy(puf[numufc - 1].sigla, sig);

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

    };
}
void alterar(){
        FILE *f = fopen("UF.data", "rb+");
        if (f == NULL) {
            printf("Arquivo nao existe. \n");
        }
        int cod;
        printf("insira o codigo que deseja alterar: \n");
        scanf("%d", &cod);
        faxineirojp();
        uf temp;
        fseek(f, 0, SEEK_SET);
        for (int i = 1; i <= 27; i++) {
            fread(&temp, sizeof(uf), 1, f);
            if (temp.codigo == cod) {
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
                fseek(f, (i-1)* sizeof(uf), SEEK_SET);
                fwrite(&temp, sizeof(uf), 1, f);
                fclose(f);
                break;
            }
            printf("codigo nao existe: \n");
            return 0;
        }

}
void excluir() {
    FILE *f = fopen("UF.data", "rb+");
    if (f == NULL) {
        printf("Arquivo nao existe. \n");
    }

}

void faxineirojp() {
    while (getchar() != '\n');
}
void comecar() {
    FILE *f = fopen("UF.data", "rb+");
    if (f == NULL) {
        f = fopen("UF.data", "wb+");
        if (f == NULL) {
            printf("Erro ao abrir arquivo UF.data\n");
            exit(-1);
        }
    }
    numufc = ftell(f)/sizeof(uf);
    puf =  malloc(numufc * sizeof(uf));
    fseek(f, 0, SEEK_SET);
    for (int i = 0; i < numufc; i++) {
        fread(&puf[i], sizeof(uf), 1, f);
    }
}
uf* reallocu(uf* p) {
    uf *novo = realloc(p, sizeof(uf) * numufc);
    if (novo == NULL) {
        exit (-1);
    }
    return novo;
}
int buscar_codigo(int cod) {
    for (int i=0; i < numufc; i++) {
        if (puf[i].codigo == cod) {
            return i;
        }
    }
    return -1;
}

