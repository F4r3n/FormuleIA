#include <stdlib.h>
#include <stdio.h>
#include "pile.h"

Pile *creerPile()
{
	Pile *pile=malloc(sizeof(Pile));
	pile->head=NULL;
	pile->taille=0;

	return pile;

}

int videPile(Pile *positionsPile)
{
	if(positionsPile->taille==0)
		return 1;

	else return 0;
}

void empiler(Pile *positionsPile, Act b)
{
	NoeudP *cell=malloc(sizeof(NoeudP));

	cell->a.action.vx=b.action.vx;
	cell->a.action.vy=b.action.vy;
	cell->a.position=b.position;
	cell->a.preced.x=b.preced.x;
	cell->a.preced.y=b.preced.y;

	cell->suivant=positionsPile->head;
	positionsPile->head=cell;
	positionsPile->taille++;
}

Act depiler(Pile *positionsPile)
{
	Act a;
	a.position=-1;
	if(videPile(positionsPile)) return a;
	NoeudP *cell = positionsPile->head;
	a=positionsPile->head->a;	
	positionsPile->head=positionsPile->head->suivant;
	free(cell);
	positionsPile->taille--;
	return a;
}
