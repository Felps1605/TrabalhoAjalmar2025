typedef struct {
    char titulo[14]; //primary key
    char nome[255];
    unsigned long int telefone;
    char endereco[255];
    int data_nascimento[3]; //dia mes e ano, faz a matematica multiplicando
    char CPF[12]; //key
    unsigned int existe : 1;
} pessoa;

extern pessoa *ppe;
// Funções

typedef enum {
    SAIR_PESSOA = 0,
    INSERIR_PESSOA = 1,
    ALTERAR_PESSOA = 2,
    EXCLUIR_PESSOA = 3,
    MOSTRAR_TODAS_PESSOAS = 4,
    MOSTRAR_PESSOA = 5
} OpcaoPessoa;

// Menu
void pessoas();
void menupessoas();

void carregar_pessoas();
void push_pessoas();
void salvar_pessoas();

void inserir_pessoa();
void alterar_pessoa();
void excluir_pessoa();
void mostrartodos_pessoas();
void mostrar_pessoa();
void faxineirojpp();
int buscar_cpf(char cpf[12]);
int buscar_existenciap();
int buscar_titulo();
