
struct Cadastrar
{
	char filme[30];
	char diretor[20];    
	char codigo[10];
	char editora[20];
	char genero[10];
	char ano[4];
	char status;
	int id;
}cadastro;


int tamanho(FILE *arquivo);
void cadastrarFilme(FILE *arquivo);
void consultarListaFilmes(FILE *arquivo);
void consultarFilmeCodigo(FILE *arquivo);
void criarArquivoTXT(FILE *arquivo);
void excluirCadastro(FILE *arquivo);
void menuOpcao(FILE *arquivo);

