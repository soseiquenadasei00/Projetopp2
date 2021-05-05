#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ll.h"
#include <locale.h>
#include<conio.h>

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
				system("cls");
				break;
			case 2:
				if (list == NULL)
				{
					printf("No data loaded\n\n");
				}
				else
				{
					printList2(list);
					ListElem listElement = getDataOfLISTofLISTS(list, 1);
					printf("\n");
					printList(listElement);
					printf("\n");
					listElement = getDataOfListElem(listElement, 2);
					printElement(listElement);
					printf("\n\n");
				}
				printf("Press any key to continue");
				getchar();
				//system("cls");
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
}
