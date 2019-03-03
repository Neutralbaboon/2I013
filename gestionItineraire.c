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

/*int compterPoints(Lsite *liste){
	//TODO
}

void enregistrerItineraire(Lsite *liste){
	//TODO
}

void ouvrirItineraire(void){
	//TODO
}*/

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

