/*******************************************************************************
Autor:Uellington Da Concei��o Damasceno

Componente Curricular: Algoritmos I

Concluido em: 

Declaro que este c�digo foi elaborado por mim de forma individual e n�o cont�m nenhum

trecho de c�digo de outro colega ou de outro autor, tais como provindos de livros e

apostilas, e p�ginas ou documentos eletr�nicos da Internet. Qualquer trecho de c�digo

de outra autoria que n�o a minha est� destacado com uma cita��o para o autor e a fonte

do c�digo, e estou ciente que estes trechos n�o ser�o considerados para fins de avalia��o.
******************************************************************************************//*
MANO, LEK, CABE�A E CABE�AS VC N�O TEM NO�AO DE COMO EU ESTOU PUTAMENTE FELIZ. 
NAS VERS�ES ANTERIORES A ESSA HAVIA UM PUTA BUG DO CARALHO QUE SEMPRE IMPEDIA QUE OS 
CALCULOS FOSSEM FEITOS DA MANEIRA CORRETA. ENFIM... DEPOIS DE MUITO TRABALHO DESCOBRIR 
QUE O PROBLEMA ERA UM FUCK "%d" QUE ESTAVA NO LUGAR ERRADO. BOM TECNICAMENTE ERA PARA 
TER UM "%f" ENFIM... OS VALORES AGORA EST�O CORRETOS E NA PROXIMA VERS��O SER� IMPLEMENTADO 
UMA MANEIRA DE RETORNAR OS VALORES CALCULADOS E EM SEGUIDA CALCULAR QUAL O POLITICO QUE MAIS 
RECEBEU PROPRINA.
VLWS FLWS... 

nessa vers�o eu descobir que n�o havia reoslvido o problema, na verdade eu so achei a solu��o para metade do problema 
agora apreceu o seguinte problema: matriz proprina tem cinco colunas ja a matriz juros calculado so tem 4 colunas. eu 
preciso retirar a coluna 0 da matriz proprina na hora de fazer o calculo. 

mano para resolver esse problema eu tive que utilizar algo muito simples que era ter que mutiplicar a segunda matres sempre com o 
valor de j - 1; bom o problema foi resolvido e na proxima vers�o ir� ter uma refatora��o do codigo. 
e para completar verifica��o de acomlagem. 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>
#include <math.h>
int main(){
	//sess�o onde todas as fun��es utilizadas s�o informadas para a fun��o prinicipal
	char recebeNome();
	int verificaSeVazio();
	int verificaLayout();
	int carregaConteudo();
	void fecharPrograma();
	//=========================================
	//variaveis utilizadas na fun��o principal
	int tentarNarquivo = 0, valido = 0, vazio = 0;
	char nomeArquivo[100];
	
	do{
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
			else 
				carregaConteudo(nomeArquivo);
	}while(tentarNarquivo == 1);
}
//===========================================================================================================================================================================
char recebeNome(char nomeArquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E CARREGA-LO;
	printf("Digite o nome de arquivo: ");
	gets(nomeArquivo);
	
	return *nomeArquivo;

}
//============================================================================================================================================================================
void fecharPrograma(){
	setlocale(LC_ALL, "portuguese");
	system("cls");
	printf("At� a proxima\n");
	system("exit");
}
/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
int verificaSeVazio(char arquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E SE ELE � VALIDO.
	int resposta = 0;
	int numeroDeLinha = 1;//come�a com o valor um por na grande maioria das vezes os arquivos n�o tem o new line na ultima linha
	
	FILE *numeroLinha = fopen(arquivo, "r");//abre o arquivo em modo de leitrua para verificar quantas linhas tem;
	if(numeroLinha == NULL){
		printf("Arquivo n�o encontrado ou n�o � valido\nTente novamente\n");
		do{
			printf("Gostaria de tentar com outro arquivo\n");
			printf("SIM___(01)               N�O____(02)\n");	
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
int carregaConteudo(char ARQ[]){
	
	float juros = 0, proprina[50][50], jurosCalculado[50][50];
	int numeroDePolitico = 0, numeroDeEmpresa = 0, i, j, parcela[50][50];
	char ch;
	
	FILE *pegarNoArquivo = fopen(ARQ, "r");
	
	fscanf(pegarNoArquivo, "%f", &juros);//leitura e armazenamento das informa��es contidas no arquivo.
	fscanf(pegarNoArquivo, "%d", &numeroDePolitico);
	fscanf(pegarNoArquivo, "%d", &numeroDeEmpresa);	
	printf("%f\n", juros);
	printf("%d\n", numeroDePolitico);
	printf("%d\n", numeroDeEmpresa);
	for(i = 0; i < numeroDePolitico; i++){//responsavel por correr as linhas do arquivo
		for(j = 0; j <= numeroDeEmpresa; j++){//responsavel por correr as colunas 
			fscanf(pegarNoArquivo, "%f", &proprina[i][j]);//responsavel por armazenar os valores que est�o em na posi��o i e j...
			if (proprina[i][j] == proprina[i][0])
				printf("%.0f ", proprina[i][j]);//imprime os valores na tela...
			else 
				printf("%.2f  ", proprina[i][j]);
		}
		printf("\n");
	}
	juros = (1+(juros/100));
	for(i = 0; i < numeroDePolitico; i++){
		for(j = 0; j < numeroDeEmpresa; j++){					
			fscanf(pegarNoArquivo, "%d", &parcela[i][j]);
			printf("%d ", parcela[i][j]);
		}
	printf("\n");
	}
	int  n = 0;
	printf("\n JUROS CALCULADO\n\n");		
	for(i = 0; i < numeroDePolitico; i++){
		for(j = 0; j <= numeroDeEmpresa; j++){
			if(proprina[i][j] == proprina[i][0])
				printf("%.0f :: ", proprina[i][j]);
			else{
				jurosCalculado[i][j] = pow(juros, parcela[i][j - 1]);
				//printf("{%.2f} [%.2i]", jurosCalculado[i][j], parcela[i][j - 1]);
				//printf(" %.2f * (%.2f) = %.2f", proprina[i][j], jurosCalculado[i][j], (proprina[i][j]*jurosCalculado[i][j]));
				printf(" {%.2f} ", jurosCalculado[i][j]*proprina[i][j]);
			}	
		}
		printf("\n");
	}
	fclose(pegarNoArquivo);
}

