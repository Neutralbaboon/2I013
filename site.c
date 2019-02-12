#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "site.h"

Site *construireSite(char* nom, float la, float lo, char* categorie, char* pays, int enDanger, Site* suivant){
	Site *retour = malloc(sizeof(Site));
	if(!retour){
		libererSite(suivant);
		return NULL;
	}

	retour->nom = strdup(nom);
	if(!retour->nom){
		free(retour);
		libererSite(suivant);
		return NULL;
	}	

	retour->la = la;
	retour->lo = lo;

	retour->categorie = strdup(categorie);
	if(!retour->categorie){
		free(retour->nom);
		free(retour);
		libererSite(suivant);
		return NULL;
	}

	retour->pays = strdup(pays);
	if(!retour->pays){
		free(retour->categorie);
		free(retour->nom);
		free(retour);
		libererSite(suivant);
		return NULL;
	}

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