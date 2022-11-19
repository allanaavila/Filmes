
struct Cadastrar
{
	char filme[40];
	char diretor[40];    
	int codigo[11];
	char editora[40];
	char genero[40];
	int ano[4];
}cadastro;


int tamanho(FILE *arquivo);
void cadastrarFilme(FILE *arquivo);
void consultarListaFilmes(FILE *arquivo);
void consultarFilmeCodigo(FILE *arquivo);
void criarArquivoTXT(FILE *arquivo);
void excluirCadastro(FILE *arquivo);
void menuOpcao(FILE *arquivo);

