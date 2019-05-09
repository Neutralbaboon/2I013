#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "grasp.h"
#define PARAMETRE2 1000 //Nombre de répétition
#define PARAMETRE3 10 //Nombre de site d'avance



Lsite *lancerGrasp(Site **tableau, double** distance, int nbsite, float la, float lo, int parametre){
	// Création du tableau siteVisite 0 = Pas visité 1 = visité
	int *siteVisite = malloc(nbsite * sizeof(int));
	int k;
	for(k=0;k<nbsite;k++){
		siteVisite[k] = 0;
	}




}


// Site suivant renvoie un tableau de deux sites ( un culturel , un naturel)

int *siteSuivant(Site **tableau, double **distance, int *sitevisite, Lsite* liste, int nbsite, int parametre, int actuel){
	//On récupère une liste de 10 candidats
	int *listecandidats = meilleursCandidats(tableau, distance, sitevisite, parametre, nbsite, actuel);



}


// On sélectionne les meilleurs candidats : Au moins un culturel , Au moins un naturel

int *meilleursCandidats(Site **tableau, double **distance, int *sitevisiteoriginal, int parametre, int nbsite, int actuel){
	int *retour = malloc(parametre * sizeof(int));
	int *sitevisite = copieSiteVisite(sitevisiteoriginal, nbsite);
	int culturel = 0;
	int naturel = 0;
	int ajout;
	int i;
	int k;

	for(i=0;i<parametre;i++){
		ajout = 0;
		while(sitevisite[ajout]!=0){
			ajout++;
		}
		for(k=ajout+1;k<nbsite;k++){
			if(sitevisite[k]==0 && distance[actuel][k]<distance[actuel][ajout]){
				if(i!=parametre-1 || ((culturel !=0 || strcmp(tableau[k]->categorie, "Natural") != 0) && (naturel !=0 || strcmp(tableau[k]->categorie, "Cultural") != 0))){
					ajout = k;
				}
			}
		}

		if(strcmp(tableau[k]->categorie, "Natural")==0){
			naturel++;
		}
		else{ 
				if(strcmp(tableau[k]->categorie, "Cultural")==0){
					culturel++;
				}
				else{
					culturel++;
					naturel++;
				}
		}

		retour[i] = ajout;
		sitevisite[ajout]= 1;

	}

	free(sitevisite);
	return retour;
}



//Choix du meilleurs culturel et naturel et marques les deux visités
int *choisirDeuxMeilleurs(Site **tableau, double **distance, int *listecandidats, int* sitevisiteoriginal, int parametre, int nbsite){
	int *scoressites = malloc(parametre * sizeof(int));
	int *listecandidats2;
	int *retour = malloc(2 * sizeof(int));
	Lsite *construction = NULL;
	int *sitevisite;
	int k;
	int i;
	int j;
	int actuel;
	int meilleurpoints;

	for(k=0;k<parametre;k++){ // Candidats k
		scoressites[k]=0;
		for(i=0;i<PARAMETRE2;i++){ // Répétition n°
			actuel = listecandidats[k];
			sitevisite = copieSiteVisite(sitevisiteoriginal, nbsite);
			for(j=0;j<PARAMETRE3;j++){ //Choix du chemin
				sitevisite[actuel] = 1;
				listecandidats2 = meilleursCandidats(tableau, distance, sitevisite, parametre, nbsite, actuel);
				actuel = listecandidats2[rand() % parametre];
				ajouterListeItineraire(construction, actuel);
				free(listecandidats2);
			}
			scoressites[k] += compterPoints(tableau, construction);
			free(construction);
			construction = NULL;
		}
	}

	//Choix du meilleur culturel en 0
	meilleurpoints = 0;
	for(k=0;k<parametre;k++){
		if(strcmp(tableau[listecandidats[k]]->categorie, "Natural")!=0 && scoressites[k] > meilleurpoints){
			retour[0] = listecandidats[k];
			meilleurpoints = scoressites[k];
		}
	}

	//Choix du meilleur naturel en 1

	for(k=0;k<parametre;k++){
		if(strcmp(tableau[listecandidats[k]]->categorie, "Cultural")!=0 && scoressites[k] > meilleurpoints){
			retour[1] = listecandidats[k];
			meilleurpoints = scoressites[k];
		}
	}

	sitevisiteoriginal[retour[0]]=1;
	sitevisiteoriginal[retour[1]]=1;
	free(scoressites);
	return retour;
}


int *copieSiteVisite(int *sitevisite, int nbsite){
	int k;
	int *retour = malloc(nbsite * sizeof(int));
	for(k=0;k<nbsite;k++){
		retour[k] = sitevisite[k];
	}
	return retour;
}

