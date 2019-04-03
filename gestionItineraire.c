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


void optimiserItineraire(double **distance, Lsite *liste){
	int modification = 1;
	Lsite *curseur1;
	Lsite *curseur2;
	int save;

	while(modification){
		curseur1 = liste;
		modification = 0;
		while(curseur1 && !modification){
			curseur2 = curseur1;
			while(curseur2 && !modification){
				if(curseur1 != curseur2 && curseur1->suivant != curseur2 && distance[curseur1->site][curseur1->suivant->site] > distance[curseur1->site][curseur2->site]){
					modification = 1;
					save = curseur1->suivant->site;
					curseur1->suivant->site = curseur2->site;
					curseur2->site = save;
				}
				curseur2 = curseur2 -> suivant;
			}
			curseur1 = curseur1 -> suivant;
		}
	}


}

