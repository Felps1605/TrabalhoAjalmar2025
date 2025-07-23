
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uf.h"

#define FILENAME "UF.data"
uf *puf = NULL;
int numufc = 0;
int capacity = 0;
int modified = 0;


void faxineirojp();
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
int buscar_existencia() {
    for (int i = 0; i < numufc; i++)
    {
        if (puf[i].existe == 1)
        {
            return i;
        }

    }
    return -1;
}
int buscar_sigla(char sig[3]) {
    for (int i = 0; i < numufc; i++)
    {
        int count = 0;
        for (int j = 0; j < strlen(puf[i].sigla); j++) {
            if (puf[i].sigla[j] == sig[j]) {
                ++count;
                if (count == 2)
                    return i;
            }
        }
    }
    return -1;
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

// Salvar o puf no arquivo
void saveUF()
{
    FILE *f = fopen(FILENAME, "wb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo uf\n");
        return;
    }
    fwrite(puf, sizeof(uf), numufc, f);
    fclose(f);
    modified = 0;
    printf("Alteracoes salvas com sucesso! \n");
}

int buscar_codigo(int cod);

// Insere um novo UF
void inserir() {
    // Ler o código
    char entrada[100];
    int cod;
    int valido;

    do {
        valido = 1;  // Assumimos que a entrada será válida

        printf("Insira o codigo:\n");
        fgets(entrada, sizeof(entrada), stdin);
        entrada[strcspn(entrada, "\n")] = '\0'; // Remove o \n
        faxineirojp();
        // Verifica se todos os caracteres são dígitos
        for (int i = 0; entrada[i] != '\0'; i++) {
            if (!isdigit(entrada[i])) {
                valido = 0;
                break;
            }
        }

        if (valido != 1) {
            printf("Entrada invalida! Digite apenas numeros inteiros positivos.\n");
            continue;  // volta para o início do laço
        }

        cod = atoi(entrada);  // Converte a string para inteiro

        if (buscar_codigo(cod) >= 0) {
            printf("Insira um numero que nao esteja no banco de dados.\n");
            valido = 0;
        }

    } while (buscar_codigo(cod) >= 0 || cod < 1 || valido !=1);

    // Ler a descrição
    do {
        char descri[100];
        printf("Insira a descricao: \n");
        fgets(descri, 100, stdin);
        descri[strcspn(descri, "\n")] = '\0';
        if (strlen(descri) == 0)
            printf("Insira uma descricao valida \n");
        else
            break;
    }while (1);

    // Ler a sigla
    char sig[3];
    int valida;
    do {
        printf("Insira a sigla: \n");
        fgets(sig, sizeof(sig), stdin);
        faxineirojp();
        sig[strcspn(sig, "\n")] = '\0';
        valida = 1;
        for (int i = 0; sig[i] != '\0'; i++) {
            if (!isalpha(sig[i])) {
                valida = 0;
                break;
            }
        }
        if (valida != 1 || strlen(sig) == 0) {
            printf("Entrada invalida. Digite apenas letras (sem numeros, espaços ou simbolos).\n");
        }
        else{

            if (buscar_sigla(sig) != -1 ) {
                if (puf[buscar_sigla(sig)].existe == 1 )
                    printf("Sigla ja esta em uso. \n");
            }else {
                if (strlen(sig) != 2)
                    printf("Insira uma sigla valida \n");
                else
                    break;
            }
        }

} while (1);

        // Dá push no novo UF
        uf temp;
        temp.codigo = cod;
        strcpy(temp.descricao, descri);
        strcpy(temp.sigla, sig);
        temp.existe = 1;

        pushUF(&temp);
        modified = 1;
        printf("%s foi inserido no sistema com sucesso. \n", temp.descricao);
}

// Show uf
void mostraruf()
{
    int cod;
    printf("Digite o codigo da UF desejada: \n");
    scanf("%d", &cod);
    faxineirojp();
    int flag = 0;
    for (int i = 0; i <= numufc; i++)
    {
        if (puf[i].codigo == cod){
            if (puf[i].existe == 0) {
                printf("Essa Uf não existe mais. \n");
                return;
            }
            flag = 1;
            printf("------------------------\n");
            printf("Estado : %s \n", puf[i].descricao);
            printf("Sigla  : %s \n", puf[i].sigla);
            printf("------------------------\n");
            break;
        }
    }
    if (flag == 0)
        printf("UF nao encontrada. \n");
}
void mostrartodos()
{
    if (puf == NULL) {
        printf("Nao ha UFs a serem exibidas. \n");
        return;
    }
    if (buscar_existencia()== -1 ) {
        printf("Nao existem Ufs a serem exibidas. \n");
        return;
    }
    else{
        for (int i = 0; i < numufc; i++) {
            if (puf[i].existe == 0)
                continue;
            printf("------------------------\n");
            printf("Codigo : %d \n", puf[i].codigo);
            printf("Estado : %s \n", puf[i].descricao);
            printf("Sigla  : %s \n", puf[i].sigla);
            printf("------------------------\n");

        }
    }
}

// Delete
void excluir()
{
    int cod;

        printf("insira o codigo da UF que deseja excluir: \n");
        scanf("%d", &cod);
        faxineirojp();
        if ((buscar_codigo(cod) < 0)){
            printf("UF nao encontrada. \n");
            return;
        }

    for (int i = 0; i < numufc; i++)
    {
        if (puf[i].codigo == cod)
        {
            if (puf[i].existe == 0) {
                printf("Essa Uf nao existe mais. \n");
                return;
            }
            puf[i].existe = 0;
            modified = 1;
            printf("%s foi removido do sistema com sucesso. \n", puf[i].descricao);
            break;
        }

    }

}

// Update
void alterar() {
    int cod;
    do {
        printf("Insira o codigo da UF que deseja alterar: \n");
        scanf("%d", &cod);
        faxineirojp();
        if (buscar_codigo(cod) >= 0){
            break;
        }
        else {
            printf("UF nao encontrada. \n");
        }

    }while (1);

    for (int i = 0; i <= numufc; i++)
    {

        if (puf[i].codigo == cod){
            if (puf[i].existe == 0) {
                printf("Essa Uf nao existe mais. \n");
                return;
            }

            
            do {
                char descri[100];
                printf("Insira a descricao: \n");
                fgets(descri, 100, stdin);
                descri[strcspn(descri, "\n")] = '\0';
                if (strlen(descri) == 0)
                    printf("Insira uma descricao valida \n");
                else
                    break;
            }while (1);
            strcpy(puf[i].descricao, descri);



            char sig[3];
            int valida;
            do
            {
                printf("Insira a sigla: \n");
                fgets(sig, sizeof(sig), stdin);
                faxineirojp();
                sig[strcspn(sig, "\n")] = '\0';
                valida = 1;
                for (int i = 0; sig[i] != '\0'; i++) {
                    if (!isalpha(sig[i])) {
                        valida = 0;
                        break;
                    }
                }
                if (valida != 1 || strlen(sig) == 0) {
                    printf("Entrada invalida. Digite apenas letras (sem numeros, espaços ou simbolos).\n");
                }
                else{

                    if (buscar_sigla(sig) != -1 ) {
                        if (puf[buscar_sigla(sig)].existe == 1 )
                            printf("Sigla ja esta em uso. \n");
                    }else {
                        if (strlen(sig) != 2)
                            printf("Insira uma sigla valida \n");
                        else
                            break;
                    }
                }
            } while (1);
            strcpy(puf[i].sigla, sig);
            modified = 1;
            printf("%s foi alterado no sistema com sucesso. \n", puf[i].descricao);
            break;
        }
    }
}

// Limpador de buffer
void faxineirojp()
{
    while (getchar() != '\n')
        ;
}

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
                saveUF();
                break;
            default:
                printf("escolha uma opcao valida \n");
                break;
        }

    } while (opuf != 0);
}
