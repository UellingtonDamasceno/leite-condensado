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
/*=============================IDENTIFICAÇÃO DO BUG========================================
OBSERVAÇÃO:
	AINDA NÃO É UM BUG EM SI. MAS, ER UM PORBLEMA QUE PRECISO RESOLVER.
BOM O ERRO CONSISTE NO FATO DE QUE O PROGRMA NÃO ESTA CALCULANDO O VALOR CORRETO DA PRORPINA
PAGA POR EMPRESA. 
FATO: 
	
VARIANTES: 
	SEM VARIANTE;
CONCLUSÃO:
BUG:

BUG CORRIGIDO:

==========================================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

#define MAX 50
#define TRUE 1
#define FALSE 0
#define MAX_LIMITE -99999999
#define MIN_LIMITE 9999999
int main(){
//=============SESSÃO DE DECLARAÇÃO DE FUNÇÕES (ORDEM DE EXECUÇÃO)=============

	char recebeNome();
	int verificaSeVazio();
	int verificaLinha();
	void carregaConteudo();
	int verificaColuna();
	int valorTotalPago();
	void totalPagoPorEmpresa();
	void totalRecebidoPorPolitico();
	void PmaisEmenosPago();
	void EmaisEmenosPagou();
	void mediaPolitico();
	void mediaEmpresa();
	void gerarArquivoP1();
	void gerarArquivoP2();
	void gerarArquivoP3();
	int erroMsn();
	void fecharPrograma();

//====================VARIÁVEIS USADAS NA FUNÇÃO PRINCIPAL===========================	

	float JNDPE [2], proprina[MAX][MAX], jurosCalculado[MAX][MAX], proprinaCalculada[MAX][MAX];
	float poliMaisDin[3], poliMenosDin[3], empreMaisDin[3], empreMenosDin[3], totalPagoEmpresa[MAX];
	float totalRecebido[MAX], parcela[MAX][MAX], mediaPoli[MAX][MAX], mediaEmpre[MAX][MAX];
	int pedirNovoArquivo = 0, devePedir = 0, tratarErro = FALSE, idenDoPolitico[MAX];
	char nomeArquivo[MAX]; 

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
						valorTotalPago(proprinaCalculada, parcela, proprina, JNDPE, idenDoPolitico);
						totalPagoPorEmpresa(proprinaCalculada, totalPagoEmpresa, JNDPE);
						totalRecebidoPorPolitico(proprinaCalculada, totalRecebido, JNDPE);
						PmaisEmenosPago(totalRecebido, idenDoPolitico, poliMaisDin, poliMenosDin, JNDPE, proprina);
						EmaisEmenosPagou(totalPagoEmpresa, empreMaisDin, empreMenosDin, JNDPE, proprina);
						mediaPolitico(proprinaCalculada, JNDPE, mediaPoli);
						mediaEmpresa(proprinaCalculada, JNDPE, mediaEmpre);
						printf("\nchegou ao final\n");
		pedirNovoArquivo = TRUE;
					}
			}
		}
	}while(pedirNovoArquivo == TRUE);
}
//============================================================================================================================================================================
/*void gerarArquivoP1(int idenDoPolitico[MAX], float proprinaCalculada[MAX][MAX], float totalRecebido[MAX],float JNDPE[2]){
	
	int i = 0, j = 0;
	
	FILE *Saida = fopen(Saida, "w+");
	
	for(i = 0; i < JNDPE[1]; i++){
		fprintf(Saida, "%d ", idenDoPolitico);
		for(j = 0; j < JNDPE[2]; j++){
			fprintf(Saida, "%.2f ", proprinaCalculada[i][j]);
		}
		fprintf(Saida, "%.2f\n", totalRecebido);
	}
}*/
//============================================================================================================================================================================
void mediaEmpresa(float proprinaCalculada[MAX][MAX], float JNDPE[2], float mediaEmpre[MAX]){
	int politico = 0, empresa = 0;
	float soma = 0;
	
	for(politico = 0; politico < JNDPE[1]; politico++){
		soma = 0;
		for(empresa = 0; empresa < JNDPE[2]; empresa++){
			printf("%.2f ", proprinaCalculada[empresa][politico]);
			soma += proprinaCalculada [empresa][politico];
			//printf("%.2f ", soma);
		}
		printf("\n");
		mediaEmpre[politico] = (soma / JNDPE[2]);
		//printf("\n{%.2f}", mediaEmpre[politico]);
	}
}
//============================================================================================================================================================================
void mediaPolitico(float proprinaCalculada[MAX][MAX], float JNDPE[2], float mediaPoli[MAX]){
	int empresa = 0, politico = 0;
	float soma = 0;
	
	for (politico = 0; politico < JNDPE[1]; politico++){
		soma = 0;
		for (empresa = 0; empresa < JNDPE[2]; empresa++){
			soma += proprinaCalculada[politico][empresa];
			printf("%.2f ", proprinaCalculada[politico][empresa]);
		}
		mediaPoli[politico] = (soma / JNDPE[1]);
		//printf("(%.2f)\n", mediaPoli[politico]);
		printf("\n");
	}
	printf("\n");
}
//============================================================================================================================================================================
void EmaisEmenosPagou(float totalPagoEmpresa[MAX], float empreMaisDin[3], float empreMenosDin[3], float JNDPE[2], float proprina[MAX][MAX]){//maior e menor proprina, com e sem juros.
	int politico = 0, empresa = 0;
	float somaDaProprinaV[MAX], somaV = 0;
		empreMaisDin[2] = MAX_LIMITE;
		empreMenosDin[2] = MIN_LIMITE;
		
	for(politico = 0; politico < JNDPE[1]; politico++){
		somaV = 0;
		for(empresa = 0; empresa < JNDPE[2]; empresa++){
			somaV += proprina[empresa][politico];
			printf("\n<%.2f> ", proprina[empresa][politico]);
		}
		somaDaProprinaV [politico]= somaV;
		printf("\nSoma Das proprina V: %.2f\n", somaDaProprinaV[politico]);
	}
	for(empresa = 0; empresa < JNDPE[2]; empresa++){
		printf("\nTotal Pago {%.2f} ", totalPagoEmpresa[empresa]);
		if(totalPagoEmpresa[empresa] > empreMaisDin[2]){
			empreMaisDin[0] = empresa + 1;
			printf("\n+%.0f:: ", empreMaisDin[0]);
			empreMaisDin[1] = somaDaProprinaV[empresa];
			printf("%.2f  ", empreMaisDin[1]);
			empreMaisDin[2] = totalPagoEmpresa[empresa];
			printf("%.2f  ", empreMaisDin[2]);
			empreMaisDin[3] = totalPagoEmpresa[empresa] - somaDaProprinaV[empresa];
			printf("%.2f", empreMaisDin[3]);
			printf("\n");
		}
		if(totalPagoEmpresa[empresa] < empreMenosDin[2]){
			empreMenosDin[0] = empresa + 1;
			printf("\n-%.0f:: ", empreMenosDin[0]);
			empreMenosDin[1] = somaDaProprinaV[empresa];
			printf("%.2f  ", empreMenosDin[1]);
			empreMenosDin[2] = totalPagoEmpresa[empresa];
			printf("%.2f  ", empreMenosDin[2]);
			empreMenosDin[3] = totalPagoEmpresa[empresa] - somaDaProprinaV[empresa];
			printf("%.2f", empreMenosDin[3]);
			printf("\n");
		}
	}
	printf("\n");
	printf("\nA empresa %.0f pagou %.2f de proprina SEM juros\n", empreMaisDin[0], empreMaisDin[1]);
	printf("A empresa %.0f pagou a maior quantia de dinherio: %.2f\n", empreMaisDin[0], empreMaisDin[2]);
	printf("A empresa %.0f pagou %.2f de proprina SO DE juros\n\n", empreMaisDin[0], empreMaisDin[3]);
	printf("A empresa %.0f pagou %.2f de proprina SEM juros\n", empreMenosDin[0], empreMenosDin[1]);
	printf("A empresa %.0f pagou a menor quantia de dinherio: %.2f\n", empreMenosDin[0], empreMenosDin[2]);
	printf("A empresa %.0f pagou %.2f de proprina SO DEjuros\n\n\n", empreMenosDin[0], empreMenosDin[3]);
}
//============================================================================================================================================================================
void PmaisEmenosPago(float totalRecebido[MAX], int idenDoPolitico[MAX], float poliMaisDin[3], float poliMenosDin[3], float JNDPE[2], float proprina[MAX][MAX]){
	int politico = 0, empresa = 0;
	float somaDaProprina[MAX], soma = 0;
		poliMaisDin [2] = MAX_LIMITE;
		poliMenosDin [2] = MIN_LIMITE;
	
	for(politico = 0; politico < JNDPE[1]; politico++){//responsavel por somar todos propinas sem juros. (horizontal)
		soma = 0;//reinicia o valor da soma para que possa armazenar os valores da proxima linha
		for(empresa = 0; empresa < JNDPE[1]; empresa++){
			soma += proprina[politico][empresa];
			printf("\n<%.2f>", proprina[politico][empresa]);
		}
		somaDaProprina[politico] = soma;
		printf("\n");
		printf("\nSoma Das proprinas: %.2f", somaDaProprina[politico]);
	}
	printf("\n");
	for(politico = 0; politico < JNDPE[2]; politico++){
		printf("%.2f      ", totalRecebido[politico]);
		if (totalRecebido[politico] > poliMaisDin[2]){
			poliMaisDin[0] = idenDoPolitico[politico];//atribue a identificação do politico que mais recebeu proprina
			poliMaisDin[1] = somaDaProprina[politico];
			poliMaisDin[2] = totalRecebido[politico];//atribue o maior valor de proprina recebida
			poliMaisDin[3] = totalRecebido[politico] - somaDaProprina[politico];//valor do juros pago para o politico que mais recebeu proprina
		}
		if(totalRecebido[politico] < poliMenosDin[2]){//não coloquei um else if pelo fato de que se o primeiro politico tiver pago a menor proprina ele não entra aki. 
			poliMenosDin[0] = idenDoPolitico[politico];//atribue a identificação do politico que menos recebeu propina
			poliMenosDin[1] = somaDaProprina[politico];
			poliMenosDin[2] = totalRecebido[politico];//atribue o menor valor de proprina recebida 
			poliMenosDin[3] = totalRecebido[politico] - somaDaProprina[politico];//valor do juros pago para o politico que menos recebeu proprina		
		}
	}
	printf("\n");
	printf("\nO politico %.0f recebeu %.2f de proprina SEM juros\n", poliMaisDin[0], poliMaisDin[1]);
	printf("O politico %.0f recebeu a maior quantia de dinherio: %.2f\n", poliMaisDin[0], poliMaisDin[2]);
	printf("O politico %.0f recebeu %.2f de proprina SO DE juros\n\n", poliMaisDin[0], poliMaisDin[3]);
	printf("O politico %.0f recebeu %.2f de proprina SEM juros\n", poliMenosDin[0], poliMenosDin[1]);
	printf("O politico %.0f recebeu a menor quantia de dinherio: %.2f\n", poliMenosDin[0], poliMenosDin[2]);
	printf("O politico %.0f recebeu %.2f de proprina SO DE juros\n\n\n", poliMenosDin[0], poliMenosDin[3]);
}
//============================================================================================================================================================================
void carregaConteudo(char ARQ[], int parcela[MAX][MAX], float proprina[MAX][MAX], float JNDPE[2], int idenDoPolitico[MAX]){
	
	int i = 0, j = 0;

	FILE *pegarNoArquivo = fopen(ARQ, "r");

	for(i = 0; i < 3; i++){
		fscanf(pegarNoArquivo, "%f", &JNDPE[i]);// responsavel por pegar o valor do juros e do numero de politicos e de empresas.
		printf("%.2f", JNDPE[i]);
	}
	for(i = 0; i < JNDPE[1]; i++){//responsavel por correr as linhas do arquivo
		for(j = 0; j <= JNDPE[2]; j++){//responsavel por correr as colunas 
			if (j == 0)
				fscanf(pegarNoArquivo, "%d", &idenDoPolitico[i]);
			else
				fscanf(pegarNoArquivo, "%f", &proprina[i][j - 1]);//responsavel por armazenar os valores que estão em na posição i e j...
		}
	}
	for(i = 0; i < JNDPE[1]; i++)
		for(j = 0; j < JNDPE[2]; j++)					
			fscanf(pegarNoArquivo, "%d", &parcela[i][j]);
			
	fclose(pegarNoArquivo);

}
//============================================================================================================================================================================
int valorTotalPago(float proprinaCalculada[MAX][MAX], int parcela[MAX][MAX], float proprina[MAX][MAX], float JNDPE[2], int idenDoPolitico[MAX]){
	
	int politico = 0, empresa = 0;
	float juros = (1+(JNDPE[0]/100));
	float jurosCalculado[MAX][MAX];
	
	for(politico = 0; politico < JNDPE[1]; politico++){
		printf("%d:: ", idenDoPolitico[politico]);
		for(empresa = 0; empresa < JNDPE[2]; empresa++){	
			jurosCalculado[politico][empresa] = pow(juros, parcela[politico][empresa]);
			proprinaCalculada[politico][empresa] = jurosCalculado[politico][empresa]*proprina[politico][empresa];
			printf("%.2f ", proprinaCalculada[politico][empresa]);
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}
//============================================================================================================================================================================
void totalPagoPorEmpresa(float proprinaCalculada[MAX][MAX], float totalPagoEmpresa[MAX], float JNDPE[2]){
	int politico, empresa;
	float soma = 0;
	
	for(politico = 0; politico < JNDPE[1]; politico++){
		soma = 0;
		for(empresa = 0; empresa < JNDPE[2]; empresa++){
			soma += proprinaCalculada[empresa][politico];
		}
		totalPagoEmpresa[politico] = soma;
		printf("\nTotal pago por empresa: %.2f", totalPagoEmpresa[politico]);
	}
	printf("\n\n");
}
//============================================================================================================================================================================
void totalRecebidoPorPolitico(float proprinaCalculada[MAX][MAX], float totalRecebido[MAX], float JNDPE[2]){
	int i = 0, j = 0;
	float soma = 0;
	
	for(i = 0; i < JNDPE[1]; i++){
		soma = 0;	
		for(j = 0; j < JNDPE[2]; j++){
			printf(" %.2f ", proprinaCalculada[i][j]);
			soma += proprinaCalculada[i][j];
		}
		totalRecebido[i] = soma;
		printf("T <%.2f>\n", totalRecebido[i]);
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
	printf("\aAté a proxima\n");
	system("exit");
}
/*===========================================================================================================================================================================*/
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
//===========================================================================================================================================================================
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
//=============================================================================================================================================================================
int verificaColuna(char arquivo[], float JNDPE[2]){
	float politico = JNDPE[1];
	float empresa = JNDPE[2];
	float numDeColuna = 0, numCorretoDeColuna = 0;
	char ch;
	
	FILE *coluna = fopen(arquivo, "r");
	while((ch = fgetc(coluna))!= EOF)
		if (ch == ' ')
			numDeColuna++;
		printf("%d\n", numDeColuna);
	numCorretoDeColuna = politico * empresa + ((empresa - 1) * politico);
		printf("%f\n", politico);
		printf("%f\n", empresa);
		printf("%d\n", numCorretoDeColuna);
	if (numDeColuna != numCorretoDeColuna){
		printf("Formato do arquivo incorreto\n");
		printf("Verifique a quantidade de elementos(colunas) do seu arquivo\n");
		printf("E tente novamente\n");
		return TRUE;
	}
	else 
		return FALSE;
	fclose(coluna);
}
//=============================================================================================================================================================================
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
