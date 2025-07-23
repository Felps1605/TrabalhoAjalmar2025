#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eleicoes.h"
#include "uf.h"
#include "candidatos.h"
#include "pessoas.h"
#include "votos.h"
#include "comparecimentos.h"

#define ARQ_VOTOS "votos.data"

voto *pvo = NULL;
int num_vot = 0;
int capacidadeVotos = 0;

void votos() {
    int op;
    do {
        menu_voto();
        scanf("%d", &op);
        faxineirojp();
        switch (op) {
            case 1: inserir_voto(); break;
            case 2: listar_votos_por_candidato(); break;
            case 3: listar_votos_por_ano(); break;
            case 4: mostrar_comparecimento_por_eleicao(); break;
            case 5: mostrar_comparecimento_por_ano(); break;
            case 0: salvar_votos(); salvar_comparecimentos(); break;
            default: printf("Opcao invalida. \n"); break;
        }
    } while (op != 0);
}

// Menu de votos
void menu_voto() {
    printf("|============================================|\n");
    printf("| 1- INSERIR                                 |\n");
    printf("| 2- LISTAR VOTOS POR CANDIDATO/ELEICAO      |\n");
    printf("| 3- LISTAR VOTOS POR ANO                    |\n");
    printf("| 4- MOSTRAR COMPARECIMENTO POR ELEICAO      |\n");
    printf("| 5- MOSTRAR COMPARECIMENTO POR ANO          |\n");
    printf("| 0- SAIR                                    |\n");
    printf("|============================================|\n");
}



// Carrega votos do arquivo
void load_votos() {
    FILE *f = fopen(ARQ_VOTOS, "rb");
    if (!f)
        return;

    voto temp;
    while (fread(&temp, sizeof(voto), 1, f) == 1) {
        push_voto(temp);
    }
    fclose(f);
}

// Insere voto no vetor com realocação dinâmica
void push_voto(const voto *pushedvoto) {
    // Verifica se o vetor (pvo) tem capacidade para mais um elemento
    if (num_vot >= capacidadeVotos) {
        // Adiciona mais 10 espaços no vetor realocando a memória
        capacidadeVotos = (capacidadeVotos == 0 ? 10 : capacidadeVotos + 10);
        pvo = (voto *)realloc(pvo, sizeof(voto) * capacidadeVotos);
        if (!pvo) return;
    }

    // Coloca o novo uf no primeiro espaço vago no vetor
    pvo[num_vot++] = *pushedvoto;
}

// Inserção de novo voto
void inserir_voto() {
    voto temp;
    int ano;
    int cod;
    int num_candidato;
    char data[20];
    char titulo[14];

    comparecimento comp;

    printf("Insira o titulo do eleitor: ");
    fgets(titulo, 14, stdin);
    faxineirojp();
    titulo[strcspn(titulo, "\n")] = '\0';

    printf("Ano da eleicao: ");
    scanf("%d", &ano);
    faxineirojp();

    printf("Codigo da UF: ");
    scanf("%d", &cod);
    faxineirojp();

    printf("Numero do candidato: ");
    scanf("%d", &num_candidato);
    faxineirojp();

    printf("Data e hora (DD/MM/AAAA HH:MM): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';

    if (!validar_dados_voto(ano, cod, num_candidato, titulo)) {
        printf("Dados inválidos!\n");
        return;
    }

        temp.ano = ano;
        temp.codigo_UF = cod;
        temp.numero_candidato = num_candidato;
        strcpy(temp.data_hora, data);
        push_voto(&temp);

        comp.codigo_UF = cod;
        comp.ano = ano;
        strcpy(comp.titulo, titulo );
        push_comparecimentos(&comp);
        printf("Voto registrado com sucesso!\n");
}
// Valida os dados do voto verificando a existência dos dados relacionados
int validar_dados_voto(int ano, int cod, int num_candidato, char titulo[14]) {
    if (buscar_titulo(titulo)== -1){
        printf("Eleitor nao encontrado. \n");
        return 0;
    }
    if (ppe[buscar_titulo(titulo)].existe == 0) {
        printf("Eleitor nao encontrado*. \n");
        return 0;
    }
    if (buscar_codigo(cod)== -1) {
        printf("UF nao encontrada.\n");
        return 0;
    }
    if (puf[buscar_codigo(cod)].existe == 0) {
        printf("UF nao encontrada*.\n");
        return 0;
    }
    if (buscar_eleicao(cod, ano)== -1){
        printf("Eleicao nao encontrada. \n");
        return 0;
    }
    if (pel[buscar_eleicao(cod, ano)].existe == 0) {
        printf("Eleicao nao encontrada*. \n");
        return 0;
    }
    if (buscar_numero(num_candidato)== -1) {
        printf("Candidato nao encontrado. \n");
        return 0;
    }
    if (pca[buscar_numero(num_candidato)].existe == 0) {
        printf("Candidato nao encontrado*. \n");
        return 0;
    }
    if (buscar_titulo_no_ano(titulo, ano) != -1) {
         printf("%s ja votou nesse ano. \n", ppe[buscar_titulo(titulo)].nome);
        return 0;
    }
    return 1;
}

void listar_votos_por_candidato() {
    int ano, flag = 0;
    printf("Digite o ano das eleicoes: ");
    scanf("%d", &ano);
    faxineirojp();

    int cod;
    printf("Codigo da UF: ");
    scanf("%d", &cod);
    faxineirojp();

    int num_candidato;
    printf("Numero do candidato: ");
    scanf("%d", &num_candidato);
    faxineirojp();

        if (buscar_codigo(cod)== -1) {
            printf("UF nao encontrada.\n");
            return ;
        }
        if (puf[buscar_codigo(cod)].existe == 0) {
            printf("UF nao encontrada*.\n");
            return ;
        }
        if (buscar_eleicao(cod, ano)== -1){
            printf("Eleicao nao encontrada. \n");
            return ;
        }
        if (pel[buscar_eleicao(cod, ano)].existe == 0) {
            printf("Eleicao nao encontrada*. \n");
            return ;
        }
        if (buscar_numero(num_candidato)== -1) {
            printf("Candidato nao encontrado. \n");
            return ;
        }
        if (pca[buscar_numero(num_candidato)].existe == 0) {
            printf("Candidato nao encontrado*. \n");
            return ;
        }
    for (int i = 0; i < num_candidato; i++) {
        if (pvo[i].ano == ano && pvo[i].numero_candidato == num_candidato) {
            printf("CodigoUF:            %d \n", pvo[i].codigo_UF);
            printf("Numero do candidato: %d \n", pvo[i].numero_candidato);
            printf("Data e hora:         %s \n", pvo[i].data_hora);
            flag = 1;
        }
    }if (flag == 0)
        printf("Esse candidato nao recebeu votos nessa eleicao. \n");
}
// Lista todos os votos de um ano, ordenando por UF
void listar_votos_por_ano() {
    int ano, flag = 0;
    printf("Digite o ano das eleicoes: ");
    scanf("%d", &ano);
    faxineirojp();

    for (int i = 0; i < num_vot; i++) {
        if (pvo[i].ano == ano) {
            printf("CodigoUF:            %d \n", pvo[i].codigo_UF);
            printf("Numero do candidato: %d \n", pvo[i].numero_candidato);
            printf("Data e hora:         %s \n", pvo[i].data_hora);
            flag = 1;
        }

    }
    if (flag == 0) {
        printf("Nao houve votos nesse ano. \n");
    }
}


// Salva todos os votos em arquivo (sobrescreve)
void salvar_votos()
{
    FILE *f = fopen(ARQ_VOTOS, "wb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo VOTOS\n");
        return;
    }
    fwrite(pvo, sizeof(voto), num_vot, f);
    fclose(f);
    printf("Alteracoes salvas com sucesso! \n");

}
