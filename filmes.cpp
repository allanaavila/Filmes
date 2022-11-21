#include <string.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include<locale.h>
#include "registros.h"


int main()
{
	setlocale(LC_ALL, "Portuguese");
	
	FILE *arquivo;

	if ((arquivo = fopen("dados.dat", "rb+")) == NULL)
	{
		if ((arquivo = fopen("dados.dat", "wb+")) == NULL)
		{
			printf(" Arquivo txt não pode ser aberto!\n");
			system("pause");
		}
	}

	menuOpcao(arquivo);
	
	
	return 1;
} 

void menuOpcao(FILE *arquivo)
{
	int menu;
	
	do{
		system("CLS"); 
		printf("============ Registro de Filme ==========\n");
		printf("1. Cadastrar Filme \n");
		printf("2. Consultar todos os Filmes\n");
		printf("3. Consultar Filmes por codigo de Cadastro\n");
		printf("4. Gerar arquivo dos filmes em TXT\n");
		printf("5. Excluir cadastro\n");
		printf("6. Finalizar cadastro\n");
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
			printf("Cadastro do filme finalizado! \n");
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
    
	
	if (!arquivoTXT){
		
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
		fprintf(arquivoTXT, "Codigo............: %s \n", cadastro.codigo);
		fprintf(arquivoTXT, "Genero............: %s \n", cadastro.genero);
		fprintf(arquivoTXT, "Ano...............: %s \n", cadastro.ano);
		fprintf(arquivoTXT, "Diretor...........: %s \n", cadastro.diretor);
		fprintf(arquivoTXT, "Editora...........: %s \n", cadastro.editora);
		fprintf(arquivoTXT,  "Status: A = Apagado || C = Cadastrado \n");
		fprintf(arquivoTXT, "Status............: %c \n", cadastro.status);
		fprintf(arquivoTXT, "---------------------------------------------------------------------\n");
			
	}
	fprintf(arquivoTXT,"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	fclose(arquivoTXT);
}


void cadastrarFilme(FILE *arquivo){
	
	char confirma;
	cadastro.status = 'C';
	fflush(stdin);

	printf("--------------+ Cadastro do Filme +-------------- \n");
	printf("ID...................: %d\n\n", tamanho(arquivo) + 1);
	
	printf("Filme................: ");
	fflush(stdin);
	gets(cadastro.filme);
	printf("Codigo...............: ");
	fflush(stdin);
	gets(cadastro.codigo);
	printf("Genero...............: ");
	fflush(stdin);
	gets(cadastro.genero);
	printf("Ano..................: ");
	fflush(stdin);
	gets(cadastro.ano);
	printf("Diretor..............: ");
	fflush(stdin);
	gets(cadastro.diretor);
	printf("Editora..............: ");
	fflush(stdin);
	gets(cadastro.editora);
	printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	
	cadastro.id = tamanho(arquivo) + 1;
	
	printf("Confirma ao cadastro [S|N]: ");
	scanf(" %c", &confirma);

	if (toupper(confirma) == 'S')
	{
		printf("Salvando cadastro do filme...\n\n");
		fseek(arquivo, 0, SEEK_END); //end parte final do arquivo
		fwrite(&cadastro, sizeof(Cadastrar), 1, arquivo);
		printf("Cadastro concluido com sucesso! \n");
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
		
		if(cadastro.status == 'C')
		{
			printf("ID................:(%d)\n", cadastro.id);
			printf("Codigo............: %s \n", cadastro.codigo);
			printf("Filme.............: %s\n" , cadastro.filme);
			printf("Genero............: %s \n", cadastro.genero);
			printf("Ano...............: %s \n", cadastro.ano);
			printf("Diretor...........: %s \n", cadastro.diretor);
			printf("Editora...........: %s \n", cadastro.editora);
			printf("Status: A = Apagado || C = Cadastrado \n");
			printf("Status............: %c \n", cadastro.status);
			printf("\n+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-\n");	
		}	
	}
	system("pause");
}

void consultarFilmeCodigo(FILE *arquivo){
	
	int numero;
	
	printf("Informe o ID do filme para consultar: ");
	scanf("%d", &numero);
	
	if ((numero <= tamanho(arquivo)) && (numero > 0))
	{
		fseek(arquivo, (numero - 1) * sizeof(Cadastrar), SEEK_SET);
		fread(&cadastro, sizeof(Cadastrar), 1, arquivo);
		
		if(cadastro.status == 'C')
		{
			printf("ID................:(%d)\n", cadastro.id);
			printf("Codigo............: %s \n", cadastro.codigo);
			printf("Filme.............: %s\n" , cadastro.filme);
			printf("Genero............: %s \n", cadastro.genero);
			printf("Ano...............: %s \n", cadastro.ano);
			printf("Diretor...........: %s \n", cadastro.diretor);
			printf("Editora...........: %s \n", cadastro.editora);
			printf("Status: A = Apagado || C = Cadastrado \n");
			printf("Status............: %c \n", cadastro.status);
		}
		else
		{
			printf("Esse filme esta indisponivel no cadastro. \n");
		}
		
	}
	else
	{
		printf("ID invalido!\n");
	}
	system("pause");
}

void excluirCadastro(FILE *arquivo)
{
	char confirma;
	int numero;

	printf("\nInforme o Id que deseja excluir:\n");
	fflush(stdin);
	scanf("%d", &numero);
	
	if ((numero <= tamanho(arquivo)) && (numero > 0))
	{
		fseek(arquivo, (numero - 1) * sizeof(Cadastrar), SEEK_SET);
		fread(&cadastro, sizeof(Cadastrar), 1, arquivo);
		fflush(stdin);
		
		if (cadastro.status == 'C')
		{
			printf("Filme........: %s \n", cadastro.filme);
			printf("Codigo.......: %s \n", cadastro.codigo);
			printf("Ano..........: %s \n", cadastro.ano);
			printf("Genero.......: %s \n", cadastro.genero);
			printf("Status: A = Apagado || C = Cadastrado \n");
			printf("Status.......: %c \n", cadastro.status);
			
			printf("Deseja excluir cadastro: [S|N] \n");
			scanf(" %c", &confirma);

			if (toupper(confirma) == 'S')
			{
				printf("analisando solicitacao...\n\n");
				cadastro.status = 'A';
				fseek(arquivo, (numero - 1) * sizeof(Cadastrar), SEEK_SET);
				fwrite(&cadastro, sizeof(Cadastrar), 1, arquivo);
				printf("Cadastro do filme excluido com sucesso! \n");
			}
		}
		else
			printf("Este filme nao esta disponivel no cadastro \n");
	}
	else
	{
		printf("Numero do cadastro invalido!\n");
	}
	system("pause");
}

