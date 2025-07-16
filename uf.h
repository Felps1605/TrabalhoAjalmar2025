struct UF {
    int codigo;
    char descricao[100];
    char sigla[3];
};
typedef struct UF uf;
void inserir();
void alterar();
void excluir();
void mostrartodos();
void mostraruf();
void estados();
void menuuf();
void faxineirojp();
int vercod();
void comecar();
uf* reallocu();
int buscar_codigo(int cod);
