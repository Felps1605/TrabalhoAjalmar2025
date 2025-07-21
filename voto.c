#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eleicoes.h"
#include "uf.h"
#include "candidatos.h"
#include "pessoas.h"
#include "votos.h"

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
//            case 2: listar_votos_por_candidato(); break;
            case 3: listar_votos_por_ano(); break;
            case 4: mostrar_comparecimento_por_eleicao(); break;
//            case 5: mostrar_comparecimento_por_ano(); break;
            case 0: salvar_votos(); break;
        }
    } while (op != 0);
}

// Menu de votos
void menu_voto() {
    load_votos();
    printf("|============================================|\n");
    printf("| 1- INSERIR                                 |\n");
    printf("| 2- LISTAR VOTOS POR ELEICAO                |\n");
    printf("| 3- LISTAR VOTOS POR ANO                    |\n");
    printf("| 4- MOSTRAR COMPARECIMENTO POR ELEICAO      |\n");
    printf("| 5- MOSTRAR COMPARECIMENTO POR ANO          |\n");
    printf("| 0- SAIR                                    |\n");
    printf("|============================================|\n");
}


// Valida os dados do voto verificando a existência dos dados relacionados
int validar_dados_voto(int ano, int codUF, char cpf[]) {
    if (buscar_eleicao(codUF, ano) < 0) return 0;
    if (buscar_codigo(codUF) < 0) return 0;
    if (buscar_cpf_por_ano(cpf, ano) < 0) return 0;
    return 1;
}

// Carrega votos do arquivo
void load_votos() {
    FILE *f = fopen(ARQ_VOTOS, "rb");
    if (!f) return;

    voto temp;
    while (fread(&temp, sizeof(voto), 1, f) == 1) {
        push_voto(temp);
    }
    fclose(f);
}

// Insere voto no vetor com realocação dinâmica
void push_voto(voto novo) {
    if (num_vot >= capacidadeVotos) {
        capacidadeVotos = (capacidadeVotos == 0) ? 10 : capacidadeVotos + 10;
        voto *temp = realloc(pvo, sizeof(voto) * capacidadeVotos);
        if (!temp) {
            printf("Erro ao alocar memória para votos.\n");
            return;
        }
        pvo = temp;
    }
    pvo[num_vot++] = novo;
}

// Inserção de novo voto
void inserir_voto() {
    voto v;
    int ano;
    int cod;
    int num_candidato;
    char data;
    printf("Ano da eleição: \n");
    scanf("%d", &ano);
    faxineirojp();

    printf("Código da UF: \n");
    scanf("%d", &cod);
    faxineirojp();

    printf("Número do candidato: \n");
    scanf("%d", &num_candidato);
    faxineirojp();

    printf("Data e hora (DD/MM/AAAA HH:MM): \n");
    fgets(data, sizeof(char), stdin);
    v.data_hora[strcspn(v.data_hora, "\n")] = '\0';

    if (!validar_dados_voto(v.ano, v.codigo_UF, v.numero_candidato)) {
        printf("Dados inválidos!\n");
        return;
    }
}

/*void push_candidatos(const candidato *pushedcandidato) {
    // Verifica se o vetor (pca) tem capacidade para mais um elemento
    if (num_can >= capacidade_ca) {
        // Adiciona mais 10 espaços no vetor realocando a memória
        capacidade_ca = (capacidade_ca == 0 ? 10 : capacidade_ca + 10);
        pca = (candidato *)realloc(pca, sizeof(candidato) * capacidade_ca);
        if (!pca) return;
    }

    // Coloca o novo candidato no primeiro espaço vago no vetor
    pca[num_can++] = *pushedcandidato;
}*/

// Comparador por UF para qsort
int compararVotosPorUF(const void *a, const void *b) {
    const voto *v1 = (const voto *)a;
    const voto *v2 = (const voto *)b;
    return v1->codigo_UF - v2->codigo_UF;
}

// Lista todos os votos de um ano, ordenando por UF
void listar_votos_por_ano() {
    int ano;
    printf("Digite o ano da eleição: ");
    scanf("%d", &ano);
    getchar();

    int encontrados = 0;
    voto *filtro = malloc(num_vot * sizeof(voto));
    if (!filtro) {
        printf("Erro ao alocar memória.\n");
        return;
    }

    for (int i = 0; i < num_vot; i++) {
        if (pvo[i].ano == ano) {
            filtro[encontrados++] = pvo[i];
        }
    }

    qsort(filtro, encontrados, sizeof(votos), compararVotosPorUF);

    for (int i = 0; i < encontrados; i++) {
        printf("UF: %d | Candidato: %d | CPF: %s | Data/Hora: %s\n",
               filtro[i].codigo_UF,
               filtro[i].numero_candidato,
               filtro[i].data_hora);
    }

    free(filtro);
}

// Mostra número total de comparecimentos por UF em um determinado ano
void mostrar_comparecimento_por_eleicao() {
    int ano, codUF, total = 0;
    printf("Ano: ");
    scanf("%d", &ano);
    printf("Código UF: ");
    scanf("%d", &codUF);
    getchar();

    for (int i = 0; i < num_vot; i++) {
        if (pvo[i].ano == ano && pvo[i].codigo_UF == codUF) {
            total++;
        }
    }

    printf("Comparecimento total na UF %d no ano %d: %d votos\n", codUF, ano, total);
}

// Salva todos os votos em arquivo (sobrescreve)
void salvar_candidatos()
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



