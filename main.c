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
	Site *liste=LectureCSV("unesco.csv");
	libererSite(liste);


	return 0;
}