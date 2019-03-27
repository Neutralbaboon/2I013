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

	afficherListeItineraire(tableau,liste);

	optimiserItineraire(distance,liste);

	afficherListeItineraire(tableau,liste);

	afficherPoint(tableau,liste);

	enregistrerItineraire(tableau,liste,la,lo);
	ouvrirItineraire();


	libererListeItineraire(liste);
	libererMatriceDistance(distance,n);
	libererSite(tableau, n);
	return 0;
}
