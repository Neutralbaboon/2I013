#include <stdio.h>
#include <stdlib.h>
#include "lectureFichiers.h"
#include "site.h"
#include "haversine.h"
#include "procheVoisin.h"
#include "gestionItineraire.h"
#include "benchmark.h"
#include <time.h>




void benchmark(int nbTest){
	
	FILE* f=fopen("Benchmark.txt", "w+");
	if(f==NULL){
		fprintf(stderr,"Droit d'accès ou espace mémoire insuffisant\n");
	}

	
	for(int i=0;i<nbTest;i++){
	
	int n;

	Site **tableau=LectureCSV("unesco.csv", &n);

	if(tableau == NULL){
		fprintf(stderr,"Une erreur s'est produite dans la lecture du fichier ! \n");
	}

	double **distance = calculMatriceDistance(tableau, n);
	Lsite *liste = lancerProcheVoisin(tableau, distance, n, rand()*MAX_LAT, rand()*MAX_LONG);

	//afficherListeItineraire(tableau,liste);

	//afficherPoint(tableau,liste);

	enregistrerItineraire(tableau,liste,rand()*MAX_LAT, rand()*MAX_LONG);
	//ouvrirItineraire();
	
	fprintf(f,"%f   %f  => Score : %d\n",tableau[liste->site]->la ,tableau[liste->site]->lo,compterPoints(tableau,liste));
	

	libererListeItineraire(liste);
	libererMatriceDistance(distance,n);
	libererSite(tableau, n);
	
	

	}	

}

	
	
	
