
typedef struct {
    int codigo;
    char descricao[100];
    char sigla[3];
    unsigned int existe: 1;
} uf;
extern uf *puf;


typedef enum {
    SAIR = 0,
    INSERIR = 1,
    ALTERAR = 2,
    EXCLUIR = 3,
    MOSTRAR_TODOS = 4,
    MOSTRAR_UF = 5
} OpcaoUF;

void estados();
void menuuf();

void loadUFs();
void pushUF();
void saveUF();

void inserir();
void alterar();
void excluir();
void mostrartodos();
void mostraruf();
void faxineirojp();
int buscar_codigo(int cod);
int buscar_existencia();
int buscar_sigla();
