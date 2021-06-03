#define _CRT_SECURE_NO_WARNINGS

#include "dataManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

jogo getNumberOfGuns(jogo j)
{
	jogo aux = j;
	jogo returnJogo;
	returnJogo.armas = NULL;
	while (aux.armas != NULL)
	{
		ARMA tempArma = aux.armas->data;
		int num = 0;
		tempArma->numero = 0;
		printf("numero de %s:", tempArma->nome);
		scanf("%d", &num);
		tempArma->numero = num;

		returnJogo.armas = addItem(returnJogo.armas, (ARMA*)tempArma);
		aux.armas = aux.armas->next;
	}
	printf("\n");
	return returnJogo;
}

jogo ManageJogo(jogo j)
{
	jogo aux1 = j;
	jogo returnJogo;
	returnJogo.armas = NULL;

	ARMA a0 = aux1.armas->data;
	returnJogo.armas = addItem(returnJogo.armas, (ARMA*)a0);

	jogo originList;
	originList.armas = returnJogo.armas;

	int logic = 0;

	while (aux1.armas != NULL)
	{
		ARMA a1 = aux1.armas->data;
		while (returnJogo.armas != NULL)
		{
			ARMA a2 = returnJogo.armas->data;

			if (strcmp(a1->nome, a2->nome) == 0)
			{
				logic++;
			}
			returnJogo.armas = returnJogo.armas->next;
		}
		returnJogo.armas = originList.armas;
		if (logic == 0)
		{
			returnJogo.armas = addItem(returnJogo.armas, (ARMA*)a1);
		}
		logic = 0;
		aux1.armas = aux1.armas->next;
	}

	returnJogo = getNumberOfGuns(returnJogo);
	return returnJogo;
}

jogo getGuns(LISTofLISTS list)
{
	//returns game with the guns that will be needed to be given numbers in real time
	LISTofLISTS aux = list;
	jogo j;
	j.armas = NULL;
	while (aux != NULL)
	{
		int i = 0;
		//lista de characteres
		ListElem list1 = aux->list;
		while (list1 != NULL)
		{
			i = 0;
			if (list1->index >= 2 && list1->index % 2 == 0)
			{
				ListElem data = list1->data;
				if (data->data != '-')
				{
					char temp[50] = { 0 };
					while (data != NULL)
					{
						temp[i] = data->data;
						i++;
						data = data->next;
					}
					ARMA newArma = (struct arma*)malloc(sizeof(ARMA));
					for (i = 0; i < 50; i++)
					{
						newArma->nome[i] = temp[i];
						if (temp[i] == 0)
						{
							break;
						}
					}
					j.armas = addItem(j.armas, (ARMA*)newArma);
				}
			}
			list1 = list1->next;
		}
		aux = aux->next;
	}
	j = ManageJogo(j);

	return j;
}

void printPlayer(Player p)
{
	Player aux = p;
	printf("--------------------\n");
	printf("Numero: %d\n", aux->numero);
	printf("Nome: %s\n\n", aux->nome);

	for (int i = 0; i < 5; i++)
	{
		Preferences tempPref = aux->preferencia[i];
		printf("Arma: %s\n", tempPref.arma);
		printf("Pontos: %d\n", tempPref.pontos);
	}

	printf("--------------------\n");
}

void Export(ListElem list,jogo dadosDasArmas,int i)
{
	ListElem aux = list;
	ListElem listaDeArmas = dadosDasArmas.armas;
	char nome[20] = "Export";
	nome[6] = i + 48;
	nome[7] = '.';
	nome[8] = 't';
	nome[9] = 'x';
	nome[10] = 't';
	nome[11] = 0;

	FILE* file = fopen(nome, "w");
	while (listaDeArmas != NULL)
	{
		ARMA arma = listaDeArmas->data;
		fprintf(file, "%s\n\n", arma->nome);

		while (aux != NULL)
		{
			Player tempPlayer = aux->data;
			for (int i = 0; i < 5; i++)
			{
				if (strcmp(tempPlayer->preferencia[i].arma, arma->nome) == 0 && i == 0)
				{					
					fprintf(file, "Numero do Player: %d\t", tempPlayer->numero);					
					fprintf(file, "Nome do Player: %s\t", tempPlayer->nome);
					fprintf(file, "Pontos da arma: %d\t ", tempPlayer->preferencia[i].pontos);

					if (tempPlayer->preferencia[i].empate == 1)
					{
						fprintf(file, "(EMPATE)");
					}
					fprintf(file, "\n\n");
				}
			}
			aux = aux->next;
		}
		aux = list;
		listaDeArmas = listaDeArmas->next;
	}
	fclose(file);
}



void ManageData(LISTofLISTS list, jogo dadosDasArmas)
{
	LISTofLISTS aux = list;
	jogo auxJogo = dadosDasArmas;
	ListElem players = NULL;
	ListElem rejectedPlayers = NULL;
	while (aux != NULL)
	{
		Player p = NULL;
		p = createPlayer(aux->list);
		players = addItem(players, (Player*)p);
		aux = aux->next;
	}
	aux = list;

	while (auxJogo.armas != NULL)
	{
		int counter = 0;
		for (counter = 0; counter < 5; counter++)
		{
			ListElem tempPlayers = playerListWithGun(players, auxJogo.armas->data, counter);
			ListElem tempPlayersOrigin = tempPlayers;
			int* numbers = (int*)malloc(ListSize(tempPlayers) * sizeof(int));
			int size = ListSize(tempPlayers);
			for (int i = 0; i < size; i++)
			{
				Player tempP = tempPlayers->data;
				numbers[i] = tempP->preferencia[counter].pontos;
				tempPlayers = tempPlayers->next;
			}
			tempPlayers = tempPlayersOrigin;

			size = ListSize(tempPlayers);
			for (int i = 0; i < size; ++i)
			{
				for (int j = i + 1; j < size; ++j)
				{
					if (numbers[i] < numbers[j])
					{
						int a = numbers[i];
						numbers[i] = numbers[j];
						numbers[j] = a;
					}
				}
			}
			
			ARMA arma = auxJogo.armas->data;
			for (int b = 0; b < size; b++)
			{
				Player auxPlayer = getPlayerWithPref(players, counter, numbers[b]);
				if (arma->numero == 1)
				{
					if (b + 1 != size)
					{
						if (numbers[b] > numbers[b+1])
						{
							printf("entregar %s para %s\n", arma->nome,auxPlayer->nome);
							arma->numero -= 1;
							auxPlayer->preferencia[counter].empate = 0;
							players = Replace(players, auxPlayer);
						}
						else if (numbers[b] == numbers[b + 1])
						{
							Player auxPlayer2 = getOtherPlayerWithPref(players, counter, numbers[b + 1],auxPlayer);							
							printf("empate entre %s e %s\n",auxPlayer->nome,auxPlayer2->nome);

							auxPlayer->preferencia[counter].empate = 1;
							auxPlayer2->preferencia[counter].empate = 1;													

							players = Replace(players, auxPlayer);
							players = Replace(players, auxPlayer2);
						}
					}
					else if(b+1 == size)
					{
						arma->numero -= 1;
						auxPlayer->preferencia[counter].empate = 0;
						players = Replace(players, auxPlayer);
					}

				}
				else if (arma->numero > 1)
				{
					arma->numero -= 1;
					auxPlayer->preferencia[counter].empate = 0;
					players = Replace(players, auxPlayer);
				}
				else
				{
					//rejectedPlayers = addItem(rejectedPlayers,rejectedPlayer);
					auxPlayer->preferencia[counter].arma[0] = '-';
					auxPlayer->preferencia[counter].arma[1] = 0;
					auxPlayer->preferencia[counter].pontos = 0;
					auxPlayer->preferencia[counter].empate = 0;
					players = Replace(players, auxPlayer);
				}
			}
		}

		auxJogo.armas = auxJogo.armas->next;
	}
	//Export(rejectedPlayers, dadosDasArmas,1);
	Export(players,dadosDasArmas,0);
}

Player getPlayerWithPref(ListElem list, int counter, int number)
{
	ListElem aux = list;
	Player auxPlayer;
	while (aux != NULL)
	{
		auxPlayer = aux->data;
		if (auxPlayer->preferencia[counter].pontos == number)
		{
			return auxPlayer;
		}
		aux = aux->next;
	}
	return NULL;
}

Player getOtherPlayerWithPref(ListElem list, int counter, int number, Player notThis)
{
	ListElem aux = list;
	Player auxPlayer;
	while (aux != NULL)
	{
		auxPlayer = aux->data;
		if (auxPlayer->preferencia[counter].pontos == number && auxPlayer->numero != notThis->numero)
		{
			return auxPlayer;
		}
		aux = aux->next;
	}
	return NULL;
}

Player getPlayerWithPref2(ListElem list, ARMA gun)
{
	ListElem aux = list;
	while (aux != NULL)
	{
		Player p = aux->data;
		for (int i = 0; i < 5; i++)
		{
			if (strcmp(p->preferencia[i].arma, gun->nome) == 0)
			{
				return p;
			}
		}
		aux = aux->next;
	}
	return NULL;
}

ListElem Replace(ListElem list, Player data)
{
	ListElem aux = list;
	while (aux != NULL)
	{
		Player temp = aux->data;
		if (strcmp(temp->nome, data->nome) == 0)
		{
			//printf("Passei\n");
			aux->data = data;
		}
		aux = aux->next;
	}
	aux = list;
	return aux;
}

//
int getIndexOfPreference(Player p, ARMA g)
{
	for (int i = 0; i < 5; i++)
	{
		if (strcmp(p->preferencia[i].arma, g->nome) == 0)
		{
			return i;
		}
	}
	return 0;
}

//get list of players with a gun at a specific index 
ListElem playerListWithGun(ListElem list, ARMA a, int index)
{
	ListElem aux = list;
	ListElem returnList = NULL;
	while (aux != NULL)
	{
		Player tempP = aux->data;

		if (strcmp(tempP->preferencia[index].arma, a->nome) == 0)
		{
			returnList = addItem(returnList, (Player*)tempP);
		}
		aux = aux->next;
	}
	return returnList;
}

//creates new player
Player createPlayer(ListElem list)
{
	Player newPlayer = (struct dados*)malloc(sizeof(struct dados));
	newPlayer->numero = 0;
	//Setup player data
	ListElem aux = list;
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
		else if (data == NULL)
		{
			newPlayer->nome[i] = 0;
			break;
		}
	}

	aux = aux->next;
	int nAux = 0;

	//Add Preferences
	Preferences newPref;
	newPref.pontos = 0;

	while (aux != NULL)
	{
		data = aux->data;
		if (aux->index % 2 == 0)
		{
			//nome da arma
			for (int i = 0; i < 50; i++)
			{
				if (data != NULL)
				{
					newPref.arma[i] = data->data;
					data = data->next;
				}
				else if (data == NULL)
				{
					newPref.arma[i] = 0;
					break;
				}
			}

		}
		else
		{
			//pontos
			newPref.pontos = 0;
			while (data != NULL)
			{
				if (data->data == '-')
				{
					newPref.pontos = 0;
				}
				else
				{
					newPref.pontos = newPref.pontos * 10 + ((char*)data->data - (int)48);
				}
				data = data->next;
			}
			newPref.index = nAux;
			newPlayer->preferencia[nAux] = newPref;
			nAux += 1;
		}
		aux = aux->next;
	}
	return newPlayer;
}