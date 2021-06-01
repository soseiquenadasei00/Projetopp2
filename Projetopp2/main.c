#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <conio.h>
#include "ll.h"
#include "dataManager.h"


// Procedimento principal
void main()
{
	system("cls");
	bool running = true;
	int answer;
	LISTofLISTS list = NULL;
	jogo dadosDoJogo;

	setlocale(LC_ALL, "Portuguese");
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
		scanf("%d", &answer);
		switch (answer)
		{
		case 1:
			list = NULL;
			list = readFile();
			dadosDoJogo = getGuns(list);
			printf("Dados Lidos:\n");
			printList2(list);
			getchar();
			printf("Press Enter key to continue...");
			getchar();
			system("cls");
			break;
		case 2:
			if (list == NULL)
			{
				printf("No data loaded\n");
			}
			else
			{
				ManageData(list,dadosDoJogo);
				//printList2(list);
			}
			getchar();
			printf("Press Enter key to continue...");
			getchar();
			system("cls");
			break;
		case 3:
			Export(list);
			getchar();
			printf("Press Enter key to continue...");
			getchar();
			system("cls");
			break;
		case 4:
			running = false;
			system("cls");
			break;
		default:
			printf("Not a valid option!");
			break;
		}
	} 	while (running);
}