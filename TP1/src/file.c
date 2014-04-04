#include <stdio.h>
#include <stdlib.h>
#include "../include/file.h"

File* creerFile(){
	File* f = malloc(sizeof(File));
	f->tete = NULL;
	f->queue = NULL;
	return f;
}

Cellule* tete(File* f){
	return f->tete;
}

Cellule* queue(File* f){
	return f->queue;
}

Cellule* suivant(Cellule* c){
	if(c == NULL) return NULL;
	if(c->suivant == NULL) return NULL;
	else{
		c = c->suivant;
		return c;
	}

}

unsigned short estVide(File* file){

	if(file == NULL){
		//puts("file nulle");
		return 1;
	}

	if(file->tete == NULL){
		//puts("file vide");
		return 1;
	}


	if(file->queue == NULL){
		//puts("file vide");
		return 1;
	}


	return 0;

}


Cellule* allouer(Element e){
	Cellule* c = malloc(sizeof(Cellule));
	c->suivant = NULL;
	c->contenu = e;
	return c;
}

int enfiler(Element e, File* file){

	if(estVide(file)){
		file->queue = allouer(e); 
		file->tete = file->queue;
		return 1;
	}
	else{
	
		file->queue->suivant = allouer(e);
		file->queue = file->queue->suivant;
		return 1;
	}

	return 0;
}



Element defiler(File* file){

	if(estVide(file))
		return -1;

	Element c = file->tete->contenu;
	Cellule * tmp = file->tete;
	file->tete = file->tete->suivant;

	if(file->tete == NULL){
		
		file->queue = NULL;
	}
	free(tmp);
	return c;



}



void concatener(File* f1, File* f2){

	if(estVide(f2)){
		return;
	}
	if(f1 == NULL){ 
		creerFile();
		f1 = f2;
		return;
	}
	
	if(estVide(f1)){
		f1->tete = f2->tete;
		f1->queue = f2->queue;
		return;
	}
	

	//Noeud* tmp = f1->queue;

	f1->queue->suivant = f2->tete;	
	f1->queue = f2->queue;
	return;

	/*	
		int e;

		do{
		e = defiler(f2);
		if(e != -1){
		enfiler(e,f1);
		}
		}while(e != -1);

		free(f2);
		return 1;
	 */
}




void afficher(File* file){
	if(!estVide(file)){
		Cellule* courant = tete(file);

		do{
			printf("%d -> ", courant->contenu);
			courant = suivant(courant);
		}while(courant != NULL);

		puts("NULL");
	}
	else
		puts("NULL");

}