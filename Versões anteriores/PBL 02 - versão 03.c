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
	BOM, O BUG CONSISTE NO FATO DE QUE APESAR DOS CALCULOS ESTAREM SENDO FEITOS DA MANEIRA CORRETA 
O PROGRAMA TRAVA POR ALGUM MOTIVO AO FINAL. 	

FATO:
	O PROGRAMA NÃO TERMINA A EXECUÇÃO DA FUNÇÃO "VALORTOTALPAGO".
	O COM CERTEZA O SOFTWARE SAI DO DO ULTIMO LAÇO DA FUNÇÃO ACIMA;
	O PROBLEMA ACONTECE ENTRE O FINAL DA EXECUÇÃO DA FUNÇÃO E O RETORNO PARA A FUNÇÃO PRINCIPAL. 
	
VARIANTES: 
	SEM VARIANTE;
CONCLUSÃO:
	BOM TUDO COMEÇA QUANDO EU ESQUEÇO DE PASSAR UM DOS PARAMETROS. JUSTO O QUE PRECISAVA SER RETORNADO.
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
//=======SESSÃO DE DECLARAÇÃO DE FUNÇÕES=======

	char recebeNome();
	int verificaSeVazio();
	int verificaLayout();
	void carregaConteudo();
	int valorTotalPago();
	void totalPagoPorEmpresa();
	void totalRecebidoPorPolitico();
	//void imprimaConteudo();
	void fecharPrograma();

//====VARIÁVEIS USADAS NA FUNÇÃO PRINCIPAL======	

	float JNDPE [2], proprina[50][50], jurosCalculado[50][50], proprinaCalculada[50][50];
	float poliMaisDin[2], poliMenosDin[2], empreMaisDin[2], empreMenosDin[2], totalPagoEmpresa[50];
	float totalRecebido[50], infoDoPolitico[3];
	int numeroDePolitico = 0, numeroDeEmpresa = 0, parcela[50][50];
	int pedirNovoArquivo = 0, devePedir = 0;
	char nomeArquivo[100];

//=============INICIO DAS INSTRUÇÕES=============	
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
			fscanf(pegarNoArquivo, "%f", &proprina[i][j]);//responsavel por armazenar os valores que estão em na posição i e j...
	
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

