#include <string.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include "registros.h"


int main()
{
	
	FILE *arquivo;

	if ((arquivo = fopen("dados.dat", "rb+")) == NULL)
	{
		if ((arquivo = fopen("dados.dat", "wb+")) == NULL)
		{
			printf(" Arquivo txt não pode ser aberto!\n");
			return 1;
		}
	}

	menuOpcao(arquivo);
	
	
	return 0;
} 

void menuOpcao(FILE *arquivo)
{
	int menu;
	
	do{
		system("CLS"); 
		printf("============ Registro de Filme ==========\n");
		printf("1.Cadastrar Filme \n");
		printf("2.Consultar todos os Filmes\n");
		printf("3.Consultar Filmes por codigo de Cadastro\n");
		printf("4.Gerar arquivo dos filmes em TXT\n");
		printf("5.Excluir cadastro\n");
		printf("6.Sair\n");
		printf("=================================\n");
		printf("Opcao: ");
		scanf("%d%*c", &menu);
		
		switch (menu)
		{
		case 1: 
			cadastrarFilme(arquivo);
			break;
		case 2:
			consultarListaFilmes(arquivo);
			break;
		case 3: 
			consultarFilmeCodigo(arquivo);
			break;
		case 4:
			criarArquivoTXT(arquivo);
			break;
		case 5:
			excluirCadastro(arquivo);
			break;
		default:
			printf("Pesquisa Finalizada! \n");
			fclose(arquivo);		  
		}
	}while(menu != 6);	
}


int tamanho(FILE *arquivo)
{
	fseek(arquivo, 0, SEEK_END);
	return ftell(arquivo) / sizeof(Cadastrar);
}


void criarArquivoTXT(FILE *arquivo){
	
	char nomeArquivo[10];
	
	printf("Digite o nome do arquivo: ");
	scanf("%s", nomeArquivo);
	
	strcat(nomeArquivo,".txt");

	FILE *arquivoTXT = fopen(nomeArquivo, "w");  //abrir arquivo
    
	
	if (arquivoTXT == NULL){
		
		printf("Problemas na criacao do arquivo! \n");
		return;
	}
	
	fprintf(arquivoTXT,"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	fprintf(arquivoTXT, "                       ----------------------- LISTA DOS FILMES ----------------------- \n\n");
	
	int i;

	for(i = 0; i < tamanho(arquivo); i++){
		
		fseek(arquivo, i * sizeof(Cadastrar), SEEK_SET); //set parte inicio do arquivo 
		fread(&cadastro, sizeof(Cadastrar), 1, arquivo);
		
		fprintf(arquivoTXT, "Filme.............: %s\n" , cadastro.filme);
		fprintf(arquivoTXT, "Codigo............: %d \n", cadastro.codigo);
		fprintf(arquivoTXT, "Genero............: %s \n", cadastro.genero);
		fprintf(arquivoTXT, "Ano...............: %d \n", cadastro.ano);
		fprintf(arquivoTXT, "Diretor...........: %s \n", cadastro.diretor);
		fprintf(arquivoTXT, "Editora...........: %s \n", cadastro.editora);
		fprintf(arquivoTXT, "---------------------------------------------------------------------\n");
			
	}
	fprintf(arquivoTXT,"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	fclose(arquivoTXT);
}


void cadastrarFilme(FILE *arquivo){
	
	char confirma;
	fflush(stdin);

	printf("--------------+ Agendamento da Reserva +-------------- \n");
	printf("Numero da reserva: %d\n\n", tamanho(arquivo) + 1);
	
	printf("Filme................: ");
	gets(cadastro.filme);
	printf("Codigo...............: ");
	scanf("%d%*c", &cadastro.codigo);
	printf("Genero...............: ");
	gets(cadastro.genero);
	printf("Ano..................: ");
	scanf("%d%*c", &cadastro.ano);
	printf("Diretor..............: ");
	gets(cadastro.diretor);
	printf("Editora..............: ");
	gets(cadastro.editora);
	printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
	
	printf("Confirma a reserva [S|N]: ");
	scanf("%c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("Salvando reserva...\n\n");
		fseek(arquivo, 0, SEEK_END); //end parte final do arquivo
		fwrite(&cadastro, sizeof(Cadastrar), 1, arquivo);
		printf("Reserva concluida com sucesso! \n");
	}
	system("pause");
}

void consultarListaFilmes(FILE *arquivo){
	int i;
	
	printf("--------------+ LISTA DOS FILMES +-------------- \n");
	for(i = 0; i < tamanho(arquivo); i++)
	{	
		fseek(arquivo, i * sizeof(Cadastrar),SEEK_SET);
		fread(&cadastro, sizeof(Cadastrar), 1, arquivo);
			
		printf("Numero da Lista...: (%d)\n", i + 1);
		printf("Codigo............: %d \n", cadastro.codigo);
		printf("Filme.............: %s\n" , cadastro.filme);
		printf("Genero............: %s \n", cadastro.genero);
		printf("Ano...............: %d \n", cadastro.ano);
		printf("Diretor...........: %s \n", cadastro.diretor);
		printf("Editora...........: %s \n", cadastro.editora);
		printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
	}
	system("pause");
}

void consultarFilmeCodigo(FILE *arquivo){
	
	int numero;
	
	printf("----------+ Consulte pelo codigo da reserva +----------\n ");
	printf("Informe o codigo da reserva: ");
	scanf("%d", &numero);
	
	if((numero <= tamanho(arquivo)) && (numero > 0))
	{
		fseek(arquivo, (numero - 1) * sizeof(Cadastrar), SEEK_SET);
		fread(&cadastro, sizeof(Cadastrar), 1, arquivo);

		printf("--------------+ FILME (%d) +-------------- \n", numero);
		printf("Reserva...........: %d \n", numero);
		printf("Codigo............: %d \n", cadastro.codigo);
		printf("Filme.............: %s\n" , cadastro.filme);
		printf("Genero............: %s \n", cadastro.genero);
		printf("Ano...............: %d \n", cadastro.ano);
		printf("Diretor...........: %s \n", cadastro.diretor);
		printf("Editora...........: %s \n", cadastro.editora);
		printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");
	}else{
		printf("Numero da reserva invalido! \n");
	}
	system("pause");
}

void excluirCadastro(FILE *arquivo)
{
	char confirma;
	int nr;

	printf("\nInforme o codigo da reserva para excluir\n");
	scanf("%d", &nr);
	
	if ((nr <= tamanho(arquivo)) && (nr > 0))
	{
		fseek(arquivo, (nr - 1) * sizeof(Cadastrar), SEEK_SET);
		fread(&cadastro, sizeof(Cadastrar), 1, arquivo);
		
		printf("Filme........:%s \n", cadastro.filme);
		printf("Codigo....:%d \n", cadastro.codigo);
		printf("Genero......:%s \n", cadastro.genero);
			
		printf("\nConfirma excluir essa reserva: [S|N] ");
		//getchar();
		scanf(" %c", &confirma);

		if (toupper(confirma) == 'S')
		{
			printf("excluindo reserva...\n\n");
			fseek(arquivo, (nr - 1) * sizeof(Cadastrar), SEEK_SET);
			fwrite(&cadastro, sizeof(Cadastrar), 1, arquivo);
		}
	}else{
		printf("\nNumero de reserva invalido!\n");
	}
	system("pause");
}

