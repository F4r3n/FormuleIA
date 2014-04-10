#include "fonction.h"
#include "Liste/listeA.h"
#include "pile/pile.h"
#include "struct.h"


void autourPosition(Position current,Vitesse vit,int taillex,int tailley, char map[MAX][MAX],int boost,Position autour[6][6],int valeur[6][6])
{
	//	puts("Autour pos");
	int b;
	b=(boost)? 2:1;
	Position suivant;
	suivant.x=current.x+vit.vx;
	suivant.y=current.y+vit.vy;
	int max=3*b;

	for(int i=0;i<max;i++){
		for(int j=0;j<max;j++){
			int sx=suivant.x-b+j;
			int sy=suivant.y-b+i;
			if((sx>=0 && sx<taillex) && (sy>=0 && sy<tailley)){
				autour[i][j].x=sx;
				autour[i][j].y=sy;
				valeur[i][j]=map[sy][sx];
			//	printf("map %d\n",map[sy][sx]);
			}
			else {
				autour[i][j].x=-1;
				autour[i][j].y=-1;
				valeur[i][j]='.';
			}
		}
	}
/*	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("(%d %d)",autour[i][j].x,autour[i][j].y);
		}
		puts(" ");
	}

	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			printf("(%d)",valeur[i][j]);
		}
		puts(" ");
	}*/
}


int shortCutF(Circuit pilote, Position depart,Vitesse vDepart, Action action[200]){
	Action possible[9]={{0,0}};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			possible[8-i*3-j].vx=-1+i;
			possible[8-i*3-j].vy=-1+j;

		}
	}

	//	for(int i=0;i<9;i++)
	//		printf("%d %d\n",possible[i].vx,possible[i].vy);

	short view[MAX][MAX]={{0,0}};
	Vitesse vView[MAX][MAX]={{{0,0}}};
	Vitesse vCurrent=vDepart;
	Position current=depart;
	//	current=pilote.depart;
	FileF *fi=creerFileF();
	Pile *pileSauvegarde=creerPile();
	int poids[6][6]={{'.'}};
	Position autour[6][6]={{{-1,-1}}};

	Action act={0,0};
	ElementFile e={{0,0},{0,0},{0,0},0};
	e.preced=current;
	e.vitesse=vCurrent;
	e.action=act;
	e.generationP=0;
	enfilerF(fi,e);
	int k=0;
	int fini=0;
	Position futur={0,0};
	int gen=0;

	while(pilote.map[current.y][current.x]!='='){

		if(videFileF(fi)){
			puts("File vide");
			return 0;

		}
		ElementFile a=defilerF(fi);

		empiler(pileSauvegarde,a);

		current.x=a.preced.x;
		current.y=a.preced.y;
		vCurrent=a.vitesse;
		gen=a.generation;

		autourPosition(current,vCurrent,pilote.tx,pilote.ty,pilote.map,0,autour,poids);
		view[current.y][current.x]=1;
		//	vView[current.y][current.x]=vCurrent;

		//	printf("Current %d %d\n",current.x,current.y);

		//	if( (current.x==3 && current.y==0))break;
		//		printf("k: %d\n",k);	
		int i=0;
		int j=0;
		int nombreCasesEnfiles=0;
		k++;
		for(i=0;i<9;i++){

			Vitesse vFutur={0,0};
			vFutur.vx=possible[i].vx+vCurrent.vx;
			vFutur.vy=possible[i].vy+vCurrent.vy;
			futur.x=vFutur.vx+current.x;
			futur.y=vFutur.vy+current.y;
			int norme=(vFutur.vx)*(vFutur.vx) +(vFutur.vy)*(vFutur.vy);
			/*	printf(" Possible %d %d\n",possible[i].vx,possible[i].vy);
				printf(" vFutur %d %d\n",vFutur.vx,vFutur.vy);
				printf(" Futur %d %d\n",futur.x,futur.y);
				printf(" Tableau %d %d\n",vView[futur.y][futur.x].vx,vView[futur.y][futur.x].vy);
				printf(" i %d\n\n",i);*/
			

			if( futur.x < pilote.tx
					&&  futur.y< pilote.ty
					&& futur.x>=0
					&& futur.y>=0
					&& (vView[futur.y][futur.x].vx!=vFutur.vx || vView[futur.y][futur.x].vy!=vFutur.vy)
					&& autour[possible[i].vy+1][possible[i].vx+1].x!=-1
					&& poids[possible[i].vy+1][possible[i].vx+1]!=46
					&& norme <=25){

				if(view[futur.y][futur.x]==0){
					ElementFile a;
					a.action=possible[i];
					a.preced=futur;
					a.vitesse=vFutur;
					a.generation=k+i;
					a.generationP=gen;
					vView[futur.y][futur.x]=vFutur;
					enfilerF(fi,a);
					nombreCasesEnfiles++;
					if(pilote.map[futur.y][futur.x]==1) {
						fini=1;
						current=futur;
						empiler(pileSauvegarde,a);
						/*	puts("**********Enfiler*********");
							printf("Futur %d %d \t%d %d\n",futur.x,futur.y,vFutur.vx,vFutur.vy);
							puts("**********Enfiler*********");*/

						break;
					}
					/*	puts("**********Enfiler*********");
						printf("Futur %d %d \t%d %d\n",futur.x,futur.y,vFutur.vx,vFutur.vy);
						puts("**********Enfiler*********");*/


				}
				else j++;
			}


		}
		//	printf("nombreCasesEnfiles %d\n",nombreCasesEnfiles);

		//On ne marque pas si on ne prend qu'une case
		if(nombreCasesEnfiles<1 && j<1){
			vView[futur.y][futur.x].vx=0;
			vView[futur.y][futur.x].vy=0;
			view[current.y][current.x]=0;

		}
		k+=i;
		if(fini){
			break;

		}


	}
	//	printf("Current %d %d\n",current.x,current.y);

	return retrouverChemin(pileSauvegarde,action,gen,k);

}

int retrouverChemin(Pile *pileBackUp,Action action[500],int gen,int taille){

//	ElementFile *tab=calloc(taille,sizeof(ElementFile));
	int i=0;
//	int j=0;
	int generation=gen;
//	printf("generation1 %d\n",generation);
	//return 0;
	while(generation!=0){
	ElementFile tmp=depiler(pileBackUp);
//	printf("generation %d\n",tmp.generation);
	
		if(tmp.generation==generation){
			generation=tmp.generationP;
			action[i]=tmp.action;
			i++;
//			printf("i %d",i);
//	printf("g %d\n",generation);

		}
//		j++;
//if(j==10) break;

	}
	/*	for(int j=0;j<i;j++){
		printf("preced %d %d\n",tab[j].preced.x,tab[j].preced.y);
		printf("vitesse %d %d\n",tab[j].vitesse.vx,tab[j].vitesse.vy);
		printf("g %d %d\n\n",tab[j].generation,tab[j].generationP);

		}*/
	//	return 0;
	//	Position preced=final;
	//	printf(" Position final %d %d\t Position depart %d %d\n",final.x,final.y,depart.x,depart.y);
/*	action[0]=tab[i-1].action;
	//	printf("action %d %d\n",action[0].vx,action[0].vy);
	int gen=tab[i-1].generationP;
	i=1;
	int index=0;
	while(1){
		index=recherchePos(tab,gen,taille+1);
		//	printf("index %d",index);

		if(index!=-1) {

			gen=tab[index].generationP;

			action[i]=tab[index].action;
			//	printf("i %d\t action %d %d\n",i,action[i].vx,action[i].vy);
			//	printf("preced %d %d\n",preced.x,preced.y);
			//	printf("vitesse %d %d\n",vPreced.vx,vPreced.vy);
			//	printf("G GP %d %d\n",tab[index].generation,tab[index].generationP);


			i++;
		}
		if(gen==0) break;

	}

	//	for(int k=0;k<i;k++)
	//		printf("%d %d\n",action[k].vx,action[k].vy);

*/
	Action temp;
	for(int k=0;k<(i/2);k++) {
		temp=action[k];
		action[k]=action[i-k-1];
		action[i-k-1]=temp;

	}
	return i;
}


int recherchePos(ElementFile *tab,int generation,int taille){
	for(int i=0;i<taille;i++){
		if(tab[i].generation==generation){
			return i;

		}

	}
	return -1;

}

