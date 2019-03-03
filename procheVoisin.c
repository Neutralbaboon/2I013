#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "haversine.h"
#include "site.h"
#include "gestionItineraire.h"
#include "procheVoisin.h"

Lsite *lancerProcheVoisin(Site **tableau, double** distance, int n, float la, float lo){
	Lsite *liste=NULL;
	double tempstotal = 0;
	double calcul;
	int siteprecedent;
	int siteprochain;

	//On ajoute à la liste et au temps le site culturel le plus proche du lieu de départ
	siteprochain = premierProcheVoisin(la, lo, n, tableau);	
	calcul = calculDistance(la, lo, tableau[siteprochain]->la, tableau[siteprochain]->lo)/VITESSE + TEMPS_SITE;


	do{
		tempstotal+= calcul;
		liste = ajouterListeItineraire(liste, siteprochain);
		tableau[siteprochain]->visite = 1;
		siteprecedent = siteprochain;
		siteprochain = suivantProcheVoisin(tableau, distance, n, siteprecedent);
		calcul = calculDistance(tableau[siteprecedent]->la, tableau[siteprecedent]->lo, tableau[siteprochain]->la, tableau[siteprochain]->lo)/VITESSE + TEMPS_SITE;
		//printf("%s position = (%lf , %lf) \n",tableau[newIndicePlusProche]->nom,tableau[newIndicePlusProche]->la,tableau[newIndicePlusProche]->lo);
	}while(tempstotal + calcul + calculDistance(la, lo, tableau[siteprochain]->la, tableau[siteprochain]->lo)/VITESSE <= MAX_VOYAGE);

	return liste;

}

int premierProcheVoisin(float la, float lo, int n, Site **tableau){
	int k;
	double calcul;
	int indicePlusProche=0;
	double longueurmin = calculDistance(la, lo, tableau[0]->la, tableau[0]->lo);

	for(k=1;k<n;k++){
		calcul = calculDistance(la, lo, tableau[k]->la, tableau[k]->lo);
		if(longueurmin>calcul){
			longueurmin=calcul;
			indicePlusProche = k;
		}
	}

	return indicePlusProche;
}


int suivantProcheVoisin(Site **tableau, double** distance, int n, int actuel){
	int k;
	int retour=0;
	if(strcmp(tableau[actuel]->categorie,"Mixed")==0){
		while(tableau[retour]->visite == 1){
			retour++;
		}

		for(k=retour+1;k<n;k++){
			if (tableau[k]->visite == 0 && distance[actuel][k]<distance[actuel][retour])
			{
				retour = k;
			}
		}

		return retour;

	}
	else{
		while(tableau[retour]->visite == 1 || strcmp(tableau[retour]->categorie,tableau[actuel]->categorie)==0){
			retour++;
		}

		for(k=retour+1;k<n;k++){
			if (tableau[k]->visite == 0 && distance[actuel][k]<distance[actuel][retour] && strcmp(tableau[k]->categorie,tableau[actuel]->categorie)!=0)
			{
				retour = k;
			}
		}		
		return retour;

	}
}

