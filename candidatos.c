#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eleicoes.h"
#include "candidatos.h"
#include "pessoas.h"
#include "UF.h"

#define FILENAME "candidatos.data"

candidato *pca = NULL;
int num_can = 0;
int capacidade_ca = 0;
int modificado_ca = 0;

// Menu
void candidatos()
{
    int opca;
    do
    {
        menu_candidatos();
        scanf("%d", &opca);
        faxineirojp();
        switch (opca)
        {
        case 1:
            inserir_candidato();
            break;
        case 2:
            excluir_candidato();
            break;
        case 3:
            mostrartodos_candidatos();
            break;
        case 4:
            mostrartodos_candidatos_por_ano();
            break;
        case 5:
            mostrar_candidato_por_eleicao();
            break;
        case 0:
            salvar_candidatos();
            break;
        default:
            printf("Opcao invalida. \n");
            break;
        }

    } while (opca != 0);
}
void menu_candidatos()
{
    printf("|============================================|\n");
    printf("| 1- INSERIR                                 |\n");
    printf("| 2- DELETAR                                 |\n");
    printf("| 3- LISTAR CANDIDATOS                       |\n");
    printf("| 4- LISTAR CANDIDATOS POR ANO               |\n");
    printf("| 5- LISTAR CANDIDATOS POR ELEICAO           |\n");
    printf("| 0- SAIR                                    |\n");
    printf("|============================================|\n");
}

// Load pega os candidatos dos arquivos
void carregar_candidatos()
{
    // Abre o arquivo
    FILE *f = fopen(FILENAME, "rb");
    // Verifica se funcionou
    if (f == NULL) return;

    // Ler o arquivo
    candidato temp;
    while (fread(&temp, sizeof(temp), 1, f) == 1) {
        push_candidatos(&temp);
    }
    fclose(f);
    modificado_ca = 0;
}

// Adicionar candidatos no vetor
void push_candidatos(const candidato *pushedcandidato) {
    // Verifica se o vetor (pca) tem capacidade para mais um elemento
    if (num_can >= capacidade_ca) {
        // Adiciona mais 10 espaços no vetor realocando a memória
        capacidade_ca = (capacidade_ca == 0 ? 10 : capacidade_ca + 10);
        pca = (candidato *)realloc(pca, sizeof(candidato) * capacidade_ca);
        if (!pca) return;
    }

    // Coloca o novo candidato no primeiro espaço vago no vetor
    pca[num_can++] = *pushedcandidato;
}

// Salvar o pca no arquivo
void salvar_candidatos()
{
    FILE *f = fopen(FILENAME, "wb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo candidatos\n");
        return;
    }
    fwrite(pca, sizeof(candidato), num_can, f);
    fclose(f);
    modificado_ca = 0;
    printf("Alteracoes salvas com sucesso! \n");
}

// Insere um novo candidato
void inserir_candidato()
{
    // Ler o código
    int cod;
        printf("Insira o codigo da UF: \n");
        scanf("%d", &cod);
        faxineirojp();
        if (cod < 1 )
        {
            printf("Codigo invalido! Precisa ser maior que 0! \n");
            return;
        }
        if (buscar_codigo(cod) == -1 || puf[buscar_codigo(cod)].existe == 0) {
            printf("Insira o codigo de uma UF que esteja no banco de dados! \n");
            return;
        }

    // Ler o ano
    int ano;
    do
    {
        printf("Insira o ano: \n");
        scanf("%d", &ano);
        faxineirojp();
        if (buscar_eleicao(cod, ano) != -1){
            if (pel[buscar_eleicao(cod, ano)].existe == 0)
                printf("Nao existe uma eleicao nesse estado nesse ano. \n");
            else
                break;
        }
    } while (1);

    // Ler o cpf
    char cpf[20];
    do {
        printf("Insira o CPF: \n");
        fgets(cpf, sizeof(cpf), stdin);
        cpf[strcspn(cpf, "\n")] = '\0';
        faxineirojp();
        if (strlen(cpf) != 11)
                printf("Insira um CPF valido \n");
        else
                if (!buscar_cpf(cpf)) {
            printf("CPF nao esta cadastrado no sistema. \n");
                    return;

        }else
            if (buscar_cpf_por_ano(cpf, ano) != -1) {
                printf("Esse candidato ja esta concorrendo nesse ano. \n");
                return;
            }else
                break;
    } while (1);


    //Ler o numero
    int num;
    do {
        char entrada[10];
        printf("Insira o numero do candidato: \n");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0';
        faxineirojp();
        if (strlen(entrada) != 2) {
            printf("Insira um numero valido (2 caracteres). \n");
            continue;
        }
        num = atoi(entrada);
        if (buscar_numero(num) != -1) {
            if (pca[buscar_numero(num)].existe == 1 )
                printf("Numero ja esta em uso. \n");
            else
                break;
        }else
            break;
    } while (1);

    // Dá push no novo candidato
    candidato tempo;
    tempo.codigoUF = cod;
    strcpy(tempo.descricao, ppe[buscar_cpf(cpf)].nome);
    tempo.ano = ano;
    strcpy(tempo.CPF, cpf);
    tempo.numero = num;
    tempo.existe = 1;

    push_candidatos(&tempo);
    modificado_ca = 1;
    printf("%s foi adicionad0 no sistema com sucesso. \n", tempo.descricao);
    ordenacao_por_uf_candidato();
}

// Show candidato
void mostrar_candidato_por_eleicao() {
    if (pca == NULL) {
        printf("Nao ha candidatos a serem exibidos. \n");
        return;
    }
    int cod;
    printf("Digite o codigo da UF da eleicao desejada: \n");
    scanf("%d", &cod);
    faxineirojp();
    int flag = 0;
    if (buscar_codigo(cod)== -1) {
        printf("UF nao encontrada. \n");
        return;
    }if (puf[buscar_existencia()].existe == 0) {
        printf("Essa UF nao existe mais. \n");
        return;
    }
            printf("Digite o ano da eleicao desejada: \n");
            int ano;
            scanf("%d", &ano);
            faxineirojp();
            if (buscar_eleicao(cod, ano) != -1) {
                if (pel[buscar_eleicao(cod, ano)].existe==0) {
                    printf("Eleicao nao existe mais. \n");
                    return;
                }
                for (int j = 0; j <= num_can; j++) {
                    if (pca [j].codigoUF == cod && pca[j].ano == ano) {
                        if (pca[j].existe == 0) {
                            continue;
                        }
                        printf("Nome     : %s \n", pca[j].descricao);
                        printf("CPF      : %s \n", pca[j].CPF);
                        printf("Numero   : %d \n\n", pca[j].numero);
                    }
                }
            }else
                printf("Eleicao nao encontrada. \n");
}


void mostrartodos_candidatos()
{
int flag = 0;
    if (pca == NULL) {
        printf("Nao ha candidatos a serem exibidos. \n");
        return;
    }
    {
        for (int i = 0; i < num_can; i++) {
            if (pca[i].existe == 0)
                continue;
            if (puf[buscar_codigo(pca[i].codigoUF)].existe == 0)
                continue;
            if (pel[buscar_eleicao(pca[i].codigoUF, pca[i].ano)].existe == 0)
                continue;
            printf("CodigoUF : %d \n", pca[i].codigoUF);
            printf("Ano      : %d \n", pca[i].ano);
            printf("Nome     : %s \n", pca[i].descricao);
            printf("CPF      : %s \n", pca[i].CPF);
            printf("Numero   : %d \n\n", pca[i].numero);

            flag = 1;
        }
    }if (flag == 0)
        printf("Nao existem candidatos a serem exibidos. \n");
}

void mostrartodos_candidatos_por_ano() {
    int flag = 0;
    if (pca == NULL) {
        printf("Nao ha candidatos a serem exibidos. \n");
        return;
    }
    printf("Digite o ano da eleicao desejada: \n");
    int ano;
    scanf("%d", &ano);
    faxineirojp();
    {
        for (int i = 0; i < num_can; i++) {
            if (pca[i].ano == ano){
                if (pca[i].existe == 0)
                    continue;
                if (puf[buscar_codigo(pca[i].codigoUF)].existe == 0)
                    continue;
                if (pel[buscar_eleicao(pca[i].codigoUF, pca[i].ano)].existe == 0)
                    continue;
                printf("CodigoUF : %d \n", pca[i].codigoUF);
                printf("Ano      : %d \n", pca[i].ano);
                printf("Nome     : %s \n", pca[i].descricao);
                printf("CPF      : %s \n", pca[i].CPF);
                printf("Numero   : %d \n\n", pca[i].numero);

                flag = 1;
            }
        }
    }if (flag == 0)
        printf("Nao existem candidatos a serem exibidos. \n");

}

// Delete
void excluir_candidato() {
    if (pca == NULL) {
        printf("Nao ha candidatos a serem excluidos. \n");
        return;
    }
    int ano;
    printf("Insira o ano da candidatura que deseja excluir: \n");
    scanf("%d", &ano);
    faxineirojp();

    do{
        char cpf[12];
        printf("Insira o CPF do candidato: \n");
        fgets(cpf, sizeof(cpf), stdin);
        cpf[strcspn(cpf, "\n")] = '\0';
        faxineirojp();
        if (strlen(cpf) != 11)
            printf("Insira um CPF valido \n");
        else
            if (!buscar_cpf(cpf)) {
                printf("CPF nao esta cadastrado no sistema. \n");
                return;

            }else
                if (buscar_cpf_por_ano(cpf, ano) != -1) {
                    if (pca[buscar_cpf_por_ano(cpf, ano)].existe == 0) {
                        printf("Candidatura ja nao existe mais. \n");
                        return;
                    }

                    if (puf[buscar_codigo(pca[buscar_cpf_por_ano(cpf, ano)].codigoUF)].existe == 0) {
                        printf("UF ja nao existe mais. \n");
                        return;
                    }
                    if (pel[buscar_eleicao(pca[buscar_cpf_por_ano(cpf, ano)].codigoUF, pca[buscar_cpf_por_ano(cpf, ano)].ano)].existe == 0) {
                        printf("Eleicao ja nao existe mais. \n");
                        return;
                    }

                    pca[buscar_cpf_por_ano(cpf, ano)].existe = 0;
                    modificado_ca = 1;
                    printf("Candidatura excluida com sucesso \n");
                    return;
                }else {
                    printf("Candidatura nao encontrada. \n");
                    return;
                }
    } while (1);
}
// Utils

int buscar_numero(int num) {
    for (int i = 0; i < num_can; i++)
    {
            if (pca[i].numero == num) {
                    return i;
            }
    }
    return -1;
}int buscar_cpf_por_ano(char cpf[12], int ano) {
    for (int i = 0; i < num_can; i++)
    {
        int count = 0;
        if (pca[i].ano== ano){
            for (int j = 0; j < num_can; j++) {
                if (pca[i].CPF[j] == cpf[j])
                    count++;
            }if (count == 11)
                return i;
        }
    }
    return -1;
}

void ordenacao_por_uf_candidato()
{
    for (int i = 0; i < (num_can - 1 ); i++) {
        for (int j = (i + 1); j < num_can; j++) {
            if (pca[i].codigoUF > pca[j].codigoUF) {
                candidato aux = pca[i];
                pca[i] = pca[j];
                pca[j] = aux;
            }
        }
    }
}
