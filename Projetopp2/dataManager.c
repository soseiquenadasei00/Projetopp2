#include "ll.h"
#include "dataManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LISTofLISTS ManageData(LISTofLISTS list) 
{
	LISTofLISTS aux1 = list;
	ListElem listOfPlayers = NULL;
	while (aux1 != NULL)
	{
		Player newPlayer = createPlayer(aux1->list);
		listOfPlayers = addItem(listOfPlayers, newPlayer);
		aux1 = aux1->next;
	}

	while (listOfPlayers != NULL)
	{
		Player tempPlayer = listOfPlayers->data;
		printf("Nome: %s\n", tempPlayer->nome);
		printf("Número: %d\n\n", tempPlayer->numero);
		printf("Arma 1: %s\n", tempPlayer->preferencias[0].arma);
		printf("Pontos 1: %d\n\n", tempPlayer->preferencias[0].pontuacao);
		printf("Arma 2: %s\n", tempPlayer->preferencias[1].arma);
		printf("Pontos 2: %d\n\n", tempPlayer->preferencias[1].pontuacao);
		printf("Arma 3: %s\n", tempPlayer->preferencias[2].arma);
		printf("Pontos 3: %d\n\n", tempPlayer->preferencias[2].pontuacao);
		printf("-----------------------------------------");
		printf("\n");
		listOfPlayers = listOfPlayers->next;
	}
	return NULL;
}

ListElem removeElement(ListElem list, int index)
{

}

/*
creates variables for player
*/ 
Player createPlayer(ListElem list)
{
	if (list != NULL) 
	{
		ListElem aux = list;
		ListElem data = aux->data;
		Player newPlayer = (Player*)malloc(sizeof(Player));
		newPlayer->numero = 0;
		for (int i = 0; i < 5; i++)
		{
			newPlayer->preferencias[i].pontuacao = 0;
		}

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
		for (int i = 0; i < strlen(newPlayer->nome); i++)
		{
			newPlayer->nome[i] = data->data;
			if (data->next != NULL)
			{
				data = data->next;
			}
			else
			{
				newPlayer->nome[i+1] = NULL;
				break;
			}
		}
		aux = aux->next;
		int nAux = 0;
		//add preferences
		while (aux!=NULL)
		{
			data = aux->data;
			/*printElement(data);
			printf("\n");*/
			if (aux->index % 2 == 0) 
			{
				//Get name of gun;
				printf("Get name of gun\n");
			}
			else
			{
				
					while (data != NULL && data->data != '-')
					{
						if (newPlayer->preferencias[nAux].pontuacao == 0)
						{
							newPlayer->preferencias[nAux].pontuacao = (int)(data->data) - 48;
						}
						else
						{
							newPlayer->preferencias[nAux].pontuacao = (newPlayer->preferencias[nAux].pontuacao * 10) + ((int)(data->data) - 48);
						}
						data = data->next;
					}
				
				++nAux;
			}
			aux = aux->next;
		}
		return newPlayer;
	}
	else
	{
		return NULL;
	}
}

int listLenght(ListElem list)
{
	int counter = 0;
	ListElem aux = list;
	while (aux != NULL)
	{
		counter++;
		aux = aux->next;
	}
	return counter;
}

bool ComparePreferences(Preferences p1, Preferences p2)
{

}