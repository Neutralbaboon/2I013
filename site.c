#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "site.h"

Site *construireSite(char* nom, float la, float lo, char* categorie, char* pays, int enDanger){
	Site *retour = malloc(sizeof(Site));
	if(!retour){
		return NULL;
	}

	retour->nom = strdup(nom);
	if(!retour->nom){
		free(retour);
		return NULL;
	}	

	retour->la = la;
	retour->lo = lo;

	retour->categorie = strdup(categorie);
	if(!retour->categorie){
		free(retour->nom);
		free(retour);
		return NULL;
	}

	retour->pays = strdup(pays);
	if(!retour->pays){
		free(retour->categorie);
		free(retour->nom);
		free(retour);
		return NULL;
	}

	retour->enDanger = enDanger;
	return retour;
}


void libererSite(Site **liste, int n){
	int k;
	for(k=0;k<n-1;k++){
		free((liste[k])->nom);
		free((liste[k])->categorie);
		free((liste[k])->pays);
		free(liste[k]);
	}
	free(liste);

}
