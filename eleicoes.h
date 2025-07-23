
typedef struct {
    int codigoUF; //importado da UF e juntamente com o ano vai ser a chave primária
    char descricao[100];
    int ano;
    unsigned int existe : 1;
} eleicao;

extern eleicao *pel;
// Funções

typedef enum {
    SAIR_ELEICAO = 0,
    INSERIR_ELEICAO = 1,
    ALTERAR_ELEICAO = 2,
    EXCLUIR_ELEICAO = 3,
    MOSTRAR_TODAS_ELEICOES = 4,
    MOSTRAR_ELEICAO = 5
} OpcaoEleicao;

// Menu
void eleicoes();
void menu_eleicao();

void carregar_eleicoes();
void push_eleicoes();
void salvar_eleicoes();

void inserir_eleicao();
void alterar_eleicao();
void excluir_eleicao();
void mostrartodos_eleicoes();
void mostrar_eleicao();
void faxineirojpe();
int buscar_eleicao(int codigouf, int ano);
int buscar_existencia_eleicao();
