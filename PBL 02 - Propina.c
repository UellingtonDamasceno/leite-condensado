/*******************************************************************************
Autor:Uellington Da Conceição Damasceno

Componente Curricular: Algoritmos I

Concluido em: 28/06/2017 às 01:01 horas.

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
	char recebeNome(); //RESPONSAVEL POR RECEBER O NOME DO ARQUIVO
	int verificaSeVazio();//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E OU VAZIO;
	int verificaLinha();// FUNÇÃO DE VALIDAÇÃO. SERVE PARA VERIFICAR A QUANTIDADE DE LINHAS NO ARQUIVO.
	void carregaConteudo();//SERVE LER AS INFORMAÇÕES DO ARQUIVO E ARMAZENAR OS VALORES DAS VARIAVEIS
	int verificaTamanhoMatriz();//FUNÇÃO DE VALIDAÇÃO. SERVE PARA VERIFICAR SE A QUNTIDADE DE POLITICO OU EMPRESA ESTA NO LIMITE PRE-SUPOSTO.
	int verificaLetra();//FUNÇÃO DE VALIDAÇÃO. SERVE PARA VERIFICAR SE EXISTE ALGUMA LETRA NO MEIO DO ARQUIVO. 
	int verificaPonto();//FUNÇÃO DE VALIDAÇÃO. SERVE PARA VERIFICAR SE EXISTE ALGUM PONTO DESNECESSARIO NO MEIO DO ARQUIVO.
	int verificaColuna();//FUNÇÃO DE VALIDAÇÃO. SERVE PARA VERIFICAR SE EXISTE A QUANTIDADE CORRETA DE ELEMENTOS NO ARQUIVO.
	void calculaJuros();//FUNÇÃO DE CALCULO. SERVE PARA CAULULAR O VALOR DO JURO.
	void calculaProprina();//FUNÇÃO DE CALCULO. SERVE PARA CALCULAR O MONTANTE DA PROPRINA PAGA.
	void totalPagoPorEmpresa();//FUNÇÃO RESPONSAVEL POR SOMAR TODOS OS VALORES E RETORNAR O TOTAL PAGO POR POLITICO
	void maisEmenos();//FUNÇÃO RESPONSAVEL POR VERIFICAR QUAL FOI A EMPRESA/POLITICO QUE MAIS RECEBEU/PAGOU PROPRINA
	void calculaMedia();//RESPONSAVEL POR CALCULAR A MEDIA;
	void gerarArquivoP1();//FUNÇÃO RESPONSAVEL POR GERAR O ARQUIVO
	void gerarArquivoP2();
	void gerarArquivoP3();
	void sucesso();//FUNÇÃO USADA PARA INFORMAR AO USARIO QUE TODOS OS CALCULOS FORAM EXECULTADOS CORRETAMENTE.
	int erroMsn();//FUNÇÃO USADA PARA INFORMAR ALGUM ERRO.
	void fecharPrograma();//FUNÇÃO USADA PARA FECHAR O PROGRAMA.

void barraSup(int tamanho, int titulo, int centro){//serve para imprimir uma barra superior. algumas vezes pode imprimir o titulo da sessão 
	int i = 0;
	printf("\t\t\t\xC9");
	for(i = 0; i<tamanho; i++){
		if (i == centro){
			if(titulo == 1)
				printf("ERRO SEMANTICO");
			else if(titulo == 2)
				printf("ERRO SINTATICO");
			else if(titulo == 3)
				printf("ERRO");
			else if(titulo == 4)
				printf("\xCD\xCD\xCDRELATORIO\xCD\xCD");
			else if (titulo == 5)
				printf("MENU");
			else				
				printf("\xCD");
		}
		else
			printf("\xCD");
	}
	printf("\xBB\n\t\t\t");
}
//======================================================================================================================================================================================
void barraInf(int tamanho){//serve para imprimir uma barra inferior.
	int i = 0;
	printf("\t\t\t\xC8");
	for(i = 0; i < tamanho; i++)
		printf("\xCD");
	printf("\xBC\n");
}
//======================================================================================================================================================================================
int main(){
//====================VARIÁVEIS USADAS NA FUNÇÃO PRINCIPAL===========================

	char nomeArquivo[MAX];
	float JNDPE[2], propina[MAX][MAX], parcela[MAX][MAX]; //JNDPE = JUROS, NUMERO DE POLITO E EMPRESA,
	float propinaCalculada[MAX][MAX], propinaSJ[MAX], propinaCJ[MAX], jurosCalculado[MAX][MAX];//armazena os primeiros valores que devem ser calculados
	float EtotalPagoCJ[MAX], EtotalPagoSJ[MAX];// armazena os valores pagos pelas empresas com e sem juros;
	float mediaPoli[MAX], mediaEmpre[MAX];//armazena a media dos valores pagos/recebidos;
	float PmaisEmenosDin[7], EmaisEmenosDin[7];//armazena os valores do politico e da empresa que mais e menos receberam/pagaram proprina;
	int pedirNovoArquivo = 0, devePedir = 0, deuErro = FALSE, idenDoPolitico[MAX];// utilizadas como variaves de controle;

//=============INICIO DAS INSTRUÇÕES=============
	do{
		
		pedirNovoArquivo = FALSE; //EVITAR LOOP INFINITO.
		recebeNome(nomeArquivo); //FUNÇÃO RESPONSAVEL POR RECEBER O NOME DO ARQUIVO
		deuErro = verificaSeVazio(nomeArquivo);//verifica se o arquivo existe e ou vazio
		
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
				carregaConteudo(nomeArquivo, parcela, propina, JNDPE, idenDoPolitico);//carrega as informações do arquivo 
				deuErro = verificaLetra(nomeArquivo);//verifca se tem alguma letra no arquivo	
				
				if (deuErro == TRUE){
					devePedir = erroMsn();
					if(devePedir == TRUE)
						pedirNovoArquivo = TRUE;
					else
						fecharPrograma();
				}
				else{
					deuErro = verificaTamanhoMatriz(JNDPE);
				
					if (deuErro == TRUE){
						devePedir = erroMsn();
						if(devePedir == TRUE)
							pedirNovoArquivo = TRUE;
						else
							fecharPrograma();
					}
					else{
						deuErro = verificaPonto(nomeArquivo);//verifica se a não existe nenhum ponto na posição errada
						
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
								calculaProprina(propinaCalculada, jurosCalculado, propina, JNDPE, propinaSJ, propinaCJ);//calcula a proprina utilizando a formula de juro composto.
								totalPagoPorEmpresa(propinaCalculada, JNDPE, EtotalPagoCJ, propina, EtotalPagoSJ);//calcula o total de proprina pago por empresa
								maisEmenos(propinaCJ, propinaSJ, PmaisEmenosDin ,JNDPE, POLITICO, idenDoPolitico);//descobre qual politico recebeu mais e menos proprina
								maisEmenos(EtotalPagoCJ, EtotalPagoSJ, EmaisEmenosDin ,JNDPE , EMPRESA, idenDoPolitico);//descobre qual empresa mais e menos pagou proprina
								calculaMedia(propinaCJ, JNDPE, mediaPoli, POLITICO);//calcula a media do politico 
								calculaMedia(EtotalPagoCJ, JNDPE, mediaEmpre, EMPRESA);//calcula a media da empresa 
								gerarArquivoP1(JNDPE, idenDoPolitico, propinaCalculada, propinaCJ, EtotalPagoCJ);//gera a primeira parte do arquivo 
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
			}
		}
	}while(pedirNovoArquivo == TRUE);//USADO PARA PERMITIR QUE O USARIO INSIRA OUTRO ARQUIVO.
}
//======================================================================================================================================================================================
char recebeNome(char nomeArquivo[]){
	system("cls");
	printf("\t");
	barraSup(40, 0, 32);
	printf("\t\xBA    DIGITE O NOME DO ARQUIVO DESEJADO   \xBA\n");
	printf("\t");
	barraInf(40);
	printf("\t\t\t\t>>>");
	gets(nomeArquivo);

	return *nomeArquivo;
}
//======================================================================================================================================================================================
int verificaSeVazio(char arquivo[]){//RESPONSAVEL POR VERIFICAR SE O ARQUIVO EXISTE E SE ELE É VALIDO.

	FILE *numeroLinha = fopen(arquivo, "r");//abre o arquivo em modo de leitrua para verificar quantas linhas tem;
	if(numeroLinha == NULL){
		barraSup(47,4, 23);
		printf("\xBA\t    Arquivo nao encontrado ou nao er valido\t     \xBA\n");
		printf("\t\t\t\xBA\t\t\tTente novamente\t\t\t     \xBA\n");
		barraInf(60);
		return TRUE;
	}
	else
		return FALSE;
	fclose (numeroLinha);
}
//======================================================================================================================================================================================
int verificaLinha(char arquivo[]){

	int numeroDeLinha = 1, taErrado = 0;
	char ch, chAnterior;

	FILE *linhas = fopen(arquivo,"r");
		while((ch= fgetc(linhas))!= EOF){
			//putchar(ch); // caso deseje olhar a estrutura do arquivo inserido so tirar o comentario dessa linha.
			if(ch == '\n'){
				numeroDeLinha++;
				if (chAnterior == '\n' || chAnterior == ' ')
					taErrado++;
			}
			chAnterior = ch;
		}
	if(numeroDeLinha % 2 == 0 || taErrado >= 1){// Pelo fato do arquivo correto sempre deve ter um numero impar de linhas. essa verificação existe
		barraSup(47, 2, 23);
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
			fscanf(pegarNoArquivo, "%d", &parcela[i][j]);//preenche o conteudo da matriz parcela

	fclose(pegarNoArquivo);
}
//======================================================================================================================================================================================
int verificaTamanhoMatriz(float JNDPE[2]){
	if (JNDPE[1] > MAX || JNDPE[2] > MAX){
		barraSup(47, 4, 23);
		printf("\xBA  A quantidade de empresa ou politido utrapassou o limite   \xBA\n");
		printf("\t\t\t\xBA\t\t\tE tente novamente\t\t     \xBA\n");
		barraInf(60);
		return TRUE;
	}
	else
		return FALSE;
}
//======================================================================================================================================================================================
int verificaLetra(char arquivo[]){
	char ch;
	
	FILE *caractere = fopen (arquivo, "r");
	while((ch = fgetc(caractere))!= EOF)//pecorre todo arquivo procurando uma letra.
		if (isalpha(ch)){
			barraSup(47, 1, 23);	
			printf("\xBA\t    Existe uma letra ou mais letras no arquivo\t     \xBA\n");
			barraInf(60);
			return TRUE;
		}
	return FALSE;
}
//======================================================================================================================================================================================
int verificaPonto(char arquivo[]){
	char ch, chAnterior;
	int taErrado = 0;
	
	FILE *caractere = fopen(arquivo, "r");
	while ((ch = fgetc(caractere))!= EOF){//pecorre todo o arquivo procurando pontos.
		if (ispunct(ch) && chAnterior == '.' || ispunct(ch) && chAnterior == ' ')//verifica se o caracter anterior era um ponto ou um espaço vazio
			taErrado++;
		chAnterior = ch;
	}
		if (taErrado >= 1){
			barraSup(47, 1, 23);
			printf("\xBA     Sentimos muito! Mas, o arquivo contem pontos a mais    \xBA\n");
			barraInf(60);
			return TRUE;
		}
		else	
			return FALSE;
}
//======================================================================================================================================================================================
int verificaColuna(char arquivo[], float JNDPE[2]){
	int taErrado = 0;
	float politico = JNDPE[POLITICO];
	float empresa = JNDPE[EMPRESA];
	float numDeColuna = 0, numCorretoDeColuna = 0;
	char ch, chAnterior;

	FILE *coluna = fopen(arquivo, "r");
	while((ch = fgetc(coluna))!= EOF){//pecorre todo arquivo procurando espaços vazio
		if (ch == ' '){
			numDeColuna++;
			if (chAnterior == ' ')//verifica se o caracter anterior é um espaço vazio 
				taErrado++;	
		}
		chAnterior = ch;
	}

	numCorretoDeColuna = politico * empresa + ((empresa - 1) * politico);//calcula a quatidade de colunas corretas que o arquivo deve ter..
	if (numDeColuna != numCorretoDeColuna || taErrado >= 1){//verifica se o numero de linhas do arquivo é diferente do numero correto que o arquivo supostamente deve ter.

		barraSup(47, 2, 23);
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
			jCalculado[i][j] = pow(juros, parcela[i][j]);//responsavel por calculoar o valor da taxa de juro.
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
			somaCJ += propCal[politico][empresa]; //responsavel por somar o valor total da propina com juros.
			somaSJ += prop[politico][empresa];// responsavel por armazenar o valor total da propina sem juros.
		}
		propCJ[politico] = somaCJ;//atribue o valor total da soma ao vetor responsavel por armazenar o valor total. kk
		propSJ[politico] = somaSJ;	
	}
}
//======================================================================================================================================================================================
void totalPagoPorEmpresa(float propCal[MAX][MAX], float JNDPE[2], float EtotalPagoCJ[MAX], float propina[MAX][MAX], float EtotalPagoSJ[MAX]){

	int politico = 0, empresa = 0;
	float somaCJ = 0, somaSJ = 0;
	
	for(empresa = 0; empresa < JNDPE[EMPRESA]; empresa++){
		somaCJ = 0, somaSJ = 0;
		for(politico = 0; politico < JNDPE[POLITICO]; politico++){
			somaCJ += propCal[politico][empresa];//calcula a propina com o juros.
			somaSJ += propina[politico][empresa];//calcula a propina sem juros.
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

	for (i = 0; i < JNDPE[PouE]; i++)//calcula a media
		media[i] = (PCJ[i] / JNDPE[PouE]);
	
}
//======================================================================================================================================================================================
void gerarArquivoP1(float JNDPE[2], int idDoPoli[MAX], float propCal[MAX][MAX], float PCJ[MAX], float EPagoCJ[MAX]){

	int i, j;
	FILE *arq = fopen("Saida.txt", "w");

	for (i = 0; i < JNDPE[POLITICO]; i++){//responsavel por imprimir o valor do montante gerado.
		fprintf(arq, "%d ", idDoPoli[i]);
		for(j = 0; j < JNDPE[EMPRESA]; j++){
			fprintf(arq, "%.2f ", propCal[i][j]);
		}
		fprintf(arq, "%.2f\n", PCJ[i]);//responsavel por imprimir o valor total de propina recebida
	}
	fprintf(arq, "\n");
	for (j = 0; j < JNDPE[EMPRESA]; j++){
		fprintf(arq, "%.2f ", EPagoCJ[j]);//responsavel por imprimir o valor total pago por empresa
	}
	fprintf(arq, "\n\n");
	fclose(arq);
}
//======================================================================================================================================================================================
void gerarArquivoP2(int idDoPoli[MAX], float PmaisEmenos[7], float EmaisEmenos [7]){
	int i, j;
	FILE *arq = fopen("Saida.txt", "a+");

	for (i = 0; i < 8; i++){//responsavel por imprimir o politico que mais e menos recebeu propina
		if (i == 0 || i == 4){
			if(i == 4)//necessario para manter a organização do layout
				fprintf(arq, "\n\n");
			fprintf(arq, "%.0f ", PmaisEmenos[i]);
		}
		else
			fprintf(arq, "%.2f ", PmaisEmenos[i]);
	}
	fprintf(arq, "\n\n");
	for (i = 0; i < 8; i++){//responsavel por imprimir e empresa que mais e menos recebeu propina
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

	for (i = 0; i < JNDPE[POLITICO]; i++){//responsavel por imprimir a media dos politicos
		fprintf(arq, "%d ", i+1);
		fprintf(arq, "%.2f \n", medPoli[i]);
	}
	fprintf(arq, "\n");
	for (i = 0; i < JNDPE[EMPRESA]; i++){//responsavel por imprimir a media das empresas
		fprintf(arq, "%d ", i+1);
		fprintf(arq, "%.2f \n", medEmpre[i]);
	}
	fclose(arq);
}
//======================================================================================================================================================================================
int erroMsn(){//responsavel por imprimir uma messagem de erro. 
	int resposta = 0, i = 0;
	
	do{
		barraSup(57, 3, 28);
		printf("\xBA\t      Gostaria e tentar com outro arquivo?\t     \xBA\n");
		printf("\t\t\t\xBA\t\tSIM___(01)           NAO___(02)\t\t     \xBA\n");
		barraInf(60);
		printf("\t\t\t>>> ");
		scanf("%d", &resposta);
		fflush(stdin);
	
		if (resposta == 1)
			return TRUE;
		else if(resposta == 2)
			return FALSE;
		else{
			barraSup(47, 4, 23);
			printf("\xBA\t\tEscolha invalida! Tente novamente!\t     \xBA\n");
			barraInf(60);
		}
	}while(resposta < 1 || resposta > 2);
}
//======================================================================================================================================================================================
void sucesso(){
	int i = 0;
	barraSup(47, 4, 23)	;
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
		
	barraSup(28, 0, 23);
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
