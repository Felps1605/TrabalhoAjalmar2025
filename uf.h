typedef struct {
    int codigo;
    char descricao[100];
    char sigla[3];
    unsigned int existe: 1;
} uf;

// Funções

// Menu
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
