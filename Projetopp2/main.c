#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ll.h"
#include "dataManager.h"
#include <locale.h>
#include<conio.h>

// Procedimento principal
void main()
{
	bool running = true;
	int answer;
	LISTofLISTS list = NULL;

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
					ManageData(list);
					/*printList2(list);*/
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
