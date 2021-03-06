#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "vitesse.h"
#include "action.h"
#include "position.h"
#include "path.h"
int calculBecauseCollision(Circuit pilote,Carte map,Position current,Vitesse vCurrent,Action *action1,Position pilote1,int *posTab,int *nbBoost);
void displayMap(Carte map,FILE *f);
void displayAction(Action *action,FILE *f,int taille);

#endif
