
#ifndef COMPARECIMENTOS_H
#define COMPARECIMENTOS_H

typedef struct {
    char titulo[14];
    int ano;
    int codigo_UF;
}comparecimento;
extern comparecimento *pco;
void comparecimentos();

void load_comparecimentos();
void push_comparecimentos();
void salvar_comparecimentos();

void mostrar_comparecimento_por_eleicao();
void mostrar_comparecimento_por_ano();

int buscar_titulo_no_ano();


#endif //COMPARECIMENTOS_H
