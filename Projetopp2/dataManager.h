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

//manages the listoflists and sorts preferences of the players
void ManageData(LISTofLISTS list);
//removes losing element of preference
ListElem removeElement(ListElem list, int index);
//add player data type to workbench
Player createPlayer(ListElem list);
//compares preferences
void ComparePreferences(Player p1, Player p2);

void printPlayer(Player p);

void Export(LISTofLISTS list);