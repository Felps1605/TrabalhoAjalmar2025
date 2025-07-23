#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pessoas.h"
#include "uf.h"

#define FILENAME "pessoas.data"
pessoa *ppe = NULL;
int num_pes = 0;
int capacidade = 0;
int modificado = 0;

// Menu
void pessoas()
{
    int oppe;
    do
    {
        menupessoas();
        scanf("%d", &oppe);
        faxineirojp();

        switch (oppe)
        {
            case INSERIR_PESSOA:
                inserir_pessoa();
                break;
            case ALTERAR_PESSOA:
                alterar_pessoa();
                break;
            case EXCLUIR_PESSOA:
                excluir_pessoa();
                break;
            case MOSTRAR_TODAS_PESSOAS:
                mostrartodos_pessoas();
                break;
            case MOSTRAR_PESSOA:
                mostrar_pessoa();
                break;
            case SAIR_PESSOA:
                salvar_pessoas();
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }

    } while (oppe != SAIR_PESSOA);
}

void menupessoas()
{
    printf("|============================================|\n");
    printf("| 1- INSERIR                                 |\n");
    printf("| 2- ALTERAR                                 |\n");
    printf("| 3- DELETAR                                 |\n");
    printf("| 4- LISTAR PESSOAS                          |\n");
    printf("| 5- MOSTRAR PESSOA                          |\n");
    printf("| 0- SAIR                                    |\n");
    printf("|============================================|\n");
}

// Pega as pessoas dos arquivos
void carregar_pessoas()
{
    // Abre o arquivo
    FILE *f = fopen(FILENAME, "rb");
    // Verifica se funcionou
    if (f == NULL) {
        return;
    }


    // Ler o arquivo
    pessoa temp;
    while (fread(&temp, sizeof(temp), 1, f) == 1) {
        push_pessoas(&temp);
    }
    fclose(f);
    modificado = 0;
}

// Adicionar UF no vetor
void push_pessoas(const pessoa *pushed_pessoa) {
    // Verifica se o vetor (ppe) tem capacidade para mais um elemento
    if (num_pes >= capacidade) {
        // Adiciona mais 10 espaços no vetor realocando a memória
        capacidade = (capacidade == 0 ? 10 : capacidade + 10);
        ppe = (pessoa *)realloc(ppe, sizeof(pessoa) * capacidade);
        if (!ppe) return;
    }

    // Coloca o novo uf no primeiro espaço vago no vetor
    ppe[num_pes++] = *pushed_pessoa;
}

// Salvar o ppe no arquivo
void salvar_pessoas()
{
    FILE *f = fopen(FILENAME, "wb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo pessoa\n");
        return;
    }
    fwrite(ppe, sizeof(pessoa), num_pes, f);
    fclose(f);
    modificado = 0;
    printf("Alteracoes salvas com sucesso! \n");
}

// Insere uma nova pessoa
void inserir_pessoa()
{
    // Ler o nome
    char nom[250];
    int valido;

    do {
        valido = 1;  // Começa assumindo que a entrada é válida
        int tem_letra = 0;  // Para garantir que há pelo menos uma letra

        printf("Insira o nome (somente letras e espaços): \n");
        fgets(nom, sizeof(nom), stdin);
        nom[strcspn(nom, "\n")] = '\0';  // Remove o '\n' do final da entrada

        // Verifica caractere por caractere
        for (int i = 0; nom[i] != '\0'; i++) {
            if (isalpha(nom[i])) {
                tem_letra = 3;  // Pelo menos uma letra foi encontrada
            } else if (nom[i] != ' ') {
                valido = 0;  // Encontrou algo que não é letra nem espaço
                break;
            }
        }

        // Verifica se há ao menos uma letra e se os caracteres são válidos
        if (!valido || !tem_letra) {
            printf("Entrada invalida! Digite apenas letras e espaços (sem números ou símbolos).\n");
            valido = 0;
        }

    } while (!valido);

    // Ler o cpf
    char cpf[20];  // Maior que 12 para evitar overflow por erro do usuário
    do {
        valido = 1;

        printf("Insira o CPF (somente numeros, sem pontos ou tracos): \n");
        fgets(cpf, sizeof(cpf), stdin);
        cpf[strcspn(cpf, "\n")] = '\0';  // Remove o \n final

        faxineirojp();

        // Verifica se só contém dígitos
        for (int i = 0; cpf[i] != '\0'; i++) {
            if (!isdigit(cpf[i])) {
                valido = 0;
                break;
            }
        }

        // Verifica tamanho e se é só número
        if (!valido || strlen(cpf) != 11) {
            printf("Insira um CPF valido com 11 digitos numericos.\n");
            valido = 0;
        }

        else
        // Verifica duplicidade
            if (buscar_cpf(cpf)) {
                printf("CPF ja esta cadastrado no sistema.\n");
                valido = 0;
            }

    } while (!valido);

    // Ler o titulo
    char tit_ele[14];
    do
    {
        printf("Insira o titulo (somente numeros, sem pontos ou tracos): \n");
        fgets(tit_ele, sizeof(tit_ele), stdin);
        tit_ele[strcspn(tit_ele, "\n")] = '\0';
        faxineirojp();

        for (int i = 0; tit_ele[i] != '\0'; i++) {
            if (!isdigit(tit_ele[i])) {
                valido = 0;
                break;
            }
        }
        if (!valido || strlen(tit_ele) != 13) {
            printf("Insira um titulo valido \n");
            valido = 0;
        }
        if (buscar_titulo(tit_ele)) {
            printf("Titulo de eleitor ja esta cadastrado no sistema. \n");
        }


    } while (!valido);

    //telefone
    char fone[14];
    do {
        valido = 1;

        printf("Insira o telefone (formato: xx9xxxxxxxx): \n");
        fgets(fone, sizeof(fone), stdin);
        fone[strcspn(fone, "\n")] = '\0';  // Remove o '\n'
        faxineirojp();
        if (strlen(fone) > 0) {
            // Verifica cada caractere
            for (int i = 0; i < 13; i++) {
                        valido = 0;
                        break;
                if (!isdigit(fone[i])) {
                        valido = 0;
                        break;
                }
            }
        }

        if (valido != 1) {
            printf("Telefone invalido! Use o formato: xx9xxxxxxxx (somente numeros e 1 espaco apos o DDD).\n");
        }

    } while (!valido);
    //endereço
    char endere[255];
    printf("Insira o endereco \n");
    fgets(endere, sizeof(endere), stdin);
    endere[strcspn(endere, "\n")] = '\0';

    //data de nascimento
    int data_nasc[3];
    printf("Insira a data_nascimento (DD MM AAAA): \n");
    scanf("%d %d %d", &data_nasc[0], &data_nasc[1], &data_nasc[2]);
    faxineirojp();

    // Dá push na nova pessoa
    pessoa temp;
    strcpy(temp.nome , nom);
    strcpy(temp.CPF, cpf);
    strcpy(temp.titulo, tit_ele);
    strcpy(temp.telefone, fone);
    strcpy(temp.endereco, endere);
    temp.data_nascimento[0] = data_nasc[0];
    temp.data_nascimento[1] = data_nasc[1];
    temp.data_nascimento[2] = data_nasc[2];

    temp.existe = 1;
    printf("%s foi inserido sistema com sucesso. \n", temp.nome);
    push_pessoas(&temp);
    modificado = 1;


}

// Show uf
void mostrar_pessoa()
{if (ppe == NULL) {
    printf("Nao ha pessoas a serem exibidas. \n");
    return;
}
    if (!(buscar_existenciap())) {
        printf("Nao existem pessoas a serem exibidas. \n");
        return;
    }
    char cpf[12];
    printf("Digite o CPF da pessoa desejada: \n");
    fgets(cpf, sizeof(cpf), stdin);
    int flag = 0;


    for (int i = 0; i <= num_pes; i++)
    {
        if (strcmp(cpf, ppe[i].CPF) == 0){
            if (ppe[i].existe == 0) {
                printf("Essa pessoa não existe mais. \n");
                return;
            }
            flag = 1;
            printf("Nome            : %s \n", ppe[i].nome);
            printf("CPF             : %s \n", ppe[i].CPF);
            printf("Data_nascimento : %d/%d/%d\n", ppe[i].data_nascimento[0], ppe[i].data_nascimento[1], ppe[i].data_nascimento[2]);
            printf("Titulo          : %s \n", ppe[i].titulo);
            printf("Telefone        : %s \n", ppe[i].telefone);
            printf("Endereco        : %s \n \n", ppe[i].endereco);
            break;
        }
    }
    if (flag == 0)
        printf("Pessoa nao encontrada. \n");
}
void mostrartodos_pessoas() {
    if (ppe == NULL) {
        printf("Nao ha pessoas a serem exibidas. \n");
        return;
    }
    if (!(buscar_existenciap())) {
        printf("Nao existem pessoas a serem exibidas. \n");
        return;
    }
    else {
        for (int i = 0; i < num_pes; i++) {
            if (ppe[i].existe == 0)
                continue;
            printf("Nome            : %s \n", ppe[i].nome);
            printf("CPF             : %s \n", ppe[i].CPF);
            printf("Data_nascimento : %d/%d/%d\n", ppe[i].data_nascimento[0], ppe[i].data_nascimento[1], ppe[i].data_nascimento[2]);
            printf("Titulo          : %s \n", ppe[i].titulo);
            printf("Telefone        : %s \n", ppe[i].telefone);
            printf("Endereco        : %s \n", ppe[i].endereco);
        }


    }
}

// Delete
void excluir_pessoa() {
    if (ppe == NULL) {
        printf("Nao ha pessoas a serem excluidas. \n");
        return;
    }
    if (!(buscar_existenciap())) {
        printf("Nao existem pessoas a serem excluidas. \n");
        return;
    }
    char cpf[12];
    printf("Digite o CPF da pessoa que deseja excluir: \n");
    fgets(cpf, sizeof(cpf), stdin);
    int flag = 0;


    for (int i = 0; i <= num_pes; i++)
    {
        if (strcmp(cpf, ppe[i].CPF) == 0){
            if (ppe[i].existe == 0) {
                printf("Essa pessoa não existe mais. \n");
                return;
            }
            flag = 1;
            ppe[i].existe = 0;
            printf("%s foi removido do sistema com sucesso. \n", ppe[i].nome);
            modificado = 1;
            break;
        }
    }
    if (flag == 0)
        printf("Pessoa nao encontrada. \n");
}

// Update
void alterar_pessoa() {
    if (ppe == NULL) {
        printf("Nao ha pessoas a serem alteradas. \n");
        return;
    }
    if (!(buscar_existenciap())) {
        printf("Nao existem pessoas a serem alteradas. \n");
        return;
    }
    char cpf[12];
    printf("Digite o CPF da pessoa que deseja alterar: \n");
    fgets(cpf, sizeof(cpf), stdin);
    faxineirojp();
    int flag = 0;

    int valido;

    for (int i = 0; i <= num_pes; i++)
    {
        if (strcmp(cpf, ppe[i].CPF) == 0){
            if (ppe[i].existe == 0) {
                printf("Essa pessoa não existe mais. \n");
                return;
            }
            flag = 1;
            char nom[255];

            do {
                valido = 1;  // Começa assumindo que a entrada é válida
                int tem_letra = 0;  // Para garantir que há pelo menos uma letra

                printf("Insira o novo nome: \n");
                fgets(nom, sizeof(nom), stdin);
                nom[strcspn(nom, "\n")] = '\0';  // Remove o '\n' do final da entrada

                // Verifica caractere por caractere
                for (int i = 0; nom[i] != '\0'; i++) {
                    if (isalpha(nom[i])) {
                        tem_letra = 1;  // Pelo menos uma letra foi encontrada
                    } else if (nom[i] != ' ') {
                        valido = 0;  // Encontrou algo que não é letra nem espaço
                        break;
                    }
                }

                // Verifica se há ao menos uma letra e se os caracteres são válidos
                if (!valido || !tem_letra) {
                    printf("Entrada invalida! Digite apenas letras e espaços (sem números ou símbolos).\n");
                    valido = 0;
                }

            } while (!valido);

            //telefone
            char fone[14];
            do {
                valido = 1;

                printf("Insira o telefone (formato: xx9xxxxxxxx): \n");
                fgets(fone, sizeof(fone), stdin);
                fone[strcspn(fone, "\n")] = '\0';  // Remove o '\n'
                faxineirojp();
                if (strlen(fone) > 0) {
                    // Verifica cada caractere
                    for (int i = 0; i < 13; i++) {
                        valido = 0;
                        break;
                        if (!isdigit(fone[i])) {
                            valido = 0;
                            break;
                        }
                    }
                }

                if (valido != 1) {
                    printf("Telefone invalido! Use o formato: xx9xxxxxxxx (somente numeros e 1 espaco apos o DDD).\n");
                }

            } while (!valido);

            //endereço
            char endere[255];
            printf("Insira o novo endereco \n");
            fgets(endere, sizeof(endere), stdin);
            endere[strcspn(endere, "\n")] = '\0';

            // Dá push na nova pessoa
            strcpy(ppe[i].telefone, fone);
            strcpy(ppe[i].endereco, endere);
            strcpy(ppe[i].nome, nom);
            printf("%s foi alterado no sistema com sucesso. \n", ppe[i].nome);
            modificado = 1;
            break;
        }
    }
    if (flag == 0)
        printf("Pessoa nao encontrada. \n");
}

// Utils
int buscar_cpf(char cpf[12])
{
    for (int i = 0; i < num_pes; i++){
    int count = 0;
    for (int j = 0; j < strlen(ppe[i].CPF); j++) {
        if (ppe[i].CPF[j] == cpf[j]) {
            ++count;
            if (count == 11)
                return 1;
        }
    }
}
    return 0;
}


int buscar_existenciap() {
    for (int i = 0; i < num_pes; i++)
    {
        if (ppe[i].existe == 1)
        {
            return 1;
        }

    }
    return 0;
}
int buscar_titulo(char tit_ele[14]) {
    for (int i = 0; i < num_pes; i++)
    {
        int count = 0;
        for (int j = 0; j < strlen(ppe[i].titulo); j++) {
            if (ppe[i].titulo[j] == tit_ele[j]) {
                ++count;
                if (count == 13)
                    return 1;
            }
        }
    }
    return 0;
}
