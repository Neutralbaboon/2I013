#include <stdio.h>
#include <stdlib.h>
#include "lectureFichiers.h"
#include "site.h"

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

	libererSite(tableau, n);
	return 0;
}