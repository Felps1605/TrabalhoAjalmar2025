
#ifndef CANDIDATOS_H
#define CANDIDATOS_H




typedef struct {
    int codigoUF; //importado da UF e juntamente com o ano vai ser a chave primária
    char descricao[100];
    char CPF[12];
    int ano;
    int numero;
    unsigned int existe : 1;
} candidato;

// Funções

// Menu
void candidatos();
void menu_candidatos();

void carregar_candidatos();
void push_candidatos();
void salvar_candidatos();

void inserir_candidato();
void excluir_candidato();
void mostrartodos_candidatos();
void mostrartodos_candidatos_por_ano();
void mostrar_candidato_por_eleicao();

int buscar_candidato(int codigouf, int ano);
int buscar_existencia_candidatos();
int buscar_numero(int num);
int buscar_cpf_por_ano(char cpf[12], int ano);
#endif //CANDIDATOS_H
