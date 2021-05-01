#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ll.h"
#include <locale.h>

// Estruturas de Dados

typedef struct
{
	char arma[50]; // arma de combate
	int pontuacao; // 0 a 100
} Preferencias;

typedef struct dados
{
	int numero;
	char nome[50];
	Preferencias preferencias[5]; // ordem de prefer�ncias (m�ximo de 5)
}*Jogador;

// Prot�tipos

void show(void* data);
int igual(void* data1, void* data2);
void main();


// Implementa��es

// Escrita na consola do dados de um jogador
void show(void* data)
{
	Jogador j = (Jogador)data;
	if (j != NULL)
		printf("%d %s ", j->numero, j->nome);
	for (int i = 0; i < 5; i++)
		printf("%s %d ", j->preferencias[i].arma, j->preferencias[i].pontuacao);
	printf("\n");
}

// Se iguais devolve 1 sen�o devolve 0
int igual(void* data1, void* data2)
{
	int* d1 = (int*)data1;
	int* d2 = (int*)data2;
	if ((d1 != NULL) && (d2 != NULL)) return(*d1 == *d2);
	else return(0);
}

// Procedimento principal
void main()
{
	bool running = true;
	int answer;
	LISTofLISTS list = NULL;

	setlocale(LC_ALL, "Portuguese");
	Jogador j = (Jogador*) malloc(sizeof(Jogador));
	do
	{
		printf("\n\tMENU\n");
		printf("-------------------------------------------\n");
		printf("(1) Carregar dados de texto\n");
		printf("(2) Escrever dados em tabela\n");
		printf("(3) Exportar os dados em tabela de texto\n");
		printf("(4) Sair do programa\n");
		printf("-------------------------------------------\n");
		printf("Choose one option: ");
		scanf("%d",&answer);
		switch (answer)
		{
			case 1:
				list = readFile();
				printf("Read list\n");
				printList2(list);
				break;
			case 2:
				//showListIterative(lista,&show);
				break;
			case 3:
				break;
			case 4:
				running = false;
				printf("Thank You for playing\n");
				break;
			default:
				printf("Not a valid option!");
				break;
		}
	}
	while (running);
	//ListElem lista = NULL;
	//Jogador j;

	//j = (Jogador)malloc(sizeof(struct dados));
	//j->numero = 1;
	//strcpy(j->nome, "Joao");
	//strcpy(j->preferencias[0].arma, "sniper");
	//j->preferencias[0].pontuacao = 87;
	//strcpy(j->preferencias[1].arma, "pistola");
	//j->preferencias[1].pontuacao = 67;
	//strcpy(j->preferencias[2].arma, "metralhadora");
	//j->preferencias[2].pontuacao = 57;
	//strcpy(j->preferencias[3].arma, "-");
	//j->preferencias[3].pontuacao = 0;
	//strcpy(j->preferencias[4].arma, "-");
	//j->preferencias[4].pontuacao = 0;
	//lista = addItemHead(lista, j);

	//j = (Jogador)malloc(sizeof(struct dados));
	//j->numero = 2;
	//strcpy(j->nome, "Maria");
	//strcpy(j->preferencias[0].arma, "metralhadora");
	//j->preferencias[0].pontuacao = 77;
	//strcpy(j->preferencias[1].arma, "sniper");
	//j->preferencias[1].pontuacao = 79;
	//strcpy(j->preferencias[2].arma, "-");
	//j->preferencias[2].pontuacao = 0;
	//strcpy(j->preferencias[3].arma, "-");
	//j->preferencias[3].pontuacao = 0;
	//strcpy(j->preferencias[4].arma, "-");
	//j->preferencias[4].pontuacao = 0;
	//lista = addItemHead(lista, j);

	//// Escrita na consola do conte�do da lista ligada
	//showListIterative(lista, &show);

	//printf("----------------\n");
	//int numero = 2;
	//// Remo��o da primeiro ocorr�ncia do registo com n�mero de jogador 2
	//lista = removeItemIterative(lista, &numero, &igual);

	//// Escrita na consola do conte�do da lista ligada
	//showListIterative(lista, &show);
}
