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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <locale.h>

char menuDeCarregamento(char nomeArquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E CARREGA-LO;
    int repetirArquivo = 0;
	
	setlocale(LC_ALL, "portuguese");
	
	FILE *verificaArquivo;	
		do{
			repetirArquivo = 0;
			printf("Digite o nome de arquivo: ");
			gets(nomeArquivo);
        	system("cls");
			fflush(stdin);
			verificaArquivo = fopen(nomeArquivo, "r");
        	if (verificaArquivo == NULL){
				printf("Arquivo não encontrado\nTente novamente\n");
				repetirArquivo = 1;
			}
        	else{
        		printf("Arquivo encontrado com sucesso\n");
        		verificaArquivo = fopen(nomeArquivo, "r");
        		int i = 0, j = 0, numDePolitico = 0, numDeEmpresa = 0;
        		int numDeParcela [50][50];
        		float valorDeProprina [50][50];
				float J = 0;
        		fscanf(verificaArquivo, "%f", &J);
        		printf("%f", J);
        		fscanf(verificaArquivo, "%d", &numDePolitico);
        		printf("%d", numDePolitico);
        		fscanf(verificaArquivo,"%d", numDeEmpresa);
        		printf("%d", numDeEmpresa);
        			for(i ; i < valorDeProprina ; i++){
        				for(j ; j < valorDeProprina ; j++){
        					fscanf(verificaArquivo, "%d\t", valorDeProprina [i][j]);
        					printf("%f\t", valorDeProprina [i][j]);
						}
					}
        		return *nomeArquivo;
			}
		}while(repetirArquivo == 1);
	fclose (verificaArquivo);
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int validacaoLinha(char arquivo){
	int quantidadeLinha = 0;
	int resposta = 0;
	
	//FILE *numeroLinha = fopen(arquivo, "r");//abre o arquivo em modo de leitrua para verificar quantas linhas tem;
	//if(numeroLinha == NULL){
	//	printf("O arquivo esta vazio\n");
	//}
	//else
	//	printf("arquivo valido\n");
	do{
		printf("Gostaria de tentar com outro arquivo\n");
		printf("SIM___(01)               NÂO____(02)\n");	
		scanf("%d", &resposta);
		fflush(stdin);
		if (resposta == 1)
			return 1;
		else if(resposta == 2){
			printf("Até aproxima\n");
			system("exit");
		} 
		else
			printf("Escolha invalida\nTente novamente\n\n");
	}while(resposta < 1 || resposta > 2);	
	//fclose (numeroLinha);
	//return numeroLinha;
}
int main(){
	int tentarNarquivo = 0;
	do{
		char nomeArquivo[100];
		menuDeCarregamento(nomeArquivo);
		int numeroLinha = validacaoLinha(nomeArquivo);
		if (numeroLinha = 1);
			tentarNarquivo = 1;   
	}while(tentarNarquivo == 1);
}
