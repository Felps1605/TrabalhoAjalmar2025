

#ifndef VOTOS_H
#define VOTOS_H



typedef struct {
    int ano;
    int codigo_UF;
    int numero_candidato;
    char data_hora[20];
}voto;
extern voto *pvo;
void votos();
void menu_voto();

void load_votos();
void push_voto();
void salvar_votos();

void inserir_voto();
void listar_votos_por_ano();
void listar_votos_por_candidato();

int validar_dados_voto();
#endif //VOTOS_H
