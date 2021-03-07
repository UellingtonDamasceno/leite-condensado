/*******************************************************************************
Autor:Uellington Da Concei��o Damasceno

Componente Curricular: Algoritmos I

Concluido em: 

Declaro que este c�digo foi elaborado por mim de forma individual e n�o cont�m nenhum

trecho de c�digo de outro colega ou de outro autor, tais como provindos de livros e

apostilas, e p�ginas ou documentos eletr�nicos da Internet. Qualquer trecho de c�digo

de outra autoria que n�o a minha est� destacado com uma cita��o para o autor e a fonte

do c�digo, e estou ciente que estes trechos n�o ser�o considerados para fins de avalia��o.
******************************************************************************************/
/*=============================IDENTIFICA��O DO BUG========================================
OBSERVA��O:
	BOM, O BUG CONSISTE NO FATO DE QUE APESAR DOS CALCULOS ESTAREM SENDO FEITOS DA MANEIRA CORRETA 
O PROGRAMA TRAVA POR ALGUM MOTIVO AO FINAL. 	

FATO:
	O PROGRAMA N�O TERMINA A EXECU��O DA FUN��O "VALORTOTALPAGO".
	O COM CERTEZA O SOFTWARE SAI DO DO ULTIMO LA�O DA FUN��O ACIMA;
	O PROBLEMA ACONTECE ENTRE O FINAL DA EXECU��O DA FUN��O E O RETORNO PARA A FUN��O PRINCIPAL. 
	
VARIANTES: 
	SEM VARIANTE;
CONCLUS�O:
	BOM TUDO COME�A QUANDO EU ESQUE�O DE PASSAR UM DOS PARAMETROS. JUSTO O QUE PRECISAVA SER RETORNADO.
ENFIM SO PRECISEI PASSAR A MATRIZ QUE ESTAVA RECEBENDO O VALOR DA PROPRINA CALCULADA.

BUG:
	valorTotalPago(parcela, proprina, JNDPE);

BUG CORRIGIDO:
	valorTotalPago(parcela, proprina, JNDPE, proprinaCalculada);
==========================================================================================*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>

int main(){
//=======SESS�O DE DECLARA��O DE FUN��ES=======

	char recebeNome();
	int verificaSeVazio();
	int verificaLayout();
	void carregaConteudo();
	int valorTotalPago();
	void totalPagoPorEmpresa();
	void totalRecebidoPorPolitico();
	//void imprimaConteudo();
	void fecharPrograma();

//====VARI�VEIS USADAS NA FUN��O PRINCIPAL======	

	float JNDPE [2], proprina[50][50], jurosCalculado[50][50], proprinaCalculada[50][50];
	float poliMaisDin[2], poliMenosDin[2], empreMaisDin[2], empreMenosDin[2], totalPagoEmpresa[50];
	float totalRecebido[50], infoDoPolitico[3];
	int numeroDePolitico = 0, numeroDeEmpresa = 0, parcela[50][50];
	int pedirNovoArquivo = 0, devePedir = 0;
	char nomeArquivo[100];

//=============INICIO DAS INSTRU��ES=============	
	do{
		pedirNovoArquivo = 0; //EVITAR LOOP INFINITO.
		
		recebeNome(nomeArquivo);
		devePedir = verificaSeVazio(nomeArquivo);
		if(devePedir == 0)
			pedirNovoArquivo = 1;
		else if (devePedir == 1)
			fecharPrograma();
		else 	
			devePedir = verificaLayout(nomeArquivo);
			if(devePedir == 0)
				pedirNovoArquivo = 1;
			else if(devePedir == 1)
				fecharPrograma();
			else
				carregaConteudo(nomeArquivo, parcela, proprina, JNDPE);
		valorTotalPago(parcela, proprina, JNDPE, proprinaCalculada);
		totalPagoPorEmpresa(proprinaCalculada, totalPagoEmpresa, JNDPE);
		totalRecebidoPorPolitico(proprinaCalculada, totalRecebido, JNDPE);
	}while(pedirNovoArquivo == 1);
}
//===========================================================================================================================================================================

void carregaConteudo(char ARQ[], int parcela[50][50], float proprina[50][50], float JNDPE[2]){
	
	int i = 0, j = 0;

	FILE *pegarNoArquivo = fopen(ARQ, "r");

	for(i = 0; i < 3; i++)
		fscanf(pegarNoArquivo, "%f", &JNDPE[i]);// responsavel por pegar o valor do juros e do numero de politicos e de empresas.
		
	for(i = 0; i < JNDPE[1]; i++)//responsavel por correr as linhas do arquivo
		for(j = 0; j <= JNDPE[2]; j++)//responsavel por correr as colunas 
			fscanf(pegarNoArquivo, "%f", &proprina[i][j]);//responsavel por armazenar os valores que est�o em na posi��o i e j...
	
	for(i = 0; i < JNDPE[1]; i++)
		for(j = 0; j < JNDPE[2]; j++)					
			fscanf(pegarNoArquivo, "%d", &parcela[i][j]);
			
	fclose(pegarNoArquivo);

}
//====================================================================================================================================================================================
int valorTotalPago(int parcela [50][50], float proprina [50][50], float JNDPE[2], float proprinaCalculada[50][50]){
	
	int i = 0, j = 0;
	float jurosCalculado [50][50];
	float juros = (1+(JNDPE[0]/100));

	for(i = 0; i < JNDPE[1]; i++){
		for(j = 0; j <= JNDPE[2]; j++){
			if(j == 0)
				continue;
			else{
				jurosCalculado[i][j] = pow(juros, parcela[i][j - 1]);
				proprinaCalculada[i][j - 1] = jurosCalculado[i][j]*proprina[i][j];
			}	
		}
	}
	return 0;
}
//==================================================================================================================================================================================
void totalPagoPorEmpresa(float proprinaCalculada[50][50], float totalPagoEmpresa[50], float JNDPE[2]){
	int politico, empresa;
	float soma = 0;
	
	for(politico = 0; politico < JNDPE[1]; politico++){
		soma = 0;
		for(empresa = 0; empresa < JNDPE[2]; empresa++){
			soma += proprinaCalculada[empresa][politico];
		}
		totalPagoEmpresa[politico] = soma;
	}
}
void totalRecebidoPorPolitico(float proprinaCalculada[50][50], float totalRecebido[50], float JNDPE[2]){
	int i = 0, j = 0;
	float soma = 0;
	
	for(i = 0; i < JNDPE[1]; i++){
		soma = 0;	
		for(j = 0; j < JNDPE[2]; j++){
			soma += proprinaCalculada[i][j];
			printf("%.2f}}} ", soma);
		}
		printf("\n");
		totalRecebido[i] = soma;
	}		
}
/*void imprimaConteudo(int parcela[50][50], float proprina[50][50], float JNDPE[2]){
	
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
	printf("At� a proxima\n");
	system("exit");
}

/*===========================================================================================================================================================================*/

int verificaSeVazio(char arquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E SE ELE � VALIDO.
	int resposta = 0;
	int numeroDeLinha = 1;
	
	FILE *numeroLinha = fopen(arquivo, "r");//abre o arquivo em modo de leitrua para verificar quantas linhas tem;
	if(numeroLinha == NULL){
		printf("Arquivo n�o encontrado ou nao � valido\nTente novamente\n");
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
	if(numeroDeLinha % 2 == 0){// Pelo fato do arquivo correto sempre deve ter um numero impar de linhas. essa verifica��o existe
		do{
			printf("\nFormato de arquivo incorreto\nGostaria e tentar com outro arquivo?\n");
			printf("SIM___(01)           N�O___(02)\n");
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

