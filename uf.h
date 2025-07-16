typedef struct {
    int codigo;
    char descricao[100];
    char sigla[3];
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
int vercod();
int buscar_codigo(int cod);
