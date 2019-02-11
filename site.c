#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "site.h"

Site *construireSite(char* nom, float la, float lo, char* categorie, char* pays, int enDanger, Site* suivant){
	Site *retour = malloc(sizeof(Site));
	retour->nom=strdup(nom);
	retour->la = la;
	retour->lo = lo;
	retour->categorie = strdup(categorie);
	retour->pays = strdup(pays);
	retour->enDanger = enDanger;
	retour->suivant = suivant;
	return retour;
}

void libererSite(Site *liste){
	Site *save;
	while(liste){
		free(liste->nom);
		free(liste->categorie);
		free(liste->pays);
		save = liste->suivant;
		free(liste);
		liste = save;
	}
}

void affichageSite(Site *s){
	printf("%s / %s / %s / (%f,%f) en danger = %d\n",s->nom,s->categorie,s->pays,s->la,s->lo,s->enDanger);;
}