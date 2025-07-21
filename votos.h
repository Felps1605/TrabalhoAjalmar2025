


typedef struct {
    int ano;
    int codigo_UF;
    int numero_candidato;
    char data_hora[20];
} voto;
typedef struct {
   char titulo[14];
}comparecimento;

void votos();
void menu_voto();

void load_votos();
void push_voto();
void salvar_votos();

void inserir_voto();
void listar_votos_por_ano();
void listar_votos_por_candidato();
void mostrar_comparecimento_por_eleicao();
void mostrar_comparecimento_por_ano();
