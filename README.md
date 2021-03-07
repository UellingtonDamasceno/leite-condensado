# leite-condensado

## Sumário
- [Problema](#problema)
- [Requisitos básicos](#requisitos-básicos)
- [Produto](#produto)
- [Objetivo de aprendizagem](#objetivo-de-aprendizagem)
- [Melhorias](#melhorias)
- [Curiosidades](#curiosidades)

## Problema
"Atualmente, o Brasil passa por um momento nunva visto na história do país, no 
qual esquemas de corrupção vêm sendo escancarados para toda a sociedade 
brasileira. Bom saber que corruptos estão sendo presos por seus atos ilícitos. no  
entando, por outro lado, é triste saber que há muito tempo o dinheiro públido é 
surrupiado dos nossos bolsos para encherem os bolsos de corruptos. O Brasil é a 
quarta nação mais corrupta do mundo, segundo o índice de corrupção do Fórum 
Econômico Mundial. O país está atrás apenas do Chade, da Bolívida e da Venezuela. 
que lidera o ranking.[¹](https://brasil.elpais.com/brasil/2016/10/03/internacional/1475517627_935822.html)

Diante de tantos esquemas sendo descobertos pela olícia Federal (PF). e 
consequentemente, com a quantidade de informações que estão sendo reveladas. a 
Polícia Federal está precisando de um sistema computacional para armazenar, 
organizar e gerar informações relevantes para as investigações.

O Diretor do setor de Inteligência da PF é um ex-aluno do curso de Engenharia de 
Computação da UEFS,e sabendo da qualidade do nosso curso, solicitou aos 
professores do MI de Algoritmos o desenvolvimento deste sistema, sendo assim esta 
será a proxima tarefa deste MI."

> Vale destacar que esse problema foi desenvolvido em 2017. 
> E por esse motivo as informações aqui presentes podem não condizer
> com a situação atual do Brasil.


## Requisitos básicos

"De acordo com as investigações da PF. as propinas eram pagas em parcelas aos 
políticos corruptos pelas empresas, para conseguirem vantagens no processo de 
licitação de grandes obras. No entanto, os políticos cobravam juros compostos do 
valor solicitados."

Diante dessa informação o sitema deverá:

| Requisito nº | Descrição | Status |
| :----------: | --------- | :----: |
| 01 | Calcular para cada politico, o montante (considerando uma taaxa de juros e o número de parcelas) a ser recebido de cada empresa. | :white_check_mark: |
| 02 | Calcular o valor total recebido por cada político (considerando os juros). | :white_check_mark: |
| 03 | Calcular o valor total de propina paga de cada empresa. | :white_check_mark: |
| 04 | Informar qual foi o político que `mais` recebeu propina, o total de propina recebida (com e sem juros) e o juros recebido. | :white_check_mark: |
| 05 | Informar qual foi o político que `menos` recebeu propina, o total de propina recebida (com e sem juros) e o juros recebido. | :white_check_mark: | 
| 06 | Informar qual foi a empresa que `mais` pagou propina, o total de propina paga (com e sem juros) e o juros pago. | :white_check_mark: | 
| 07 | Informar qual foi a empresa que `menos` pagou propina, o total de propina paga (com e sem juros) e o juros pago. | :white_check_mark: |
| 08 | Informar qual foi a média de propina recebida por cada `político`. | :white_check_mark: |
| 09 | Informar qual foi a média de propina paga por cada `empresa`. | :white_check_mark: |

## Produto
- Um sistema **bem modularizado** e que não faz uso  de **variáveis globais** e que atenda os [requisitos básicos](#requisitos-básicos), usando a linguagem de programação C. 
- Um [Relatório](https://github.com/UellingtonDamasceno/leite-condensado/blob/main/res/relatorio.pdf) conforme o modelo e instrução disponibilizados pelo tutor.

## Objetivo de aprendizagem
- Leitura e escrita de arquivos em C.
- Operações aritiméticas com matrizes e vetores.
- Modularização, Funções e procedimentos.

## Algoritmo
### Entradas
### Saída

## Melhorias
- Particionar as matrizes e multplicar blocos menores por vez a fim de reduzir a quantidade de acesso a memória RAM e consequentemente aumentar a velocidade das operações. [mais detalhes](https://github.com/UellingtonDamasceno/DGEMM-memory-analysis)
- Renomar algumas variáveis como por exemplo o vetor JPDNE. (Fazia sentido na época kkkk).
- Inserir bibliotecas necessárias para o bom funcionamento do _software_ em sistemas operacionais baseado em Linux.

## Curiosidades
1. O nome do repositório é uma referência e tem como objetivo ser diferente e chamativo. **Por favor, julge o código e não e não minha habilidade em fazer referências. Taokey?**.
2. Há um cálculo que está errado mas pode dá o resultado correto em uma determinada situação. (Gostaria de saber qual é? Descobriu? Manda um oi e vamos conversar sobre).
3. Ao olhar as versões anteriores verá que durante muito tempo digitei "propina" errado.
4.  Os códigos na pasta de [versões anteriores](https://github.com/UellingtonDamasceno/leite-condensado/tree/main/Vers%C3%B5es%20anteriores) possuem uma descrição que lista as diferenças entre a versão atual e a anterior.

----------
:arrow_left: [Problema anterior](https://github.com/UellingtonDamasceno/professor-curioso)
