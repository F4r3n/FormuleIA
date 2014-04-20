#ifndef FONCTION_H
#define FONCTION_H
#define MAX 200

#include <stdlib.h>
#include <stdio.h>
#include "../include/pile.h"
#include "struct.h"
#include "../include/file.h"

typedef struct _Circuit
{
	short taille;
	Position arrivee;
	Position depart;

}Circuit;

typedef struct _Carte
{

	int **map;
	short tx;
	short ty;

}Carte;

void autourPosition(Position current,Vitesse vit,Carte *carte,int boost, Position autour[6][6],int valeur[6][6]);
int shortCutF(Circuit pilote,Carte carte, Position depart,Vitesse vDepart, Action *action);
int retrouverChemin(Pile *pileBackUp,Action *action,int gen,int taille);
int recherchePos(ElementFile *tab,int generation, int taille);
int isArrived(Position *posArrived,short *alreadyArrived,int **map,Position pilot1,Position pilot2,int taille);
void destruction(char ****tab);
char opti(Vitesse v);
int isPossible(Position current,Vitesse vCurrent, Carte *carte,int boost);

#endif
