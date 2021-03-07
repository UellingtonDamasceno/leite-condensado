#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

#define MAX 50
#define TRUE 1
#define FALSE 0
#define MAX_LIMITE -99999999 
#define MIN_LIMITE 99999999
#define POLITICO 1
#define EMPRESA 2

int main(){
//=============SESSÃO DE DECLARAÇÃO DE FUNÇÕES (ORDEM DE EXECUÇÃO)=============

	char recebeNome();
	int verificaSeVazio();
	int verificaLinha();
	void carregaConteudo();
	int verificaColuna();
	void calculaJuros();
	void calculaProprina();
	void totalPagoPorEmpresa();
	void totalRecebidoPorPolitico();
	void maisEmenos();
	void calculaMedia();
	void gerarArquivoP1();
	void gerarArquivoP2();
	void gerarArquivoP3();
	int erroMsn();
	void fecharPrograma();

//====================VARIÁVEIS USADAS NA FUNÇÃO PRINCIPAL===========================	

	char nomeArquivo[MAX];
	float JNDPE [2], proprina[MAX][MAX], parcela[MAX][MAX]; //armazena conteudo do arquivo
	float proprinaCalculada[MAX][MAX], proprinaSJ[MAX], proprinaCJ[MAX], jurosCalculado[MAX][MAX];//armazena os primeiros valores que devem ser calculados
	float EtotalPagoCJ[MAX], EtotalPagoSJ[MAX];// armazena os valores pagos pelas empresas com e sem juros;
	float totalProprina[MAX], mediaPoli[MAX], mediaEmpre[MAX];//armazena a media dos valores pagos/recebidos;
	float PmaisEmenosDin[7], EmaisEmenosDin[7];//armazena os valores do politico e da empresa que mais e menos receberam/pagaram proprina;
	int pedirNovoArquivo = 0, devePedir = 0, tratarErro = FALSE, idenDoPolitico[MAX];// utilizadas como variaves de controle;
	 
//=============INICIO DAS INSTRUÇÕES=============	
	do{
		pedirNovoArquivo = FALSE; //EVITAR LOOP INFINITO.
		
		recebeNome(nomeArquivo);
		tratarErro = verificaSeVazio(nomeArquivo);
		if(tratarErro == TRUE){
			devePedir = erroMsn();
			if (devePedir == TRUE)
				pedirNovoArquivo = TRUE;
			else 
				fecharPrograma();
		}
		else{	
			tratarErro = verificaLinha(nomeArquivo);
			if(tratarErro == TRUE){
				devePedir = erroMsn();
				if (devePedir = TRUE)
					pedirNovoArquivo = TRUE;
				else
					fecharPrograma();
			}
			else{
				carregaConteudo(nomeArquivo, parcela, proprina, JNDPE, idenDoPolitico);	
				tratarErro = verificaColuna(nomeArquivo, JNDPE);
					if (tratarErro == TRUE){
						devePedir = erroMsn();
						if(devePedir == TRUE)
							pedirNovoArquivo = TRUE;
						else
							fecharPrograma();
					}
					else{
						calculaJuros(parcela, JNDPE, jurosCalculado);
						calculaProprina(proprinaCalculada, jurosCalculado, proprina, JNDPE, proprinaSJ, proprinaCJ);
						totalPagoPorEmpresa(proprinaCalculada, JNDPE, EtotalPagoCJ, proprina, EtotalPagoSJ);
						maisEmenos(proprinaCJ, proprinaSJ, PmaisEmenosDin ,JNDPE, POLITICO);
						maisEmenos(EtotalPagoCJ, EtotalPagoSJ, EmaisEmenosDin ,JNDPE , EMPRESA);
						calculaMedia(proprinaCJ, JNDPE, mediaPoli, POLITICO);
						calculaMedia(EtotalPagoCJ, JNDPE, mediaEmpre, EMPRESA);
						gerarArquivoP1(JNDPE, idenDoPolitico, proprinaCalculada, proprinaCJ, EtotalPagoCJ);
						gerarArquivoP2(idenDoPolitico, PmaisEmenosDin, EmaisEmenosDin);
						gerarArquivoP3(JNDPE, mediaEmpre, mediaPoli);
						printf("\nchegou ao final\n");
		pedirNovoArquivo = TRUE;
					}
			}
		}
	}while(pedirNovoArquivo == TRUE);
}
//======================================================================================================================================================================================
char recebeNome(char nomeArquivo[]){
	
	printf("DIGITE O NOME DO ARQUIVO DESEJADO: ");
	gets(nomeArquivo);
	
	return *nomeArquivo;
}
//======================================================================================================================================================================================
int verificaSeVazio(char arquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E SE ELE É VALIDO.
	int numeroDeLinha = 1;
	
	FILE *numeroLinha = fopen(arquivo, "r");//abre o arquivo em modo de leitrua para verificar quantas linhas tem;
	if(numeroLinha == NULL){
		printf("Arquivo nao encontrado ou nao er valido\nTente novamente\n");
		return TRUE;
	}
	else
		return FALSE;		
	fclose (numeroLinha);
}
//======================================================================================================================================================================================
int verificaLinha(char arquivo[]){

	int numeroDeLinha = 1;
	char caracter;
	
	FILE *linhas = fopen(arquivo,"r");
		while((caracter = fgetc(linhas))!= EOF)
			if(caracter == '\n')
				numeroDeLinha++;
				
	if(numeroDeLinha % 2 == 0){// Pelo fato do arquivo correto sempre deve ter um numero impar de linhas. essa verificação existe
		printf("\nFormato de arquivo incorreto\n");
		printf("Verifique a quantidade de linhas do seu arquivo\n");
		printf("E tente novamente\n");
		return TRUE;
	}
	else
		return FALSE;
	fclose(linhas);
}
//======================================================================================================================================================================================
void carregaConteudo(char ARQ[], int parcela[MAX][MAX], float proprina[MAX][MAX], float JNDPE[2], int idenDoPolitico[MAX]){
	
	int i = 0, j = 0;

	FILE *pegarNoArquivo = fopen(ARQ, "r");

	for(i = 0; i < 3; i++){
		fscanf(pegarNoArquivo, "%f", &JNDPE[i]);// responsavel por pegar o valor do juros e do numero de politicos e de empresas.
		printf("%.2f\n", JNDPE[i]);
	}
	
	for(i = 0; i < JNDPE[1]; i++){//responsavel por correr as linhas do arquivo
		for(j = 0; j <= JNDPE[2]; j++){//responsavel por correr as colunas 
			if (j == 0)
				fscanf(pegarNoArquivo, "%d", &idenDoPolitico[i]); // pega a identificação do politico. 
			else
				fscanf(pegarNoArquivo, "%f", &proprina[i][j - 1]);//responsavel por armazenar os valores que estão em na posição i e j...
		}
	}
	
	for(i = 0; i < JNDPE[1]; i++)
		for(j = 0; j < JNDPE[2]; j++)
			fscanf(pegarNoArquivo, "%d", &parcela[i][j]);
			
	fclose(pegarNoArquivo);
}
//======================================================================================================================================================================================
int verificaColuna(char arquivo[], float JNDPE[2]){
	
	float politico = JNDPE[1];
	float empresa = JNDPE[2];
	float numDeColuna = 0, numCorretoDeColuna = 0;
	char ch;
	
	FILE *coluna = fopen(arquivo, "r");
	while((ch = fgetc(coluna))!= EOF)
		if (ch == ' ')
			numDeColuna++;

	numCorretoDeColuna = politico * empresa + ((empresa - 1) * politico);//calcula a quatidade de colunas corretas que o arquivo deve ter..

	if (numDeColuna != numCorretoDeColuna){//verifica se o numero de linhas do arquivo é diferente do numero correto que o arquivo supostamente deve ter.
		printf("Formato do arquivo incorreto\n");
		printf("Verifique a quantidade de elementos(colunas) do seu arquivo\n");
		printf("E tente novamente\n");
		return TRUE;
	}
	else 
		return FALSE;
	fclose(coluna);
}
//======================================================================================================================================================================================
void calculaJuros(int parcela[MAX][MAX], float JNDPE[2], float jurosCalculado[MAX][MAX]){//responsavel por calcular o juros.
	
	int i = 0, j = 0;
	float juros = (1 + (JNDPE[0]/100));
	for(i = 0; i < JNDPE[1]; i++){
		for(j = 0; j < JNDPE[2]; j++){
			jurosCalculado[i][j] = pow(juros, parcela[i][j]); 
			//printf("%.2f ", jurosCalculado[i][j]);
		}
		//printf("\n");
	}
}
//======================================================================================================================================================================================
void calculaProprina(float proprinaCalculada[MAX][MAX], float jurosCalculado[MAX][MAX], float proprina[MAX][MAX], float JNDPE[2], float proprinaSJ[MAX], float proprinaCJ[MAX]){
	
	int politico = 0, empresa = 0;
	float somaCJ = 0, somaSJ = 0;
	
	for(politico = 0; politico < JNDPE[1]; politico++){
		somaCJ = 0;
		somaSJ = 0;
		for(empresa = 0; empresa < JNDPE[2]; empresa++){	
			
			proprinaCalculada[politico][empresa] = jurosCalculado[politico][empresa] * proprina[politico][empresa];
			somaCJ += proprinaCalculada[politico][empresa]; //responsavel por somar o valor total da proprina com juros.
			somaSJ += proprina[politico][empresa];// responsavel por armazenar o valor total da proprina sem juros.
			printf("%.2f ", proprinaCalculada[politico][empresa]);
			//printf("%.2f ", proprina[politico][empresa]);
			//printf(" {%.2f} ", proprinaSJ[empresa]);
		}
		proprinaCJ[politico] = somaCJ;//atribue o valor total da soma ao vetor responsavel por armazenar o valor total. kk 
		proprinaSJ[politico] = somaSJ;
		printf(" < %.2f >", proprinaCJ[politico]);
		//printf("%.2f\n", proprinaSJ[politico]);
		printf("\n");
	}
	printf("\n");
}
//======================================================================================================================================================================================
void totalPagoPorEmpresa(float proprinaCalculada[MAX][MAX], float JNDPE[2], float EtotalPagoCJ[MAX], float proprina[MAX][MAX], float EtotalPagoSJ[MAX]){
	int politico, empresa;
	float somaCJ = 0, somaSJ = 0;
	
	for(politico = 0; politico < JNDPE[1]; politico++){
		somaCJ = 0, somaSJ = 0;
		for(empresa = 0; empresa < JNDPE[2]; empresa++){
			somaCJ += proprinaCalculada[empresa][politico];//calcula a proprina com o juros.
			//printf("[%.2f] ", proprinaCalculada[empresa][politico]);
			somaSJ += proprina[empresa][politico];//calcula a proprina sem juros.
		}
		EtotalPagoCJ[politico] = somaCJ;
		EtotalPagoSJ[politico] = somaSJ;
		//printf("\n");
		printf("%.2f    ", EtotalPagoCJ[politico]);
		//printf("(%.2f)\n\n", EtotalPagoSJ[empresa]);
	}
	printf("\n");
}
//======================================================================================================================================================================================
void maisEmenos(float PCJ[MAX], float PSJ[MAX], float maisEmenos[7], float JNDPE[2], int PouE){
	int i;
	maisEmenos[2] = MAX_LIMITE;
	maisEmenos[5] = MIN_LIMITE;
	
	for (i = 0; i != JNDPE[PouE]; i++){
		//printf("\nTotal Pago {%.2f} ", PCJ[i]);
		if(PCJ[i] > maisEmenos[2]){//PECORRE TODO VETOR VERIFICANDO QUAL É O MAIOR VALOR
			maisEmenos[0] = i + 1;//ARMAZENA A ID DO POLITICO OU EMPRESA
		//	printf("\n+%.0f:: ", maisEmenos[0]);
			maisEmenos[1] = PSJ[i];//ARMAZENA O VALOR SEM JUROS
		//	printf("%.2f  ", maisEmenos[1]);
			maisEmenos[2] = PCJ[i];//ARMAZENA O VALOR COM JUROS
		//	printf("%.2f  ", maisEmenos[2]);
			maisEmenos[3] = PCJ[i] - PSJ[i];//CALCULA E ARMAZENA O VALOR DO JUROS
		//	printf("%.2f", maisEmenos[3]);
		//	printf("\n");
		}
		if(PCJ[i] < maisEmenos[5]){//PECORRE TODO VETOR VERIFICANDO QUAL É O MENOR VALOR
			maisEmenos[4] = i + 1;//ARMAZENA A ID DO POLITICO OU EMPRESA
		//	printf("\n-%.0f:: ", maisEmenos[4]);
			maisEmenos[5] = PSJ[i];//ARMAZENA O VALOR SEM JUROS
		//	printf("%.2f  ", maisEmenos[5]);
			maisEmenos[6] = PCJ[i];//ARMAZENA O VALOR COM JUROS
		//	printf("%.2f  ", maisEmenos[6]);
			maisEmenos[7] = PCJ[i] - PSJ[i];//CALCULA E ARMAZENA O VALOR DO JUROS
		//	printf("%.2f", maisEmenos[7]);
		//	printf("\n");
		}
	}
	printf("\n%.0f:: [%.2f]   {%.2f}    [%.2f]\n", maisEmenos[0], maisEmenos[1], maisEmenos[2], maisEmenos[3]);
	printf("%.0f:: [%.2f]   {%.2f}    [%.2f]\n", maisEmenos[4], maisEmenos[5], maisEmenos[6], maisEmenos[7]);	
}
//======================================================================================================================================================================================
void calculaMedia(float PCJ[MAX], float JNDPE[MAX], float media[MAX], int PouE){

	float soma = 0;
	int i;
	printf("\n");
	for (i = 0; i < JNDPE[PouE]; i++){
		media[i] = (PCJ[i] / JNDPE[PouE]);
		printf("%.2f\n", media[i]);
	}
	printf("\n");
}
//======================================================================================================================================================================================
void gerarArquivoP1(float JNDPE[2], int idDoPoli[MAX], float propCal[MAX][MAX], float PCJ[MAX], float EPagoCJ[MAX]){
	
	int i, j;
	FILE *arq = fopen("Saida.txt", "w");
	
	for (i = 0; i < JNDPE[1]; i++){
		fprintf(arq, "%d ", idDoPoli[i]);
		//printf("%d ", idDoPoli[i]);
		for(j = 0; j < JNDPE[2]; j++){
			//printf("%.2f ", propCal[i][j]);	
			fprintf(arq, "%.2f ", propCal[i][j]);
		}
		//printf("%.2f\n", PCJ[i]);
		fprintf(arq, "%.2f\n", PCJ[i]);
	}
	fprintf(arq, "\n");
	for (j = 0; j < JNDPE[2]; j++){
		fprintf(arq, "%.2f ", EPagoCJ[j]);
	}
	fprintf(arq, "\n\n");
	fclose(arq);
}
//======================================================================================================================================================================================
void gerarArquivoP2(int idDoPoli[MAX], float PmaisEmenos[7], float EmaisEmenos [7]){
	int i, j;
	FILE *arq = fopen("Saida.txt", "a+");
	
	for (i = 0; i < 8; i++){
		if (i == 0 || i == 4){
			if(i == 4)
				fprintf(arq, "\n\n");
			fprintf(arq, "%.0f ", PmaisEmenos[i]);
		}
		else 
			fprintf(arq, "%.2f ", PmaisEmenos[i]);
	}
	fprintf(arq, "\n\n");
	for (i = 0; i < 8; i++){
		if (i == 0 || i == 4){
			if (i == 4)
				fprintf(arq ,"\n\n");
			fprintf(arq, "%.0f ", EmaisEmenos[i]);
		}
		else 
			fprintf(arq, "%.2f ", EmaisEmenos[i]);
	}
	fprintf(arq, "\n\n");
	fclose(arq);
}
//======================================================================================================================================================================================
void gerarArquivoP3(float JNDPE[2], float mediaEmpre[MAX], float mediaPoli[MAX]){
	int i;
	FILE *arq = fopen("Saida.txt", "a+");
	
	for (i = 0; i < JNDPE[1]; i++){
		fprintf(arq, "%d ", i+1); 
		fprintf(arq, "%.2f \n", mediaPoli[i]);
	}
	fprintf(arq, "\n");
	for (i = 0; i < JNDPE[2]; i++){
		fprintf(arq, "%d ", i+1);
		fprintf(arq, "%.2f \n", mediaEmpre[i]);
	}
	fclose(arq);
}
//======================================================================================================================================================================================
int erroMsn(){
	int resposta = 0;
	do{
		printf("\nGostaria e tentar com outro arquivo?\n");
		printf("SIM___(01)           NAO___(02)\n");
		scanf("%d", &resposta);
		fflush(stdin);
		if (resposta == 1)
			return 1;
		else if(resposta == 2)
			return 0;
		else
			printf("Escolha invalida\nTente novamente\n");
	}while(resposta < 1 || resposta > 2);
}
//======================================================================================================================================================================================
void fecharPrograma(){ // USADA PARA FINALIZAR O PROGRAMA.
	setlocale(LC_ALL, "portuguese");
	system("cls");
	printf("\aAté a proxima\n");
	system("exit");
}
