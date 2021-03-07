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

/*==================================BUG DA VERSÃO========================================

BOM, NAS ULTIMAS VERSSÕES EU NÃO COMENTEI COM MUITA CLAREZA. POIS ESTAVA TOTALMENTE PERDIDO. 
PORÉM, TOMEI VERGONHA NA CARA E AKI ESTOU. ENFIM, VAMOS AO PROBLEMA. 

NESSA VERSÃO TEM UM BUG COM RELAÇÃO A FUNÇÃO DE PRINTAR NA TELA O CONTEUDO DAS MATRIZES QUE ARMAZENAM 
OS VALORES QUE ESTÃO NO ARQUIVO. 

BOM O BUG ER MEIO COISADO. POIS, AINDA NÃO IDENTIFIQUEI COM MUITA CLAREZA OQ ESTA ACONTECENDO. 
ENTRETANTO, ATÉ OQ CONSEGUIR OBSERVAR POSSO AFIRMAR QUE TEM GRANDES CHANCES DO BUG ACONTECER POR CAUSA 
DA PASSAGEM DA MATRIZ COMO PARAMETRO DE UMA FUNÇÃO PARA A OUTRA. POIS, NA FUNÇÃO ONDE PEGA OS VALORES 
DO ARQUIVO OS VALORES ESTÃO CORRETOS. POREM, QUANDO COLOCO DENTRO DA FUNCÃO QUE IMPRIME NA TELA ELES FICAM 
BUGADOS.

NESSE MOMENTO ESTOU TESTANDO TODAS AS POSSVEIS POSSIBLIDADES VISANDO IDENTIFICAR O QUE O BUG REALMENTE É.
=========================================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

int main(){
//=======SESSÃO DE DECLARAÇÃO DE FUNÇÕES=======

	char recebeNome();
	int verificaSeVazio();
	int verificaLayout();
	void carregaConteudo();
	void imprimaConteudo();
	void fecharPrograma();

//====VARIÁVEIS USADAS NA FUNÇÃO PRINCIPAL======	

	float JNDPE [2], proprina[50][50], jurosCalculado[50][50], proprinaCalculada[50][50];
	int numeroDePolitico = 0, numeroDeEmpresa = 0, parcela[50][50];
	int tentarNarquivo = 0, valido = 0, vazio = 0;
	char nomeArquivo[100];
	int i, j;

//=============INICIO DAS INSTRUÇÕES=============	
	do{
		tentarNarquivo = 0; //EVITAR LOOP INFINITO.
		
		recebeNome(nomeArquivo);
		vazio = verificaSeVazio(nomeArquivo);
		if(vazio == 0)
			tentarNarquivo = 1;
		else if (vazio == 1)
			fecharPrograma();
		else 	
			valido = verificaLayout(nomeArquivo);
			if(valido == 0)
				tentarNarquivo = 1;
			else if(valido == 1)
				fecharPrograma();
			else{ 
				carregaConteudo(nomeArquivo, parcela, proprina, JNDPE);
				imprimaConteudo(parcela, proprina, JNDPE);
			}
	}while(tentarNarquivo == 1);
}
//===========================================================================================================================================================================

void carregaConteudo(char ARQ[], int parcela[50][50], float proprina[50][50], float JNDPE[2]){
	
	int i = 0, j = 0;

	FILE *pegarNoArquivo = fopen(ARQ, "r");

	for(i = 0; i < 3; i++)
		fscanf(pegarNoArquivo, "%f", &JNDPE[i]);// responsavel por pegar o valor do juros e do numero de politicos e de empresas.
		printf("%f\n", JNDPE[i]);
 
	for(i = 0; i < JNDPE[1]; i++)//responsavel por correr as linhas do arquivo
		for(j = 0; j <= JNDPE[2]; j++)//responsavel por correr as colunas 
			fscanf(pegarNoArquivo, "%f", &proprina[i][j]);//responsavel por armazenar os valores que estão em na posição i e j...
	
	for(i = 0; i < JNDPE[1]; i++)
		for(j = 0; j < JNDPE[2]; j++)					
			fscanf(pegarNoArquivo, "%d", &parcela[i][j]);
			
	fclose(pegarNoArquivo);

}
void imprimaConteudo(int parcela[50][50], float proprina[50][50], float JNDPE[2]){
	
	int i = 0, j = 0;
	
	for(i = 0; i <= 2; i++){
		if (i == 0)
			printf("%f\n", JNDPE[i]);
		else 
			printf("%.0f\n", JNDPE[i]);
	}
	
	for(i = 0; i < JNDPE[1]; i++){
		for(j = 0; j <= JNDPE[2]; i++){
			if(proprina[i][j] == proprina[i][0])
				printf("%.0f ", proprina[i][j]);
			else
				printf("%.2f ", proprina[i][j]);
		}
		printf("\n");
	}
	
	for(i = 0; i < JNDPE[1]; i++){
		for(j = 0; j < JNDPE[2]; j++)
			printf("%d ", parcela[i][j]);
		printf("\n");
	}
}

//===========================================================================================================================================================================

char recebeNome(char nomeArquivo[]){//RESPONSAVEL POR RECEBER O NOME DO ARQUIVO. 
	
	printf("Digite o nome de arquivo: ");
	gets(nomeArquivo);
	
	return *nomeArquivo;

}

//============================================================================================================================================================================

void fecharPrograma(){ // USADA PARA FINALIZAR O PROGRAMA.
	setlocale(LC_ALL, "portuguese");
	system("cls");
	printf("Até a proxima\n");
	system("exit");
}

/*===========================================================================================================================================================================*/

int verificaSeVazio(char arquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E SE ELE É VALIDO.
	int resposta = 0;
	int numeroDeLinha = 1;
	
	FILE *numeroLinha = fopen(arquivo, "r");//abre o arquivo em modo de leitrua para verificar quantas linhas tem;
	if(numeroLinha == NULL){
		printf("Arquivo não encontrado ou nao é valido\nTente novamente\n");
		do{
			printf("Gostaria de tentar com outro arquivo\n");
			printf("SIM___(01)               NAO____(02)\n");	
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

//=====================================================================================================================================================================

int verificaLayout(char arquivo[]){

	int numeroDeLinha = 1, resposta = 0;
	char caracter;

	FILE *linhas = fopen(arquivo,"r");
		while((caracter = fgetc(linhas))!= EOF)
			if(caracter == '\n')
				numeroDeLinha++;
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
	fclose(linhas);
}
//=============================================================================================================================================================================

