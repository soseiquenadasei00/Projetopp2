#include "ll.h"
#include <stdio.h>
#include <stdbool.h>

// Estruturas de Dados

typedef struct pref
{
	char arma[50]; // arma de combate
	int pontuacao; // 0 a 100
	int index;
}Preferences;

typedef struct dados
{
	int numero;
	char nome[50];
	Preferences preferencias[5]; // ordem de preferências (máximo de 5)
}*Player;

typedef struct listPlayers {
	Player player;
	int index;
	struct listPlayers* nextPlayer;
} *playerList;

int playerListSize(playerList list);

playerList addPlayer(ListElem list, Player p);
Player getPlayerFromList(ListElem list, int index);
//manages the listoflists and sorts preferences of the players
void ManageData(LISTofLISTS list);
//removes losing element of preference
ListElem removeElement(ListElem list, int index);
//add player data type to workbench
Player createPlayer(ListElem list);
//compares preferences
bool ComparePreferences(Player p1, Player p2);

void printPlayer(Player p);

void Export(LISTofLISTS list);