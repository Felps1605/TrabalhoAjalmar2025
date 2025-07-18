#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eleicoes.h"

#include "UF.h"

#define FILENAME "eleicoes.data"

eleicao *pel = NULL;
int num_elei = 0;
int capacidade_el = 0;
int modificado_el = 0;

// Menu
void eleicoes()
{
    int opel;
    do
    {
        menu_eleicao();
        scanf("%d", &opel);
        faxineirojpe();
        switch (opel)
        {
        case 1:
            inserir_eleicao();
            break;
        case 2:
            alterar_eleicao();
            break;
        case 3:
            excluir_eleicao();
            break;
        case 4:
            mostrartodos_eleicoes();
            break;
        case 5:
            mostrar_eleicao();
            break;
        case 0:
            salvar_eleicoes();
            break;
        default:
            printf("Opcao invalida. \n");
            break;
        }

    } while (opel != 0);
}
void menu_eleicao()
{
    printf("|============================================|\n");
    printf("| 1- INSERIR                                 |\n");
    printf("| 2- ALTERAR                                 |\n");
    printf("| 3- DELETAR                                 |\n");
    printf("| 4- LISTAR ELEICOES                         |\n");
    printf("| 5- MOSTRAR ELEICAO                         |\n");
    printf("| 0- SAIR                                    |\n");
    printf("|============================================|\n");
}

// Load pega as eleicoes dos arquivos
void carregar_eleicoes()
{
    // Abre o arquivo
    FILE *f = fopen(FILENAME, "rb");
    // Verifica se funcionou
    if (f == NULL) return;

    // Ler o arquivo
    eleicao temp;
    while (fread(&temp, sizeof(temp), 1, f) == 1) {
        push_eleicoes(&temp);
    }
    fclose(f);
    modificado_el = 0;
}

// Adicionar eleicao no vetor
void push_eleicoes(const eleicao *pushedeleicao) {
    // Verifica se o vetor (pel) tem capacidade para mais um elemento
    if (num_elei >= capacidade_el) {
        // Adiciona mais 10 espaços no vetor realocando a memória
        capacidade_el = (capacidade_el == 0 ? 10 : capacidade_el + 10);
        pel = (eleicao *)realloc(pel, sizeof(eleicao) * capacidade_el);
        if (!pel) return;
    }

    // Coloca o novo uf no primeiro espaço vago no vetor
    pel[num_elei++] = *pushedeleicao;
}

// Salvar o pel no arquivo
void salvar_eleicoes()
{
    FILE *f = fopen(FILENAME, "wb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo uf\n");
        return;
    }
    fwrite(pel, sizeof(eleicao), num_elei, f);
    fclose(f);
    modificado_el = 0;
    printf("Alteracoes salvas com sucesso! \n");
}

// Insere uma nova eleicao
void inserir_eleicao()
{
    // Ler o código
    int cod;
        printf("Insira o codigo da UF: \n");
        scanf("%d", &cod);
        faxineirojpe();
        if (cod < 1 )
        {
            printf("Codigo invalido! Precisa ser maior que 0! \n");
            return;
        }
        if (buscar_codigo(cod) == -1 || puf[buscar_codigo(cod)].existe == 0) {
            printf("Insira o codigo de uma UF que esteja no banco de dados! \n");
            return;
        }

    // Ler a descrição
    char descri[100];
    printf("Insira a descricao: \n");
    fgets(descri, 100, stdin);
    descri[strcspn(descri, "\n")] = '\0';

    // Ler a sigla
    int ano;
    do
    {
        printf("Insira o ano: \n");
        scanf("%d", &ano);
        faxineirojpe();
        if (buscar_eleicao(cod, ano) != -1) {
            if (buscar_existencia_eleicao(cod, ano)==1)
                printf("Ja existe uma eleicao nesse estado nesse ano. \n");
        }else
            break;

    } while (1);

    // Dá push na nova eleição
    eleicao tempo;
    tempo.codigoUF = cod;
    strcpy(tempo.descricao, descri);
    tempo.ano = ano;
    tempo.existe = 1;

    push_eleicoes(&tempo);
    modificado_el = 1;
    printf("%s foi adicionada no sistema com sucesso. \n", tempo.descricao);

}

// Show uf
void mostrar_eleicao() {
    if (pel == NULL) {
        printf("Nao ha eleicoes a serem exibidas. \n");
        return;
    }
    int cod;
    printf("Digite o codigo da UF da eleicao desejada: \n");
    scanf("%d", &cod);
    faxineirojpe();
    int flag = 0;
    if (buscar_codigo(cod)== -1) {
        printf("UF nao encontrada. \n");
        return;
    }if (puf[buscar_existencia()].existe == 0) {
        printf("Essa UF nao existe mais. \n");
        return;
    }
    for (int i = 0; i <= num_elei; i++)
    {
        if (pel[i].codigoUF == cod){
            printf("Digite o ano da eleicao desejada: \n");
            int ano;
            scanf("%d", &ano);
            faxineirojpe();
            if (buscar_eleicao(cod, ano) != -1) {
                if (pel[i].existe==0) {
                    printf("Eleicao nao existe mais. \n");
                    return;
                }
                flag = 1;
                printf("CodigoUF  : %d \n", pel[i].codigoUF);
                printf("Descricao : %s \n", pel[i].descricao);
                printf("Ano       : %d \n", pel[i].ano);
                break;
            }
        }
    }
    if (flag == 0)
        printf("Eleicao nao encontrada. \n");
}
void mostrartodos_eleicoes()
{
int flag = 0;
    if (pel == NULL) {
        printf("Nao ha eleicoes a serem exibidas. \n");
        return;
    }
    {
        for (int i = 0; i < num_elei; i++) {
            if (pel[i].existe == 0)
                continue;
            if (puf[buscar_codigo(pel[i].codigoUF)].existe == 0)
                continue;
            printf("CodigoUF : %d \n", pel[i].codigoUF);
            printf("Descricao: %s \n", pel[i].descricao);
            printf("Ano      : %d \n\n", pel[i].ano);
            flag = 1;
        }
    }if (flag == 0)
        printf("Nao existem eleicoes a serem exibidas. \n");
}

// Delete
void excluir_eleicao()
{   if (pel == NULL) {
        printf("Nao ha eleicoes a serem excluidas. \n");
        return;
    }
    int cod;
    printf("Digite o codigo da UF da eleicao que deseja excluir: \n");
    scanf("%d", &cod);
    faxineirojpe();
    int flag = 0;
    if (buscar_codigo(cod)== -1) {
        printf("UF nao encontrada. \n");
        return;
    }
    if (puf[buscar_existencia()].existe == 0) {
        printf("Essa UF nao existe mais. \n");
        return;
    }

    printf("Digite o ano da eleicao que deseja excluir: \n");
    int ano;
    scanf("%d", &ano);
    faxineirojpe();
    for (int i = 0; i <= num_elei; i++)
    {
            if (pel[i].codigoUF == cod && pel[i].ano == ano) {
                if (pel[i].existe == 0) {
                    printf("Essa eleicao nao existe mais. \n");
                    return;
                }
                pel[i].existe = 0;
                printf("%s foi removida do sistema com sucesso. \n", pel[i].descricao);
                modificado_el = 1;
                flag = 1;
                break;
            }
    }

    if (flag == 0) {
        printf("Eleicao nao encontrada. \n");
        return;
    }
}

// Update
void alterar_eleicao() {
    if (pel == NULL) {
        printf("Nao ha eleicoes a serem alteradas. \n");
        return;
    }
    int cod;
    printf("Digite o codigo da UF da eleicao que deseja alterar: \n");
    scanf("%d", &cod);
    faxineirojpe();
    int flag = 0;
    if (buscar_codigo(cod)== -1) {
        printf("UF nao encontrada. \n");
        return;
    }
    if (puf[buscar_existencia()].existe == 0) {
        printf("Essa UF nao existe mais. \n");
        return;
    }

    for (int i = 0; i <= num_elei; i++)
    {
        if (pel[i].codigoUF == cod){
            printf("Digite o ano da eleicao desejada: \n");
            int ano;
            scanf("%d", &ano);
            faxineirojpe();
            if (buscar_eleicao(cod, ano) != -1) {
                if (pel[i].existe == 0) {
                    printf("Essa eleicao nao existe mais. \n");
                    return;
                }
                flag = 1;
                char descri[100];
                printf("Insira a nova descricao: \n");
                fgets(descri, 100, stdin);
                descri[strcspn(descri, "\n")] = '\0';
                strcpy(pel[i].descricao, descri);
                modificado_el = 1;
                printf("%s modificada com sucesso. \n", pel[i].descricao);
                break;
            }
        }
    }
    if (flag == 0)
        printf("Eleicao nao encontrada. \n");
}

// Utils
int buscar_eleicao(int cod, int ano)
{
    for (int i = 0; i < num_elei; i++)
    {
        if (pel[i].codigoUF == cod && pel[i].ano== ano)
        {
            return i;
        }
    }
    return -1;
}

int buscar_existencia_eleicao() {
    for (int i = 0; i < num_elei; i++)
    {
        if (pel[i].existe == 1)
        {
            return 1;
        }

    }
    return -1;
}

// Limpador de buffer
void faxineirojpe()
{
    while (getchar() != '\n');
}
