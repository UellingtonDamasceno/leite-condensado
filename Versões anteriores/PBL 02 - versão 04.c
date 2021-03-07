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
#include <locale.h>
#include <math.h>

#define MAX 50
#define TRUE 1
#define FALSE 0
int main(){
//=======SESSÃO DE DECLARAÇÃO DE FUNÇÕES=======

	char recebeNome();
	int verificaSeVazio();
	int verificaLayout();
	void carregaConteudo();
	int valorTotalPago();
	void totalPagoPorEmpresa();
	void totalRecebidoPorPolitico();
	void PmaisEmenosPago();
	void MeMPCeSJ();
	//void empresaQueMaisPagou();
	//void empresaQueMenosPagou();
	//void imprimaConteudo();
	void fecharPrograma();

//====VARIÁVEIS USADAS NA FUNÇÃO PRINCIPAL======	

	float JNDPE [2], proprina[MAX][MAX], jurosCalculado[MAX][MAX], proprinaCalculada[MAX][MAX];
	float poliMaisDin[3], poliMenosDin[3], empreMaisDin[3], empreMenosDin[3], totalPagoEmpresa[MAX];
	float totalRecebido[MAX], parcela[MAX][MAX], idenDoPolitico[MAX];
	int pedirNovoArquivo = 0, devePedir = 0;
	char nomeArquivo[MAX]; 

//=============INICIO DAS INSTRUÇÕES=============	
	do{
		pedirNovoArquivo = FALSE; //EVITAR LOOP INFINITO.
		
		recebeNome(nomeArquivo);
		devePedir = verificaSeVazio(nomeArquivo);
		if(devePedir == FALSE)
			pedirNovoArquivo = TRUE;
		else if (devePedir == TRUE)
			fecharPrograma();
		else{	
			devePedir = verificaLayout(nomeArquivo);
			if(devePedir == FALSE)
				pedirNovoArquivo = TRUE;
			else if(devePedir == TRUE)
				fecharPrograma();
			else{
				carregaConteudo(nomeArquivo, parcela, proprina, JNDPE);
				valorTotalPago(proprinaCalculada, parcela, proprina, JNDPE, idenDoPolitico, jurosCalculado);
				totalPagoPorEmpresa(proprinaCalculada, totalPagoEmpresa, JNDPE);
				totalRecebidoPorPolitico(proprinaCalculada, totalRecebido, JNDPE);
				PmaisEmenosPago(totalRecebido, idenDoPolitico, poliMaisDin, poliMenosDin, JNDPE);
				MeMPCeSJ(totalRecebido, proprina, JNDPE);
				printf("\nchegou ao final\n");
			}
		}
	}while(pedirNovoArquivo == TRUE);
}
//===========================================================================================================================================================================
void MeMPCeSJ(float totalRecebido[MAX], float proprina[MAX][MAX], float JNDPE[2]){//maior e menor proprina, com e sem juros.
	float somaDaProprina[MAX], soma = 0;
	int empresa = 0, politico = 0;

	for(politico = 0; politico < JNDPE[1]; politico++){
		soma = 0;
		for(empresa = 0; empresa < JNDPE[2]; empresa++){
			soma += proprina[politico][empresa - 1];
		}
		somaDaProprina[politico] = soma;
		printf("\nTotal dos juros pagos: %.2f", somaDaProprina[politico]);
	}
}
//===========================================================================================================================================================================
void PmaisEmenosPago(float totalRecebido[MAX], float idenDoPolitico[MAX], float poliMaisDin[3], float poliMenosDin[3], float JNDPE[2]){
	int igual = 0, politico = 0;
	
	poliMaisDin [2] = -99999999;
	poliMenosDin [2] = 999999999;
	
	
	for(politico = 0; politico < JNDPE[2]; politico++){
		printf("%.2f      ", totalRecebido[politico]);
		if (totalRecebido[politico] > poliMaisDin[2]){
			poliMaisDin[0] = idenDoPolitico[politico];//atribue a identificação do politico que mais recebeu proprina
			poliMaisDin[2] = totalRecebido[politico];//atribue o maior valor de proprina recebida
			
		}
		else if(totalRecebido[politico] < poliMenosDin[2]){
			poliMenosDin[0] = idenDoPolitico[politico];//atribue a identificação do politico que menos recebeu propina
			poliMenosDin[2] = totalRecebido[politico];//atribue o menor valor de proprina recebida 
		}
	}
	
	printf("\n\nO politico %.0f recebeu a maior quantia de dinherio: %.2f\n", poliMaisDin[0], poliMaisDin[2]);
	printf("O politico %.0f recebeu a menor quantia de dinherio: %.2f\n", poliMenosDin[0], poliMenosDin[2]);
}
//===========================================================================================================================================================================
void carregaConteudo(char ARQ[], int parcela[MAX][MAX], float proprina[MAX][MAX], float JNDPE[2]){
	
	int i = 0, j = 0;

	FILE *pegarNoArquivo = fopen(ARQ, "r");

	for(i = 0; i < 3; i++)
		fscanf(pegarNoArquivo, "%f", &JNDPE[i]);// responsavel por pegar o valor do juros e do numero de politicos e de empresas.
		
	for(i = 0; i < JNDPE[1]; i++)//responsavel por correr as linhas do arquivo
		for(j = 0; j <= JNDPE[2]; j++)//responsavel por correr as colunas 
			fscanf(pegarNoArquivo, "%f", &proprina[i][j]);//responsavel por armazenar os valores que estão em na posição i e j...
	
	for(i = 0; i < JNDPE[1]; i++)
		for(j = 0; j < JNDPE[2]; j++)					
			fscanf(pegarNoArquivo, "%d", &parcela[i][j]);
			
	fclose(pegarNoArquivo);

}
//====================================================================================================================================================================================
int valorTotalPago(float proprinaCalculada[MAX][MAX], int parcela[MAX][MAX], float proprina[MAX][MAX], float JNDPE[2] , float idenDoPolitico[MAX], float jurosCalculado[MAX][MAX]){
	
	int politico = 0, empresa = 0;
	float juros = (1+(JNDPE[0]/100));

	for(politico = 0; politico < JNDPE[1]; politico++){
		for(empresa = 0; empresa <= JNDPE[2]; empresa++){
			if(empresa == 0){
				idenDoPolitico[politico] = proprina[politico][empresa];
				printf("%.0f  ", idenDoPolitico[politico]);
			}
			else{
				jurosCalculado[politico][empresa] = pow(juros, parcela[politico][empresa - 1]);
				proprinaCalculada[politico][empresa - 1] = jurosCalculado[politico][empresa]*proprina[politico][empresa];
				printf("%.2f ", proprinaCalculada[politico][empresa - 1]);
			}	
		}
		printf("\n");
	}
	printf("\n");
	return 0;
}
//==================================================================================================================================================================================
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
	printf("\n");
}
//=================================================================================================================================================================================
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
//==================================================================================================================================================================================
/*void imprimaConteudo(int parcela[MAX][MAX], float proprina[MAX][MAX], float JNDPE[2]){
	
	int i = 0, j = 0;
	
	for(i = 0; i < 3; i++){
		if (i == 0)
			printf("%f\n", JNDPE[i]);
		else 
			printf("%.0f\n", JNDPE[i]);
	}
	
	for(i = 0; i < JNDPE[1]; i++){
		for(j = 0; j <= JNDPE[2]; j++){
			if(j == 0)
				printf("%.0f:: ", proprina[i][j]);
			else
				printf("%.2f ", proprina[i][j]);
		}
		printf("\n");
	}
		
	for(i = 0; i < JNDPE[1]; i++){
		for(j = 0;j <= JNDPE[2]; j++){
			printf("%d ", parcela[i][j]);
		}
		printf("\n");
	}
}*/

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
		printf("Arquivo nao encontrado ou nao er valido\nTente novamente\n");
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
			printf("SIM___(01)           NAO___(02)\n");
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

