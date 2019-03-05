#include <stdio.h>
#include <stdlib.h>
#include "gestionItineraire.h"

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
	while(liste){
		score++; // Chaque site UNESCO visité compte pour 1 point
		if(!(tableau[liste->site]->visite)) score +=2; //Chaque pays différent visité compte pour 2 points
		if(tableau[liste->site]->enDanger) score+=3; //Chaque site qui est listé comme “en danger” compte pour 3 points
		return score;
}

/*void enregistrerItineraire(Site **tableau, Lsite *liste){
	FILE* fopen(const char* "tour.txt", const char* "w+");
	
	
}
*/
/*void ouvrirItineraire(void){
	//TODO
}
*/

void afficherListeItineraire(Site **tableau, Lsite *liste){
	while(liste){
		printf("(%f,%f) %s\n", tableau[liste->site]->la, tableau[liste->site]->lo, tableau[liste->site]->categorie);
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

