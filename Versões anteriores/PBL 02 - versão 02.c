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
	NESSE MOMENTO ESTOU TENTANDO CALCULAR O JUROS COMPOSTO DA PROPRINA. ATE ENT�O 
TODOS OS VALORES QUE EST�O SENDO PASSADOS PARA A FUN��O QUE VAI CALCULAR EST�O CORRETOS.
E DIANTE DISSO N�O SEI POR QUAL MOTIVO O PROGRAMA SO ESTA CALCULANDO A PRIMEIRA LINHA DO DA PROPRINA. 
	
	SE O CALCULO ACONTECER DENTRO DO PRINTF FUNCIONA NORMALMENTE POREM SE OS CALCULOS OCORRE 
FORA DO PRINTF E ATRIBUIR O RESULTADO A UMA TECEIRA MARTRIZ N�O FUNCIONA A PARTIR DA SEGUNDA EXECU��O
EX:
	FUNCIONA
		PRINTF("%F", JUROS + ALGUMACOISA);
	N�O FUNCIONA
		X = JUROS + ALGUMACOISA;
		PRINTF("%F", X);

FATO:
		ESTA CONFIRMADO: O PROBLEMA ACONTECE QUANDO TENTO ATRIBURIR O VALOR 
	A MATRIZ QUE PASSO COMO PARAMETRO. 
		OS VALORES QUE EST�O COMANDANDO O LA�O DOS LA�OS FORS EST�O CORRETOS.
		O CALCULO DO JUROS EST� CORRETO.
	ATRAVES DOS TESTE FOI POSSIVEL OBSERVAR QUE O VALOR DA PROPRINA E DO JUROS 
		CALCULADO EST�O CORRETOS.
	
VARIANTES: 
		TODOS OS TESTE FORAM FEITOS SEM NENHUMA VARIANTE OU SEJA ALTERANDO UM VALOR 
	ESPECIFICO QUE N�O DEPENDE DE OUTROS.

CONCLUS�O:
		O BUG ACONTECIA POR QUE EXISTIA UMA COLUNA DA MATRIZ DA PROPRINA QUE CONTIA A IDENTIFICA��O 
	DO POLITICO, E DIANTE DISSO NA HORA DE FAZER O CALCULO ESSA COLUNA FOI IGNORADA. POREM NA 
	HORA DE IMPRIMIR O VALOR ESQUECIA DE IGNORAR ESSSA COLUNA E CONSEQUENTMENTE IMPRIMIA UM VALOR 
	LIXO. QUE POR ALGUM MOTIVO TRAVAVA O SOFTWARE. 

	ENFIM PARA RESOLVER O BUG SO PRECISEI PRINTAR OS VALORES COM O VALOR DE J SEMPRE COM -1 

BUG:
	for(i = 0; i < JNDPE[1]; i++){
		for(j = 0; j <= JNDPE[2]; j++){
			if(j == 0)
				printf("%.0f :: ", proprina[i][j]);
			else{
				jurosCalculado[i][j] = pow(juros, parcela[i][j - 1]); // NESSSA LINHA ELIMINAVA A COLUNA DOS POLITICOS
		TESTE 001	printf("{%.2f} [%.2i]", jurosCalculado[i][j], parcela[i][j - 1]);
		TESTE 002	printf(" %.2f * (%.2f) = %.2f", proprina[i][j], jurosCalculado[i][j], (proprina[i][j]*jurosCalculado[i][j]));
				proprinaCalculada[i][j - 1] = jurosCalculado[i][j]*proprina[i][j];
				printf("[%.2f] ", proprinaCalculada[i][j]);// E NESSSA MANDAVA IMPRIMIR O VALOR ERRDO
			}	
		}
		printf("\n");
	}
BUG CORRIGIDO:
	for(i = 0; i < JNDPE[1]; i++){
		for(j = 0; j <= JNDPE[2]; j++){
			if(j == 0)
				printf("%.0f :: ", proprina[i][j]);
			else{
				jurosCalculado[i][j] = pow(juros, parcela[i][j - 1]);
				//printf("{%.2f} [%.2i]", jurosCalculado[i][j], parcela[i][j - 1]);
				//printf(" %.2f * (%.2f) = %.2f", proprina[i][j], jurosCalculado[i][j], (proprina[i][j]*jurosCalculado[i][j]));
				proprinaCalculada[i][j - 1] = jurosCalculado[i][j]*proprina[i][j];
				printf("[%.2f] ", proprinaCalculada[i][j - 1]); //CORRE��O DO BUG
			}	
		}
		printf("\n");
	}
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
	void valorTotalPago();
	//void imprimaConteudo();
	void fecharPrograma();

//====VARI�VEIS USADAS NA FUN��O PRINCIPAL======	

	float JNDPE [2], proprina[50][50], jurosCalculado[50][50], proprinaCalculada[50][50];
	int numeroDePolitico = 0, numeroDeEmpresa = 0, parcela[50][50];
	int pedirNovoArquivo = 0, devePedir = 0;
	char nomeArquivo[100];
	int i, j;

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
			else{ 
				//printf("-infor - %f\ninfor - %f\ninfor - %f\n",JNDPE[0], JNDPE[1], JNDPE[2]);
				carregaConteudo(nomeArquivo, parcela, proprina, JNDPE);
				valorTotalPago(parcela, proprina, JNDPE);
				//imprimaConteudo(parcela, proprina, JNDPE);
			}
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
void valorTotalPago(int parcela [50][50], float proprina [50][50], float JNDPE[2], float proprinaCalculada[50][50]){
	int i = 0, j = 0;
	float jurosCalculado [50][50];
	float juros = (1+(JNDPE[0]/100));

	for(i = 0; i < 3; i++){
		if (i == 0)
			printf("%f\n", JNDPE[i]);
		else 
			printf("%.0f\n", JNDPE[i]);
	}
	for(i = 0; i < JNDPE[1]; i++){
		for(j = 0; j <= JNDPE[2]; j++){
			if(j == 0)
				printf("%.0f :: ", proprina[i][j]);
			else{
				jurosCalculado[i][j] = pow(juros, parcela[i][j - 1]);
				//printf("{%.2f} [%.2i]", jurosCalculado[i][j], parcela[i][j - 1]);
				//printf(" %.2f * (%.2f) = %.2f", proprina[i][j], jurosCalculado[i][j], (proprina[i][j]*jurosCalculado[i][j]));
				proprinaCalculada[i][j - 1] = jurosCalculado[i][j]*proprina[i][j];
				printf("[%.2f] ", proprinaCalculada[i][j - 1]);
			}	
		}
		printf("\n");
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

