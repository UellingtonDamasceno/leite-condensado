/*******************************************************************************
Autor:Uellington Da Conceição Damasceno

Componente Curricular: Algoritmos I

Concluido em: 21/06/2017

Declaro que este código foi elaborado por mim de forma individual e não contém nenhum

trecho de código de outro colega ou de outro autor, tais como provindos de livros e

apostilas, e páginas ou documentos eletrônicos da Internet. Qualquer trecho de código

de outra autoria que não a minha está destacado com uma citação para o autor e a fonte

do código, e estou ciente que estes trechos não serão considerados para fins de avaliação.
******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX 50
#define TRUE 1
#define FALSE 0
#define MAX_LIMITE -99999999
#define MIN_LIMITE 99999999
#define POLITICO 1
#define EMPRESA 2
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
	void sucesso();
	int erroMsn();
	void fecharPrograma();

void barraSup(int tamanho, int titulo){
	int i = 0;
	printf("\t\t\t\xC9");
	for(i = 0; i<tamanho; i++){
		if (i == 23){
			if(titulo == 1)
				printf("ERRO SEMANTICO");
			else if(titulo == 2)
				printf("ERRO SINTATICO");
			else if(titulo == 3)
				printf("\xCD\xCD\xCDRELATORIO\xCD\xCD");
			else				
				printf("\xCD");
		}
		else
			printf("\xCD");
	}
	printf("\xBB\n\t\t\t");
}
void barraInf(int tamanho){
	int i = 0;
	printf("\t\t\t\xC8");
	for(i = 0; i < tamanho; i++)
		printf("\xCD");
	printf("\xBC\n");
}
int main(){
//====================VARIÁVEIS USADAS NA FUNÇÃO PRINCIPAL===========================

	char nomeArquivo[MAX];
	float JNDPE[2], proprina[MAX][MAX], parcela[MAX][MAX]; //JNDPE = JUROS, NUMERO DE POLITO E EMPRESA,
	float proprinaCalculada[MAX][MAX], proprinaSJ[MAX], proprinaCJ[MAX], jurosCalculado[MAX][MAX];//armazena os primeiros valores que devem ser calculados
	float EtotalPagoCJ[MAX], EtotalPagoSJ[MAX];// armazena os valores pagos pelas empresas com e sem juros;
	float totalProprina[MAX], mediaPoli[MAX], mediaEmpre[MAX];//armazena a media dos valores pagos/recebidos;
	float PmaisEmenosDin[7], EmaisEmenosDin[7];//armazena os valores do politico e da empresa que mais e menos receberam/pagaram proprina;
	int pedirNovoArquivo = 0, devePedir = 0, deuErro = FALSE, idenDoPolitico[MAX];// utilizadas como variaves de controle;

//=============INICIO DAS INSTRUÇÕES=============
	do{
		pedirNovoArquivo = FALSE; //EVITAR LOOP INFINITO.

		recebeNome(nomeArquivo);
		deuErro = verificaSeVazio(nomeArquivo);//verifica se o arquivo esta se existe e ou vazio
		if(deuErro == TRUE){
			devePedir = erroMsn();
			if (devePedir == TRUE)
				pedirNovoArquivo = TRUE;
			else
				fecharPrograma();
		}
		else{
			deuErro = verificaLinha(nomeArquivo);//verifica se a quantidade de linhas do arquivo é correta
			if(deuErro == TRUE){
				devePedir = erroMsn();
				if (devePedir == TRUE)
					pedirNovoArquivo = TRUE;
				else
					fecharPrograma();
			}
			else{
				carregaConteudo(nomeArquivo, parcela, proprina, JNDPE, idenDoPolitico);//carrega as informações do arquivo 
				deuErro = verificaLetra(nomeArquivo);
				if (deuErro == TRUE){
					devePedir = erroMsn();
					if(devePedir == TRUE)
						pedirNovoArquivo = TRUE;
					else
						fecharPrograma();
				}
				else{
					deuErro = verificaColuna(nomeArquivo, JNDPE);//verifica se o arquivo tem a quantidade correta de elementos.
					if (deuErro == TRUE){
						devePedir = erroMsn();
						if(devePedir == TRUE)
							pedirNovoArquivo = TRUE;
						else
							fecharPrograma();
					}
					else{
						calculaJuros(parcela, JNDPE, jurosCalculado);//calcula o valor do juros
						calculaProprina(proprinaCalculada, jurosCalculado, proprina, JNDPE, proprinaSJ, proprinaCJ);//calcula a proprina utilizando a formula de juro composto.
						totalPagoPorEmpresa(proprinaCalculada, JNDPE, EtotalPagoCJ, proprina, EtotalPagoSJ);//calcula o total de proprina pago por empresa
						maisEmenos(proprinaCJ, proprinaSJ, PmaisEmenosDin ,JNDPE, POLITICO, idenDoPolitico);//descobre qual politico recebeu mais e menos proprina
						maisEmenos(EtotalPagoCJ, EtotalPagoSJ, EmaisEmenosDin ,JNDPE , EMPRESA, idenDoPolitico);//descobre qual empresa mais e menos pagou proprina
						calculaMedia(proprinaCJ, JNDPE, mediaPoli, POLITICO);//calcula a media do politico 
						calculaMedia(EtotalPagoCJ, JNDPE, mediaEmpre, EMPRESA);//calcula a media da empresa 
						gerarArquivoP1(JNDPE, idenDoPolitico, proprinaCalculada, proprinaCJ, EtotalPagoCJ);//gera a primeira parte do arquivo 
						gerarArquivoP2(idenDoPolitico, PmaisEmenosDin, EmaisEmenosDin);//gera a segunda parte do arquivo 
						gerarArquivoP3(JNDPE, mediaEmpre, mediaPoli);//gera a terceira parte do arquivo 
						sucesso();//imprime uma mensagem de sucesso.
						devePedir = erroMsn();//possibilita que o usario insira outro arquivo sem a necessidade de fechar o programa.
						if (devePedir == TRUE)
							pedirNovoArquivo = TRUE;
						else
							fecharPrograma();
					}
				}
			}
		}
	}while(pedirNovoArquivo == TRUE);
}
//======================================================================================================================================================================================
char recebeNome(char nomeArquivo[]){
	system("cls");
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
		barraSup(47, 2);
		printf("\xBA\t\t   Formato de arquivo incorreto\t\t     \xBA\n");
		printf("\t\t\t\xBA\t Verifique a quantidade de linhas do seu arquivo     \xBA\n");
		printf("\t\t\t\xBA\t\t      E tente novamente\t\t\t     \xBA\n");
		barraInf(60);
		return TRUE;
	}
	else
		return FALSE;
	fclose(linhas);
}
//======================================================================================================================================================================================
void carregaConteudo(char ARQ[], int parcela[MAX][MAX], float prop[MAX][MAX], float JNDPE[2], int idDoPoli[MAX]){
	int i = 0, j = 0;

	FILE *pegarNoArquivo = fopen(ARQ, "r");

	for(i = 0; i < 3; i++)
		fscanf(pegarNoArquivo, "%f", &JNDPE[i]);// responsavel por pegar o valor do juros e do numero de politicos e de empresas.
	

	for(i = 0; i < JNDPE[POLITICO]; i++){//responsavel por correr as linhas do arquivo
		for(j = 0; j <= JNDPE[EMPRESA]; j++){//responsavel por correr as colunas
			if (j == 0)
				fscanf(pegarNoArquivo, "%d", &idDoPoli[i]); // pega a identificação do politico.
			else
				fscanf(pegarNoArquivo, "%f", &prop[i][j - 1]);//responsavel por armazenar os valores que estão em na posição i e j...	
		}
	}

	for(i = 0; i < JNDPE[POLITICO]; i++)
		for(j = 0; j < JNDPE[EMPRESA]; j++)
			fscanf(pegarNoArquivo, "%d", &parcela[i][j]);

	fclose(pegarNoArquivo);
}
//======================================================================================================================================================================================
int verificaLetra(char arquivo[]){
	char ch;
	int i = 0, erro = FALSE;
	FILE *caractere = fopen (arquivo, "r");
	while((ch = fgetc(caractere))!= EOF)
		if (isalpha(ch)){
			erro = TRUE;
			barraSup(47, 1);	
			printf("\xBA  Sentimos muito! Mas, existe um erro semantico no arquivo  \xBA\n");
			barraInf(60);
			return TRUE;
		}
		else 	
			return FALSE;
}
int verificaColuna(char arquivo[], float JNDPE[2]){
	int i = 0;
	float politico = JNDPE[POLITICO];
	float empresa = JNDPE[EMPRESA];
	float numDeColuna = 0, numCorretoDeColuna = 0;
	char ch;

	FILE *coluna = fopen(arquivo, "r");
	while((ch = fgetc(coluna))!= EOF)
		if (ch == ' ')
			numDeColuna++;

	numCorretoDeColuna = politico * empresa + ((empresa - 1) * politico);//calcula a quatidade de colunas corretas que o arquivo deve ter..
	if (numDeColuna != numCorretoDeColuna){//verifica se o numero de linhas do arquivo é diferente do numero correto que o arquivo supostamente deve ter.

		barraSup(47, 2);
		printf("\xBA\t\t  Formato do arquivo incorreto\t\t     \xBA\n");
		printf("\t\t\t\xBA   Verifique a quantidade de elementos(colunas) do arquivo  \xBA\n");
		printf("\t\t\t\xBA\t\t\tE tente novamente\t\t     \xBA\n");
		barraInf(60);
			
		return TRUE;
	}
	else
		return FALSE;
	fclose(coluna);
}
//======================================================================================================================================================================================
void calculaJuros(int parcela[MAX][MAX], float JNDPE[2], float jCalculado[MAX][MAX]){//responsavel por calcular o juros.
	
	int i = 0, j = 0;
	float juros = (1 + (JNDPE[0]/100));
	
	for(i = 0; i < JNDPE[POLITICO]; i++)
		for(j = 0; j < JNDPE[EMPRESA]; j++)
			jCalculado[i][j] = pow(juros, parcela[i][j]);
}
//======================================================================================================================================================================================
void calculaProprina(float propCal[MAX][MAX], float jCalculado[MAX][MAX], float prop[MAX][MAX], float JNDPE[2], float propSJ[MAX], float propCJ[MAX]){

	int politico = 0, empresa = 0;
	float somaCJ = 0, somaSJ = 0;
	for(politico = 0; politico < JNDPE[POLITICO]; politico++){
		somaCJ = 0;
		somaSJ = 0;
		for(empresa = 0; empresa < JNDPE[EMPRESA]; empresa++){
			propCal[politico][empresa] = jCalculado[politico][empresa] * prop[politico][empresa];
			somaCJ += propCal[politico][empresa]; //responsavel por somar o valor total da proprina com juros.
			somaSJ += prop[politico][empresa];// responsavel por armazenar o valor total da proprina sem juros.
		}
		propCJ[politico] = somaCJ;//atribue o valor total da soma ao vetor responsavel por armazenar o valor total. kk
		propSJ[politico] = somaSJ;	
	}
}
//======================================================================================================================================================================================
void totalPagoPorEmpresa(float propCal[MAX][MAX], float JNDPE[2], float EtotalPagoCJ[MAX], float proprina[MAX][MAX], float EtotalPagoSJ[MAX]){

	int politico = 0, empresa = 0;
	float somaCJ = 0, somaSJ = 0;
	
	for(empresa = 0; empresa < JNDPE[EMPRESA]; empresa++){
		somaCJ = 0, somaSJ = 0;
		for(politico = 0; politico < JNDPE[POLITICO]; politico++){
			somaCJ += propCal[politico][empresa];//calcula a proprina com o juros.
			somaSJ += proprina[politico][empresa];//calcula a proprina sem juros.
		}
		EtotalPagoCJ[empresa] = somaCJ;
		EtotalPagoSJ[empresa] = somaSJ;
	}
}
//======================================================================================================================================================================================
void maisEmenos(float PCJ[MAX], float PSJ[MAX], float maisEmenos[7], float JNDPE[2], int PouE, int idPolitico[MAX]){
	int i;
	maisEmenos[2] = MAX_LIMITE;
	maisEmenos[6] = MIN_LIMITE;
	
	for (i = 0; i != JNDPE[PouE]; i++){
		if(PCJ[i] > maisEmenos[2]){//PECORRE TODO VETOR VERIFICANDO QUAL É O MAIOR VALOR
			if(PouE == 1)
				maisEmenos[0] = idPolitico[i];
			else
				maisEmenos[0] = i + 1;//ARMAZENA A ID DO POLITICO OU EMPRESA
			maisEmenos[1] = PSJ[i];//ARMAZENA O VALOR SEM JUROS
			maisEmenos[2] = PCJ[i];//ARMAZENA O VALOR COM JUROS
			maisEmenos[3] = PCJ[i] - PSJ[i];//CALCULA E ARMAZENA O VALOR DO JUROS
		}
		if(PCJ[i] < maisEmenos[6]){//PECORRE TODO VETOR VERIFICANDO QUAL É O MENOR VALOR
			if(PouE == 1)
				maisEmenos[4] = idPolitico[i];
			else
				maisEmenos[4] = i + 1;//ARMAZENA A ID DO POLITICO OU EMPRESA
			maisEmenos[5] = PSJ[i];//ARMAZENA O VALOR SEM JUROS
			maisEmenos[6] = PCJ[i];//ARMAZENA O VALOR COM JUROS
			maisEmenos[7] = PCJ[i] - PSJ[i];//CALCULA E ARMAZENA O VALOR DO JUROS
		}
	}
}
//======================================================================================================================================================================================
void calculaMedia(float PCJ[MAX], float JNDPE[2], float media[MAX], int PouE){

	float soma = 0;
	int i;

	for (i = 0; i < JNDPE[PouE]; i++){
		media[i] = (PCJ[i] / JNDPE[PouE]);
	}
	
}
//======================================================================================================================================================================================
void gerarArquivoP1(float JNDPE[2], int idDoPoli[MAX], float propCal[MAX][MAX], float PCJ[MAX], float EPagoCJ[MAX]){

	int i, j;
	FILE *arq = fopen("Saida.txt", "w");

	for (i = 0; i < JNDPE[POLITICO]; i++){
		fprintf(arq, "%d ", idDoPoli[i]);
		for(j = 0; j < JNDPE[EMPRESA]; j++){
			fprintf(arq, "%.2f ", propCal[i][j]);
		}
		fprintf(arq, "%.2f\n", PCJ[i]);
	}
	fprintf(arq, "\n");
	for (j = 0; j < JNDPE[EMPRESA]; j++){
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
void gerarArquivoP3(float JNDPE[2], float medEmpre[MAX], float medPoli[MAX]){
	int i;
	FILE *arq = fopen("Saida.txt", "a+");

	for (i = 0; i < JNDPE[POLITICO]; i++){
		fprintf(arq, "%d ", i+1);
		fprintf(arq, "%.2f \n", medPoli[i]);
	}
	fprintf(arq, "\n");
	for (i = 0; i < JNDPE[EMPRESA]; i++){
		fprintf(arq, "%d ", i+1);
		fprintf(arq, "%.2f \n", medEmpre[i]);
	}
	fclose(arq);
}
//======================================================================================================================================================================================
int erroMsn(){
	int resposta = 0, i = 0;
	
	do{
		barraSup(60, 0);
		printf("\xBA\t      Gostaria e tentar com outro arquivo?\t     \xBA\n");
		printf("\t\t\t\xBA\t\tSIM___(01)           NAO___(02)\t\t     \xBA\n");
		barraInf(60);
		scanf("%d", &resposta);
		fflush(stdin);
	
		if (resposta == 1)
			return TRUE;
		else if(resposta == 2)
			return FALSE;
		else
			printf("Escolha invalida\nTente novamente\n");
	}while(resposta < 1 || resposta > 2);
}
//======================================================================================================================================================================================
void sucesso(){
	int i = 0;
	barraSup(47, 3)	;
	printf("\xBA\t\tTODOS OS VALORES FORAM VALIDADOS\t     \xBA\n");
	printf("\t\t\t\xBA\t    OS CALCULOS ESTAO NO ARQUIVO: 'Saida.txt'\t     \xBA\n");
	barraInf(60);
}
//======================================================================================================================================================================================
void fecharPrograma(){ // USADA PARA FINALIZAR O PROGRAMA.

	int i;
	system("cls");
	for (i = 0; i < 14; i++)//desce 14 linhas
		printf("\n");
	for (i = 0; i < 2; i++)//centraliza o texto
		printf("\t");
		
	barraSup(28, 0);
	for (i = 0; i < 2; i++)//centraliza o texto
		printf("\t");
	printf("\a\xBA\t>Ate a proxima<      \xBA\n");//mensagem de até a proxima
	for (i = 0; i < 2; i++)
		printf("\t");
	barraInf(28);
	
	for (i = 0; i < 14; i++)
		printf("\n");
		
	system("exit");

}
