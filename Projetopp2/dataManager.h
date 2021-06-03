#define _CRT_SECURE_NO_WARNINGS
#include "ll.h"
#include <stdio.h>
#include <stdbool.h>

// Estruturas de Dados
typedef struct arma
{
	char nome[50];
	int numero;
}*ARMA;

typedef struct comp
{
	ListElem armas;
}jogo;

typedef struct pref
{
	char arma[50]; // arma de combate
	int pontos; // 0 a 100
	int index;
	int empate;
}Preferences;

typedef struct dados
{
	int numero;
	char nome[50];
	Preferences preferencia[5]; // ordem de preferências (máximo de 5)
}*Player;

jogo ManageJogo(jogo j);
jogo getGuns(LISTofLISTS list);
jogo getNumberOfGuns(jogo j);

ListElem Replace(ListElem list, Player data);

ListElem playerListWithGun(ListElem list, ARMA a,int index);

int getIndexOfPreference(Player p, ARMA g);

Player getPlayerWithPref(ListElem list, int counter, int number);
Player getOtherPlayerWithPref(ListElem list, int counter, int number,Player notThis);
Player getPlayerWithPref2(ListElem list, ARMA gun);
//manages the listoflists and sorts preferences of the players
void ManageData(LISTofLISTS list, jogo dadosDasArmas);
//removes losing element of preference
ListElem removeElement(ListElem list, int index);
//add player data type to workbench
Player createPlayer(ListElem list);

void printPlayer(Player p);

void Export(ListElem list, jogo dadosDasArmas,int i);