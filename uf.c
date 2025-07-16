#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "UF.h"

#define FILENAME "UF.data"

// Menu
void estados()
{
    int opuf;
    do
    {
        menuuf();
        scanf("%d", &opuf);
        faxineirojp();
        switch (opuf)
        {
        case 1:
            inserir();
            break;
        case 2:
            alterar();
            break;
        case 3:
            excluir();
            break;
        case 4:
            mostrartodos();
            break;
        case 5:
            mostraruf();
            break;
        case 0:
            break;
        default:
            printf("escolha uma opcao valida \n");
            break;
        }

    } while (opuf != 0);
}
void menuuf()
{
    printf("|============================================|\n");
    printf("| 1- INSERIR                                 |\n");
    printf("| 2- ALTERAR                                 |\n");
    printf("| 3- DELETAR                                 |\n");
    printf("| 4- LISTAR ESTADOS                          |\n");
    printf("| 5- MOSTRAR ESTADO                          |\n");
    printf("| 0- SAIR                                    |\n");
    printf("|============================================|\n");
}

// Load pega os UFs dos arquivos
void loadUFs()
{
    // Abre o arquivo
    FILE *f = fopen(FILENAME, "rb");
    // Verifica se funcionou
    if (f == NULL) return;

    // Ler o arquivo
    uf temp;
    while (fread(&temp, sizeof(temp), 1, f) == 1) {
        pushUF(&temp);
    }
    fclose(f);
    modified = 0;
}

// Adicionar UF no vetor
void pushUF(const uf *pushedUf) {
    // Verifica se o vetor (puf) tem capacidade para mais um elemento
    if (numufc >= capacity) {
        // Adiciona mais 10 espaços no vetor realocando a memória
        capacity = (capacity == 0 ? 10 : capacity + 10);
        puf = (uf *)realloc(puf, sizeof(uf) * capacity);
        if (!puf) return;
    }

    // Coloca o novo uf no primeiro espaço vago no vetor
    puf[numufc++] = *pushedUf;
}

// Insere um novo UF
void inserir()
{
    // Ler o código
    int cod;
    do
    {
        printf("digite o codigo: \n");
        scanf("%d", &cod);
        faxineirojp();
        if (cod < 1 || cod > 27)
        {
            printf("codigo invalido! Deve estar entre 1 e 27.\n");
            return;
        }
        if (buscar_codigo(cod) >= 0)
            printf("Digite um numero que nao esta no banco de dados: \n");
    } while (buscar_codigo(cod) >= 0 || cod < 1 || cod > 27);

    // Ler a descrição
    char descri[100];
    printf("insira a descriçao: \n");
    fgets(descri, 100, stdin);
    descri[strcspn(descri, "\n")] = '\0';

    // Ler a sigla
    char sig[3];
    do
    {
        printf("insira a sigla: \n");
        fgets(sig, sizeof(sig), stdin);
        sig[strcspn(sig, "\n")] = '\0';
        if (strlen(sig) != 2)
            printf("Digite uma sigla valida \n");
    } while (strlen(sig) != 2);

    // Dá push no novo UF
    uf temp;
    temp.codigo = cod;
    strcpy(temp.descricao, descri);
    strcpy(temp.sigla, sig);

    pushUF(&temp);
    modified = 1;
}

// Show uf
void mostraruf()
{
    int cod;
    printf("digite o código da UF desejada: \n");
    scanf("%d", &cod);
    faxineirojp();
    for (int i = 0; i < numufc; i++)
    {
        if (puf[i].codigo == cod)
        {
            printf("codigo :%d \n", puf[i].codigo);
            printf("Estado : %s \n", puf[i].descricao);
            printf("Sigla : %s \n", puf[i].sigla);
            break;
        }else
        printf("UF nao encontrada. \n");
    }

}
void mostrartodos()
{
    for (int i = 0; i < numufc; i++) {
        printf("codigo :%d \n", puf[i].codigo);
        printf("Estado : %s \n", puf[i].descricao);
        printf("Sigla : %s \n", puf[i].sigla);
    }
}

// Delete
void excluir()
{
    int cod;
    printf("digite o código da UF que deseja excluir: \n");
    scanf("%d", &cod);
    faxineirojp();
    for (int i = 0; i < numufc; i++)
    {
        if (puf[i].codigo == cod)
        {

            break;
        }else
        printf("UF nao encontrada. \n");
    }

}

// Update
void alterar()
{
    FILE *f = fopen(FILENAME, "rb+");
    if (f == NULL)
    {
        printf("Arquivo nao existe. \n");
    }
    int cod;
    printf("insira o codigo que deseja alterar: \n");
    scanf("%d", &cod);
    faxineirojp();
    uf temp;
    fseek(f, 0, SEEK_SET);
    int flag = 0;
    for (int i = 1; i <= 27; i++)
    {
        fread(&temp, sizeof(uf), 1, f);
        if (temp.codigo == cod)
        {
            char descri[100];
            printf("insira a descriçao: \n");
            fgets(descri, 100, stdin);
            descri[strcspn(descri, "\n")] = '\0';
            strcpy(temp.descricao, descri);

            char sig[3];
            printf("insira a sigla: \n");
            fgets(sig, sizeof(sig), stdin);
            sig[strcspn(sig, "\n")] = '\0';
            strcpy(temp.sigla, sig);
            fseek(f, (i - 1) * sizeof(uf), SEEK_SET);
            fwrite(&temp, sizeof(uf), 1, f);
            fclose(f);
            flag = 1;
            break;
        }
    }
    if (flag == 0)
       printf("codigo nao existe: \n");
}

// Limpador de buffer
void faxineirojp()
{
    while (getchar() != '\n')
        ;
}

// Utils
uf *reallocu(uf *p)
{
    uf *novo = realloc(p, sizeof(uf) * numufc);
    if (novo == NULL)
    {
        exit(-1);
    }
    return novo;
}
int buscar_codigo(int cod)
{
    for (int i = 0; i < numufc; i++)
    {
        if (puf[i].codigo == cod)
        {
            return i;
        }
    }
    return -1;
}
