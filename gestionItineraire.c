#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestionItineraire.h"
#include "haversine.h"

Lsite *ajouterListeItineraire(Lsite *liste, int site){
	Lsite *ajout = (Lsite *)malloc(sizeof(Lsite));
	ajout->site = site;
	ajout->suivant = NULL;

	if(liste == NULL){
		return ajout;
	}

	Lsite *cur=liste;

	while(cur->suivant){
		cur = cur->suivant;
	}

	cur->suivant = ajout;
	return liste;

}

void ajouterentreListeItineraire(Lsite *sitea , int ajout){
	Lsite *lajout = malloc(sizeof(Lsite));
	lajout->site = ajout;
	lajout->suivant = sitea->suivant;
	sitea->suivant = lajout;
}

void supprimerSiteSuivant(Lsite *site){
	Lsite *save = site->suivant->suivant;
	free(site->suivant);
	site->suivant = save;
}

int compterPoints(Site **tableau, Lsite *liste){
	int score=0;
	Lsite *cur1=liste;
	Lsite *cur2;
	int found;
	while(cur1){
		score++; // Chaque site UNESCO visité compte pour 1 point
		cur2 = liste;
		found = 0;
		while(cur2!=cur1 && !found){
			if(strcmp(tableau[cur1->site]->pays,tableau[cur2->site]->pays)==0) found = 1; //Chaque pays différent visité compte pour 2 points
			cur2 = cur2->suivant;
		}
		if(!found){
			score+=2;
		}
		if(tableau[cur1->site]->enDanger) score+=3; //Chaque site qui est listé comme “en danger” compte pour 3 points
		cur1 = cur1->suivant;
	}
	
	return score;
}

double compterHeure(Site **tableau, double **distance, double la , double lo , Lsite *liste){
	double heure;

	heure = calculDistance(tableau[liste->site]->la, tableau[liste->site]->lo, la, lo) / VITESSE;
	heure += TEMPS_SITE;

	while(liste->suivant){
		heure += distance[liste->site][liste->suivant->site]/VITESSE;
		heure += TEMPS_SITE;
		liste = liste->suivant;
	}

	heure += calculDistance(tableau[liste->site]->la, tableau[liste->site]->lo, la, lo) / VITESSE;
	return heure;
}

void enregistrerItineraire(Site **tableau, Lsite *liste, float la, float lo){
	FILE* f=fopen("Tour.txt", "w");
	if(f==NULL){
		fprintf(stderr,"Droit d'accès ou espace mémoire insuffisant\n");
		return;
	}

	fprintf(f,"%f, %f,\n",la,lo);

	while(liste){
		fprintf(f,"%f, %f, %s\n",tableau[liste->site]->la ,tableau[liste->site]->lo, tableau[liste->site]->categorie);
		liste = liste->suivant;
	}

	fprintf(f,"%f, %f,\n",la,lo);

	fclose(f);
	
}


void ouvrirItineraire(void){
	system("java -jar UnescoMap.jar");
}


void afficherListeItineraire(Site **tableau, Lsite *liste){
	while(liste){
		printf("(%f,%f) %s \t %s %d\n", tableau[liste->site]->la, tableau[liste->site]->lo, tableau[liste->site]->categorie, tableau[liste->site]->pays, tableau[liste->site]->enDanger);
		liste = liste->suivant;
	}
}

void libererListeItineraire(Lsite *iti){
	Lsite *save = NULL;
	while(iti!=NULL){
		save = iti->suivant;
		free(iti);
		iti = save;
	}
}

void afficherPoint(Site **tableau, Lsite *liste){
	printf("\n**************************\n");
	printf("* NOMBRE DE POINTS : %3d *\n",compterPoints(tableau, liste));
	printf("**************************\n");
}

int min(int x , int y){
	if(x<y){
		return x;
	}
	return y;
}

int max(int x, int y){
	if(x>y){
		return x;
	}
	return y;
}

int nbelem(Lsite *liste){
	int retour = 0;
	while(liste){
		retour++;
		liste = liste->suivant;
	}
	return retour;
}


int *deuxopt(double **distance, int *tsite, int nbsite){
	int amelioration = 1;
	int i;
	int j;
	double dxixi1; 
	double dxjxj1;
	double dxixj;
	double dxi1xj1;

	while(amelioration){
		amelioration = 0;
		for(i=0;i<nbsite-1;i++){
			for(j=0;j<nbsite-1;j++){
				if(j!= i-1 && j!= i && j!= i+1){
					dxixi1 = distance[tsite[i]][tsite[i+1]];
					dxjxj1 = distance[tsite[j]][tsite[j+1]];
					dxixj = distance[tsite[i]][tsite[j]];
					dxi1xj1 = distance[tsite[i+1]][tsite[j+1]];
					if(dxixi1 + dxjxj1 > dxixj + dxi1xj1){
						amelioration = 1;
						tsite = remplacerarrete(tsite,i,j,nbsite);
					}
				}
			}
		}
	} 
	return tsite;

}

int *remplacerarrete(int *tsite, int i, int j, int nbsite){
	int *retour = malloc(sizeof(int)* nbsite);
	int k;
	int l;

	for(k=0;k<=min(i,j);k++){
		retour[k] = tsite[k];
	}

	for(l=max(i,j);l>min(i,j);l--){
		retour[k] = tsite[l]; 
		k++;
	}

	for(k=max(i,j)+1;k<nbsite;k++){
		retour[k]= tsite[k];
	}


	free(tsite);
	return retour;
}

void optimiserItineraire(double **distance, Lsite *liste){
	int nbsite = nbelem(liste);
	int *tsite = malloc(sizeof(int) * nbsite);
	int k= 0;

	Lsite *saveliste = liste;
	while(saveliste){
		tsite[k]=saveliste->site;
		k++;
		saveliste = saveliste->suivant;
	}

	tsite = deuxopt(distance,tsite, nbsite);

	saveliste = liste;
	k=0;
	while(saveliste){
		saveliste->site = tsite[k];
		k++;
		saveliste = saveliste->suivant;
	}

	free(tsite);

}

int essaiCompleterItineraire(Site **tableau, double **distance, Lsite *liste, int n, double la , double lo){
	//On recherche par quel catégorie de site ne peut pas compléter l'itinéraire
	char nontype[MAX_CATEGORIE];
	categorieImpossible(tableau,liste,nontype);

	// Pour tout couple (a,b=a+1) d'arrete on cherche le site le plus proche
	Lsite *curseura = liste;
	Lsite *curseurb= liste->suivant;
	int siteencours;
	double distanceencours;

	//On enregistre a tel que la déviation soit minimum
	Lsite *curseuramin;
	int siteplusproche;
	double mindistance = 100000;

	while(curseurb){
		siteencours = plusProcheSiteQuiNEstPasDeType(tableau, distance, curseura->site, curseurb->site, n, nontype);
		distanceencours = distance[siteencours][curseura->site]+distance[siteencours][curseurb->site];
		if(distanceencours<mindistance){
			curseuramin = curseura;
			mindistance = distanceencours;
			siteplusproche = siteencours;
		}
		curseura = curseura->suivant;
		curseurb = curseurb->suivant;
	}

	ajouterentreListeItineraire(curseuramin , siteplusproche);
	if(compterHeure(tableau, distance, la, lo, liste)<MAX_VOYAGE){
		return 1;
	}
	
	supprimerSiteSuivant(curseuramin);
	return 0;

}

int plusProcheSiteQuiNEstPasDeType(Site **tableau, double** distance, int a, int b, int n , char* nontype){
	int k;
	int sitemin;
	double distancemin=2000000;
	double calcul;

	for(k=0;k<n;k++){
		if(k!=a && k!=b && strcmp(tableau[k]->categorie, nontype)!=0 ){
			calcul = distance[a][k]+distance[b][k];
			if(calcul <distancemin){
				distancemin = calcul;
				sitemin = k;
			}

		}
	}

	return sitemin;

}

void categorieImpossible(Site **tableau, Lsite *liste, char *nontype){
	int nombrenaturel = nombreDeNaturel(tableau,liste);
	int nombreculturel = nombreDeCulturel(tableau,liste);

	if(nombrenaturel > nombreculturel){
		strcpy(nontype,"Natural");
	}
	else{
		if(nombrenaturel< nombreculturel){
			strcpy(nontype,"Cultural");		
		}
		else{
			strcpy(nontype, "");
		}
	}


}

int nombreDeNaturel(Site **tableau, Lsite *liste){
	int retour=0;
	while(liste){
		if(strcmp(tableau[liste->site]->categorie,"Natural")==0){
			retour++;
		}
		liste = liste->suivant;
	}

	return retour;

}

int nombreDeCulturel(Site **tableau, Lsite *liste){
	int retour=0;
	while(liste){
		if(strcmp(tableau[liste->site]->categorie,"Cultural")==0){
			retour++;
		}
		liste = liste->suivant;
	}
	return retour;
}

int nombreDeMixte(Site **tableau, Lsite *liste){
	int retour=0;
	while(liste){
		if(strcmp(tableau[liste->site]->categorie,"Mixed")==0){
			retour++;
		}
		liste = liste->suivant;
	}
	return retour;
}

void completerItineraire(Site **tableau, double **distance, Lsite *liste, int n, double la , double lo){
	while(essaiCompleterItineraire(tableau, distance, liste, n, la , lo)){
		optimiserItineraire(distance, liste);
	}

}

