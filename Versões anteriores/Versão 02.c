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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

char menuDeCarregamento(char nomeArquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E CARREGA-LO;
    int repetirArquivo = 0;
	
	setlocale(LC_ALL, "portuguese");
	
	FILE *verificaArquivo;	
		repetirArquivo = 0;
		printf("Digite o nome de arquivo: ");
		gets(nomeArquivo);
       	system("cls");
		fflush(stdin);
		verificaArquivo = fopen(nomeArquivo, "r");
		return *nomeArquivo;
		fclose (verificaArquivo);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int validacaoLinha(char arquivo[]){
	int resposta = 0;
	int numeroDeLinha = 1;//come�a com o valor um por na grande maioria das vezes os arquivos n�o tem o new line na ultima linha
	char caracter = NULL;
	
	FILE *numeroLinha = fopen(arquivo, "r");//abre o arquivo em modo de leitrua para verificar quantas linhas tem;
	if(numeroLinha == NULL){
		printf("Arquivo n�o encontrado ou n�o � valido\nTente novamente\n");
		do{
			printf("Gostaria de tentar com outro arquivo\n");
			printf("SIM___(01)               N�O____(02)\n");	
			scanf("%d", &resposta);
			fflush(stdin);
			if (resposta == 1)
				return 1;
			else if(resposta == 2)
				return 2;
			else
				printf("Escolha invalida\nTente novamente\n\n");
		}while(resposta < 1 || resposta > 2);
	}
	else{
		while((caracter = fgetc(numeroLinha))!= EOF){
			putchar(caracter);
			fflush(stdin);
			if(caracter == '\n')
				numeroDeLinha++;
		}
		if(numeroDeLinha % 2 == 0)// Pelo fato do arquivo correto sempre deve ter um numero impar de linhas. essa verifica��o existe
			do{
				printf("\nFormato de arquivo incorreto\nGostaria e tentar com outro arquivo?\n");
				printf("SIM___(01)           N�O___(02)\n");
				scanf("%d", &resposta);
				fflush(stdin);
				if (resposta == 1)
					return 1;
				else if(resposta == 2)
					return 2;
				else
					printf("Escolha invalida\nTente novamente\n");
			}while(resposta < 1 || resposta > 2);
		else
			return 0;		
	}
	fclose (numeroLinha);
	return numeroLinha;
}
/*int verificaColuna(char arquivo[]){
	int numCempresa = 0, resposta = 0;
	char caracter;
	
	FILE *numeroColuna = fopen(arquivo, "r");
	while((caracter = fgetc(numeroColuna))!= EOF){
		if(caracter == ' ')
			++numCempresa;
	}
}*/
int carregaConteudo(char nomeArquivo){
	float juros = 0, proprina[50][50];
	int numeroDePolitico = 0, numeroDeEmpresa = 0, i, j;
	FILE *pegarNoArquivo = fopen(nomeArquivo, "r");
	fscanf(pegarNoArquivo, "%f", &juros);//leitura e armazenamento das informa��es contidas no arquivo.
	printf("%f\n", juros);
	fscanf(pegarNoArquivo, "%d", &numeroDePolitico);
	printf("%d\n", numeroDePolitico);
	fscanf(pegarNoArquivo, "%d", &numeroDeEmpresa);
	printf("%d\n", numeroDeEmpresa);
	for(i = 0; i < numeroDePolitico; i++){//responsavel por correr as linhas do arquivo
		for(j = 0; j < numeroDeEmpresa; j++){//responsavel por correr as colunas 
			fscanf(pegarNoArquivo, "%f", &proprina[i][j]);//responsavel por armazenar os valores que est�o em na posi��o i e j...
			if (proprina[i][j] == proprina[i][0])
				printf("%.0f ", proprina[i][j]);//imprime os valores na tela...
			else 
				printf("%.2f\t", proprina[i][j]);
		}
		printf("\n");
	}
	fclose(pegarNoArquivo);
}
int main(){
	int tentarNarquivo = 0;
	do{
		char nomeArquivo[100];
		menuDeCarregamento(nomeArquivo);
		int numeroLinha = validacaoLinha(nomeArquivo);
		if (numeroLinha == 1)
			tentarNarquivo = 1;
		else if(numeroLinha == 2){
			printf("At� a proxima\n");
					system("exit");
		}
		else
			carregaConteudo(nomeArquivo);
	}while(tentarNarquivo == 1);
}
