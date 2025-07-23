#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "eleicoes.h"
#include "uf.h"
#include "candidatos.h"
#include "pessoas.h"
#include "votos.h"
#include "comparecimentos.h"

#define FILENAME "comparecimentos.data"

comparecimento *pco = NULL;
int num_com = 0;
int capacidade_com = 0;

void comparecimentos() {

}
// Carrega votos do arquivo
void load_comparecimentos() {
    FILE *f = fopen(FILENAME, "rb");
    if (!f)
        return;

    comparecimento temp;
    while (fread(&temp, sizeof(comparecimento), 1, f) == 1) {
        push_comparecimentos(temp);
    }
    fclose(f);
}

// Insere comparecimento no vetor com realocação dinâmica
void push_comparecimentos(const comparecimento *pushedecomparecimento) {
    // Verifica se o vetor (pco) tem capacidade para mais um elemento
    if (num_com >= capacidade_com) {
        // Adiciona mais 10 espaços no vetor realocando a memória
        capacidade_com = (capacidade_com == 0 ? 10 : capacidade_com + 10);
        pco = (comparecimento *)realloc(pco, sizeof(comparecimento) * capacidade_com);
        if (!pco) return;
    }

    // Coloca o novo uf no primeiro espaço vago no vetor
    pco[num_com++] = *pushedecomparecimento;
}
void salvar_comparecimentos()
{
    FILE *f = fopen(FILENAME, "wb");
    if (f == NULL) {
        printf("Erro ao abrir o arquivo comparecimentos.data\n");
        return;
    }
    fwrite(pco, sizeof(comparecimento), num_com, f);
    fclose(f);
    printf("Alteracoes salvas com sucesso! \n");
    free(pco);
}

void mostrar_comparecimento_por_eleicao() {
    int ano, codUF, total = 0;
    printf("Ano: ");
    scanf("%d", &ano);
    faxineirojp();
    printf("Codigo UF: ");
    scanf("%d", &codUF);
    faxineirojp();

    if (buscar_eleicao(codUF, ano)== -1){
        printf("Eleicao nao encontrada. \n");
        return ;
    }
    if (pel[buscar_eleicao(codUF, ano)].existe == 0) {
        printf("Eleicao nao encontrada*. \n");
        return ;
    }

    for (int i = 0; i < num_com; i++) {
        if (pco[i].ano == ano && pco[i].codigo_UF == codUF) {
            total++;
        }
    }

    printf("Comparecimento total na UF %d no ano %d: %d votos.\n", codUF, ano, total);
}
void mostrar_comparecimento_por_ano() {
    int ano, total = 0, flag = 0;
    printf("Ano: ");
    scanf("%d", &ano);
    faxineirojp();

    for (int i = 0; i < num_com; i++) {
        if (pco[i].ano == ano ) {
            total++;
            flag++;
        }
    }
    if (flag == 0) {
        printf("Nao houve eleicoes nesse ano. \n");
        return ;
    }
    printf("Comparecimento total no ano %d: %d votos.\n", ano, total);
}
