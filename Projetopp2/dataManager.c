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

void Export(LISTofLISTS list)
{
	if (list != NULL)
	{
		LISTofLISTS aux = list;
		FILE* exportFile = NULL;
		exportFile = fopen("export.txt", "w");
		while (aux != NULL)
		{
			ListElem line = getDataOfLISTofLISTS(list, aux->index);
			while (line != NULL)
			{
				ListElem data = getDataOfListElem(line, line->index);
				while (data != NULL)
				{
					char character = data->data;
					fputc(character, exportFile);
					data = data->next;
				}
				fputc(' ', exportFile);
				line = line->next;
			}
			fputc('\n', exportFile);
			aux = aux->next;
		}
		fclose(exportFile);
	}
	else
	{
		printf("No data loaded\n");
	}
}
/*
pega lista de players
cria variáveis player com os dados e salva em lista ligada
gerencia os dados das variáveis fp tipo player
*/
void ManageData(LISTofLISTS list, jogo dadosDasArmas)
{
	LISTofLISTS aux = list;
	jogo auxJogo = dadosDasArmas;
	ListElem players = NULL;
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
			/*ARMA test = auxJogo.armas->data;
			
			printf("\n%s(%d)\n",test->nome,counter);
			for (int i = 0; i < ListSize(tempPlayers); ++i)
			{
				printf("%d -> ", numbers[i]);
			}*/

			ARMA arma = auxJogo.armas->data;
			for (int b = 0; b < size; b++)
			{
				Player auxPlayer = getPlayerWithPref(players, counter, numbers[b]);
				if (arma->numero > 0)
				{
					arma->numero -= 1;
				}
				else
				{
					auxPlayer->preferencia[counter].arma[0] = '-';
					auxPlayer->preferencia[counter].arma[1] = 0;
					auxPlayer->preferencia[counter].pontos = 0;
					players = Replace(players, auxPlayer);
				}
			}
			
			
			/*	ARMA tempARMA = auxJogo.armas->data;
				while (tempPlayers != NULL)
				{
					Player tempP = tempPlayers->data;
					if (tempP->preferencia[counter].pontos == numbers[b])
					{
						if (tempARMA->numero > 0)
						{
							tempARMA->numero -= 1;
						}
						else
						{
							tempP->preferencia[counter].arma[0] = '-';
							tempP->preferencia[counter].arma[1] = 0;
							tempP->preferencia[counter].pontos = 0;
						}
						players = Replace(players, tempP);
					}
					tempPlayers = tempPlayers->next;
				}
			}*/

		}
		/*ARMA tempA = auxJogo.armas;
		int counter = 0;*/
		//if (ListSize(tempPlayers) > tempA->numero)
		//{
		//	ListElem tempPlayers2 = NULL;
		//	// ListElem tempPlayers3 = NULL;

		//	while (tempPlayers != NULL)
		//	{
		//		if (counter == getIndexOfPreference(tempPlayers->data, auxJogo.armas))
		//		{
		//			tempPlayers2 = addItem(tempPlayers2, tempPlayers->data);
		//		}
		//		tempPlayers = tempPlayers->next;
		//	}
		//	ARMA tempARMA = auxJogo.armas->data;
		//	if (ListSize(tempPlayers2) <= tempARMA->numero)
		//	{
		//		tempARMA->numero -= ListSize(tempPlayers2);
		//	}
		//	else
		//	{
		//		int* numbers = (int*)malloc(ListSize(tempPlayers2) * sizeof(int));
		//		ListElem listStart = tempPlayers2;
		//		for (int i = 0; i < ListSize(tempPlayers2); i++)
		//		{
		//			Player tempP = tempPlayers2->data;
		//			numbers[i] = tempP->preferencia[counter].pontos;
		//			tempPlayers2 = tempPlayers2->next;
		//		}

		//		tempPlayers2 = listStart;

		//		for (int i = 0; i < ListSize(tempPlayers2); ++i)
		//		{
		//			for (int j = i + 1; j < ListSize(tempPlayers2); ++j)
		//			{
		//				if (numbers[i] < numbers[j])
		//				{
		//					int a = numbers[i];
		//					numbers[i] = numbers[j];
		//					numbers[j] = a;
		//				}
		//			}
		//		}

		//		for (int b = 0; b < ListSize(tempPlayers2); b++)
		//		{
		//			while (tempPlayers2 != NULL)
		//			{
		//				Player tempP = tempPlayers2->data;
		//				if (tempP->preferencia[counter].pontos == numbers[b])
		//				{
		//					if (tempARMA->numero > 0)
		//					{
		//						tempARMA->numero -= 1;
		//					}
		//					else
		//					{
		//						tempP->preferencia[counter].arma[0] = '-';
		//						tempP->preferencia[counter].arma[1] = 0;
		//						tempP->preferencia[counter].pontos = 0;
		//					}
		//					players = Replace(players, tempP);
		//				}
		//				tempPlayers2 = tempPlayers2->next;
		//			}
		//		}
		//	}
		//	counter++;
		//}
		//else printf("n entrei\n");
		auxJogo.armas = auxJogo.armas->next;
	}

	while (players != NULL)
	{
		printPlayer(players->data);
		players = players->next;
	}

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

ListElem Replace(ListElem list, Player data1, Player data2)
{
	ListElem aux = list;
	while (aux != NULL)
	{
		Player comparePlayer = aux->data;
		if (strcmp(comparePlayer->nome, data1->nome) == 0)
		{
			aux->data = data2;
		}
		aux = aux->next;
	}
	aux = list;
	return aux;
	
}


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
ListElem playerListWithGun(ListElem list, ARMA a,int index)
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

void ComparePreferences(Player p1, Player p2)
{
	/*
		comparar strings

		se p1 arma == p2 arma
			se p1 pontos > p2 pontos
				p2 arma = '-'
				p2 pontos = 0
			senão se p1 pontos < p2 pontos
				p1 arma = '-'
				p1 pontos = 0
			senão
				nada acontece
	*/
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


//ListElem tempPlayers = playerListWithGun(players, auxJogo.armas->data);
//ARMA tempA = auxJogo.armas->data;
//printf("%d ->", tempA->numero);

//int counter = 0;
//
//if (ListSize(tempPlayers) > tempA->numero)
//{
//	ListElem tempPlayers2 = NULL;
//	// ListElem tempPlayers3 = NULL;

//	while (tempPlayers != NULL)
//	{
//		if (counter == getIndexOfPreference(tempPlayers->data, auxJogo.armas))
//		{
//			tempPlayers2 = addItem(tempPlayers2, tempPlayers->data);
//		}
//		tempPlayers = tempPlayers->next;
//	}
//	ARMA tempARMA = auxJogo.armas;
//	if (ListSize(tempPlayers2) <= tempARMA->numero)
//	{
//		tempARMA->numero -= ListSize(tempPlayers2);
//	}
//	else
//	{
//		int* numbers = (int*)malloc(ListSize(tempPlayers2) * sizeof(int));
//		ListElem listStart = tempPlayers2;
//		for (int i = 0; i < ListSize(tempPlayers2); i++)
//		{
//			Player tempP = tempPlayers2->data;
//			numbers[i] = tempP->preferencia[counter].pontos;
//			tempPlayers2 = tempPlayers2->next;
//		}

//		tempPlayers2 = listStart;

//		for (int i = 0; i < ListSize(tempPlayers2); ++i)
//		{
//			for (int j = i + 1; j < ListSize(tempPlayers2); ++j)
//			{
//				if (numbers[i] < numbers[j])
//				{
//					int a = numbers[i];
//					numbers[i] = numbers[j];
//					numbers[j] = a;
//				}
//			}
//		}

//		for (int b = 0; b < ListSize(tempPlayers2); b++)
//		{
//			while (tempPlayers2 != NULL)
//			{
//				Player tempP = tempPlayers2->data;
//				if (tempP->preferencia[counter].pontos == numbers[b])
//				{
//					if (tempARMA->numero > 0)
//					{
//						tempARMA->numero -= 1;
//					}
//					else
//					{
//						tempP->preferencia[counter].arma[0] = '-';
//						tempP->preferencia[counter].arma[1] = 0;
//						tempP->preferencia[counter].pontos = 0;
//					}
//					players = Replace(players, tempP);
//				}
//				tempPlayers2 = tempPlayers2->next;
//			}
//		}
//	}
//	counter++;
//}
//else
//{
//	printf("%d - %d = ", tempA->numero,ListSize(tempPlayers));
//	tempA->numero -= ListSize(tempPlayers);
//	printf("%d\n", tempA->numero);
//}
//else printf("n entrei\n");