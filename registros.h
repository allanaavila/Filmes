
struct Cadastrar
{
	char filme[40];
	char diretor[40];    
	char codigo[30];
	char assistir[30];
	char genero[30];
	char ano[10];
	char status;
	int id;
}cadastro;

void abertura();
int tamanho(FILE *arquivo);
void cadastrarFilme(FILE *arquivo);
void consultarListaFilmes(FILE *arquivo);
void consultarFilmeCodigo(FILE *arquivo);
void criarArquivoTXT(FILE *arquivo);
void excluirCadastro(FILE *arquivo);
void menuOpcao(FILE *arquivo);

