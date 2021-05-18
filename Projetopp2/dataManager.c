#define _CRT_SECURE_NO_WARNINGS
#include "ll.h"
#include "dataManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

void printPlayer(Player p) 
{
	Player aux = p;
	printf("Número: %d\n", aux->numero);
	printf("Nome: %s\n", aux->nome);

	for (int i = 0; i < 5; i++)
	{
		printf("Arma: %s\n", aux->preferencias[i].arma);
		printf("Pontos: %d\n", aux->preferencias[i].pontuacao);
	}
}

LISTofLISTS ManageData(LISTofLISTS list)
{
	LISTofLISTS aux1 = list;
	int counter = ListOFListsSize(aux1)-1;
	ListElem playersList = NULL;
	while (counter >= 0) 
	{
		Player newPlayer = createPlayer(getDataOfLISTofLISTS(aux1, counter));
		playersList = addPlayer(playersList, newPlayer);
		counter -= 1;
	}
	ListSize(playersList);
	while (playersList != NULL)
	{
		printPlayer(playersList->data);
		playersList = playersList->next;
	}

	
	return list;
}

ListElem addPlayer(ListElem list, Player p)
{
	int index = 0;
	if (list == NULL)
	{
		ListElem newList = (ListElem*)malloc(sizeof(ListElem));
		newList->data = p;
		newList->next = NULL;
		newList->index = index;
		list = newList;
		return list;
	}
	else
	{
		ListElem aux = list;
		while (list->next != NULL)
		{
			list = list->next;
			index = list->index;
		}
		ListElem newItem = (ListElem*)malloc(sizeof(ListElem));
		newItem->data = p;
		newItem->next = NULL;
		newItem->index = index + 1;
		list->next = newItem;
		list = aux;
		return list;
	}
}

//creates new player
Player createPlayer(ListElem list)
{
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
	//-----------------------
	//Setup player data
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
		//Add Name
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
		//Add Preferences
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
	return newPlayer;
}
