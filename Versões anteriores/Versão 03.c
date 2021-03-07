/*******************************************************************************
Autor:Uellington Da Conceição Damasceno

Componente Curricular: Algoritmos I

Concluido em: 

Declaro que este código foi elaborado por mim de forma individual e não contém nenhum

trecho de código de outro colega ou de outro autor, tais como provindos de livros e

apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código

de outra autoria que não a minha está destacado com uma citação para o autor e a fonte

do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
******************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

int main(){
	//sessão onde todas as funções utilizadas são informadas para a função prinicipal
	char recebeNome();
	int validacaoDoArquivo();
	int verificaLayout();
	int carregaConteudo();
	void fecharPrograma();
	//=========================================
	//variaveis utilizadas na função principal
	int tentarNarquivo = 0, valido = 0, layout = 0;
	char nomeArquivo[100];
	
	do{
		recebeNome(nomeArquivo);
		valido = validacaoDoArquivo(nomeArquivo);
		if(valido == 0)
			tentarNarquivo = 1;
		else if (valido == 1)
			fecharPrograma();
		else 	
			layout = verificaLayout(nomeArquivo);
			if(layout == 0)
				tentarNarquivo = 1;
			else if(layout == 1)
				fecharPrograma();
			else 
				tentarNarquivo = 1;
	}while(tentarNarquivo == 1);
}
//===========================================================================================================================================================================
char recebeNome(char nomeArquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E CARREGA-LO;
    setlocale(LC_ALL, "portuguese");
	
	printf("Digite o nome de arquivo: ");
	gets(nomeArquivo);
	
	return *nomeArquivo;

}
//============================================================================================================================================================================
void fecharPrograma(){
	setlocale(LC_ALL, "portuguese");
//	system("cls");
	printf("Até a proxima\n");
	system("exit");
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int validacaoDoArquivo(char arquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E SE ELE É VALIDO.
	int resposta = 0;
	int numeroDeLinha = 1;//começa com o valor um por na grande maioria das vezes os arquivos não tem o new line na ultima linha
	char caracter = NULL;
	
	FILE *numeroLinha = fopen(arquivo, "r");//abre o arquivo em modo de leitrua para verificar quantas linhas tem;
	if(numeroLinha == NULL){
		printf("Arquivo não encontrado ou não é valido\nTente novamente\n");
		do{
			printf("Gostaria de tentar com outro arquivo\n");
			printf("SIM___(01)               NÂO____(02)\n");	
			scanf("%d", &resposta);
			fflush(stdin);
			if (resposta == 1)
				return 0;
			else if(resposta == 2)
				return 1;
			else
				printf("Escolha invalida\nTente novamente\n\n");
		}while(resposta < 1 || resposta > 2);
	}
	else
		return 2;		
	fclose (numeroLinha);
}
//====================================================================================================================================================================
/*int verificaColuna(char arquivo[]){
	int numCempresa = 0, resposta = 0;
	char caracter;
	
	FILE *numeroColuna = fopen(arquivo, "r");
	while((caracter = fgetc(numeroColuna))!= EOF){
		if(caracter == ' ')
			++numCempresa;
	}
}*/
//======================================================================================================================================================================
int verificaLayout(char arquivo[]){
	int numeroDeLinha = 1, resposta = 0;
	char caracter;
	FILE *linhas = fopen(arquivo,"r");
		while((caracter = fgetc(linhas))!= EOF)
			if(caracter == '\n')
				numeroDeLinha++;
			printf("%d", numeroDeLinha);
	if(numeroDeLinha % 2 == 0){// Pelo fato do arquivo correto sempre deve ter um numero impar de linhas. essa verificação existe
		do{
			printf("\nFormato de arquivo incorreto\nGostaria e tentar com outro arquivo?\n");
			printf("SIM___(01)           NÃO___(02)\n");
			scanf("%d", &resposta);
			fflush(stdin);
			if (resposta == 1)
				return 0;
			else if(resposta == 2)
				return 1;
			else
				printf("Escolha invalida\nTente novamente\n");
		}while(resposta < 1 || resposta > 2);
	}
	else
		return 2;
}
//=============================================================================================================================================================================
int carregaConteudo(char nomeArquivo[]){
	
	float juros = 0, proprina[50][50];
	int numeroDePolitico = 0, numeroDeEmpresa = 0, i, j;
	
	FILE *pegarNoArquivo = fopen(nomeArquivo, "r");
	
	fscanf(pegarNoArquivo, "%f", &juros);//leitura e armazenamento das informações contidas no arquivo.
	printf("%f\n", juros);
	fscanf(pegarNoArquivo, "%d", &numeroDePolitico);
	printf("%d\n", numeroDePolitico);
	fscanf(pegarNoArquivo, "%d", &numeroDeEmpresa);
	printf("%d\n", numeroDeEmpresa);
	for(i = 0; i < numeroDePolitico; i++){//responsavel por correr as linhas do arquivo
		for(j = 0; j <= numeroDeEmpresa; j++){//responsavel por correr as colunas 
			fscanf(pegarNoArquivo, "%f", &proprina[i][j]);//responsavel por armazenar os valores que estão em na posição i e j...
			if (proprina[i][j] == proprina[i][0])
				printf("%.0f ", proprina[i][j]);//imprime os valores na tela...
			else 
				printf("%.2f\t", proprina[i][j]);
		}
		printf("\n");
	}
	fclose(pegarNoArquivo);
}

