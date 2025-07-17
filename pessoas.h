typedef struct {
    char titulo[14]; //primary key
    char nome[255];
    unsigned long int telefone;
    char endereco[255];
    int data_nascimento[3]; //dia mes e ano, faz a matematica multiplicando
    char CPF[12]; //key
    int existe;
} pessoa;

// Funções

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