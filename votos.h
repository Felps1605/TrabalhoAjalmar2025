
#ifndef VOTOS_H
#define VOTOS_H



typedef struct {
    int ano;
    int codigo_UF;
    int numero_candidato;
    char data_hora[20];
}voto;

typedef enum {
    SAIR_VOTO = 0,
    INSERIR_VOTO = 1,
    LISTAR_VOTOS_POR_CANDIDATO = 2,
    LISTAR_VOTOS_POR_ANO = 3,
    MOSTRAR_COMPARECIMENTO_POR_ELEICAO = 4,
    MOSTRAR_COMPARECIMENTO_POR_ANO = 5
} OpcaoVoto;

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
