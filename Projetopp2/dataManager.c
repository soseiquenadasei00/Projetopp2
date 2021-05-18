#define _CRT_SECURE_NO_WARNINGS
#include "ll.h"
#include "dataManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void printPlayer(Player p) 
{
	printf("Número: %d\n", p->numero);
	printf("Nome: %s\n", p->nome);

	for (int i = 0; i < 5; i++)
	{
		printf("Arma: %s\n", p->preferencias[i].arma);
		printf("Pontos: %d\n", p->preferencias[i].pontuacao);
	}
}

LISTofLISTS ManageData(LISTofLISTS list)
{
	LISTofLISTS aux1 = list;
	int counter = ListOFListsSize(aux1);
	ListElem playersList = NULL;
	while (counter >= 0) 
	{
		Player newPlayer = createPlayer(getDataOfLISTofLISTS(aux1, counter-1));
		playersList = addItem(playersList, &newPlayer);
		counter -= 1;
	}
	ListSize(playersList);
	
	return list;
}

ListElem removeElement(ListElem list, int index)
{

}
//creates new player
Player createPlayer(ListElem list)
{
	/*printf("\n");
	printList(list);*/
	ListElem aux = list;
	Player newPlayer = (Player*)malloc(sizeof(Player));
	//setups player base
	newPlayer->numero = 0;
	for (int i = 0; i < 50; i++)
	{
		newPlayer->nome[i] = 0;
	}
	for (int i = 0; i < 5; i++)
	{
		newPlayer->preferencias[i].index = i;
		newPlayer->preferencias[i].pontuacao = 0;
		for (int b = 0; b < 50; b++)
		{
			newPlayer->preferencias[i].arma[b] = 0;
		}
	}
	if (aux != NULL)
	{
		ListElem data = aux->data;
		//add number
		while (data != NULL)
		{
			if (newPlayer->numero == 0)
			{
				newPlayer->numero = (int)(data->data) - 48;
			}
			else
			{
				newPlayer->numero = (newPlayer->numero * 10) + ((int)(data->data) - 48);
			}
			data = data->next;
		}
		aux = aux->next;
		data = aux->data;
		//add name
		for (int i = 0; i < 50; i++)
		{
			if (data != NULL)
			{
				newPlayer->nome[i] = data->data;
				data = data->next;
			}
			else if(data == NULL)
			{
				break;
			}
		}
		aux = aux->next;
		int nAux = 0;
		//add preferences
		while (aux != NULL)
		{
			data = aux->data;
			if (aux->index % 2 == 0)
			{
				for (int i = 0; i < 50; i++)
				{
					if (data != NULL && data->data != '-')
					{
						newPlayer->preferencias[nAux].arma[i] = data->data;
						data = data->next;
					}
					else if (data == NULL || data->data == '-')
					{
						break;
					}
				}
			}
			else
			{
				while (data != NULL)
				{
					if (data->data != '-')
					{
						if (newPlayer->preferencias[nAux].pontuacao == 0)
						{
							newPlayer->preferencias[nAux].pontuacao = (int)data->data - 48;
							//printf("add first number: %d\n", newPlayer->preferencias[nAux].pontuacao);
						}
						else
						{
							newPlayer->preferencias[nAux].pontuacao = (newPlayer->preferencias[nAux].pontuacao * 10) + ((int)data->data - 48);
							//printf("add next number: %d\n", newPlayer->preferencias[nAux].pontuacao);
						}
					}
					data = data->next;
				}
				nAux += 1;
			}
			aux = aux->next;
		}
	}
	/*printf("numero: %d\n", newPlayer->numero);
	printf("nome: %s\n", newPlayer->nome);
	for (int i = 0; i < 5; i++)
	{
		printf("arma %d: %s\n", i, newPlayer->preferencias[i].arma);
		printf("pontos: %d\n", newPlayer->preferencias[i].pontuacao);
	}
	printf("\n");*/
	return newPlayer;
}
