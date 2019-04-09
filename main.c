#include <stdio.h>
#include <stdlib.h>
#include "lectureFichiers.h"
#include "site.h"
#include "haversine.h"
#include "procheVoisin.h"
#include "gestionItineraire.h"

int main(int argc, char** argv){
	if(argc!=3){
		fprintf(stderr,"Usage : projet LAT LONG\n");
		return 1;
	}
	float la = atof(argv[1]);
	float lo = atof(argv[2]);
	printf("Commande : ./projet %f %f\n", la,lo);

	int n;

	Site **tableau=LectureCSV("unesco.csv", &n);

	if(tableau == NULL){
		fprintf(stderr,"Une erreur s'est produite dans la lecture du fichier ! \n");
		return 1;
	}

	double **distance = calculMatriceDistance(tableau, n);
	Lsite *liste = lancerProcheVoisin(tableau, distance, n, la, lo);

	printf("Nombre d'heure avant optimisation = %lf\n",compterHeure(tableau, distance, la , lo , liste));
	afficherPoint(tableau,liste);

	optimiserItineraire(distance,liste);
	completerItineraire(tableau, distance, liste, n, la, lo);


	//afficherListeItineraire(tableau,liste);
	printf("Nombre d'heure apres optimisation et complément = %lf\n",compterHeure(tableau, distance, la , lo , liste));
	afficherPoint(tableau,liste);
	printf("Nombre de site culturel :\t%2d\n", nombreDeCulturel(tableau, liste));
	printf("Nombre de site naturel : \t%2d\n", nombreDeNaturel(tableau, liste));
	printf("Nombre de site mixte :   \t%2d\n", nombreDeMixte(tableau, liste));
	printf("________________________________________\n");
	printf("TOTAL =                  \t%d\n", nbelem(liste));


	enregistrerItineraire(tableau,liste,la,lo);
	ouvrirItineraire();


	libererListeItineraire(liste);
	libererMatriceDistance(distance,n);
	libererSite(tableau, n);
	return 0;
}
