#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "site.h"
#include "lectureFichiers.h"


Site **LectureCSV(char* fichier, int *n){

	// On essaye d'ouvrir le fichier puis on compte le nombre de ligne à lire

	FILE *f;
	f = fopen(fichier,"r");
	if(!f){
		fprintf(stderr,"Erreur fichier inexistant ou permission insuffisante\n");
		return NULL;
	}
	printf("Lecture du fichier ...\n");

	*n = -1;
	char buffer[MAX_LIGNE];

	while(fgets(buffer, MAX_LIGNE, f)!=NULL){
		*n = *n +1;
	}

	fclose(f);

	// On crée le tableau contenant les données

	Site **retour = (Site **)malloc(sizeof(Site*)* (*n));

	// On reouvre le fichier afin de construire le tableau avec les données

	f = fopen(fichier,"r");
	if(!f){
		fprintf(stderr,"Une erreur est survenue !\n");
		return NULL;
	}

	int k=0;
	char nom[MAX_NOM];
	float la;
	float lo;
	char categorie[MAX_CATEGORIE];
	char pays[MAX_PAYS];
	int enDanger;

	//Ignorer le commentaire en première ligne
	fgets(buffer,MAX_LIGNE, f);

	// On remplit le tableau

	while(fgets(buffer, MAX_LIGNE, f)!=NULL){
		stringToArgs(buffer, nom, &la, &lo, categorie, pays, &enDanger);
		retour[k] = construireSite(nom, la, lo, categorie, pays, enDanger);
		if(!retour[k]){
			fprintf(stderr,"Erreur d'allocation . Pas assez de mémoire ?\n");
			libererSite(retour,k+1);
			return NULL;
		}
		k++;
	}
	fclose(f);
	return retour;
}

void stringToArgs(char* buffer, char* nom, float* la, float *lo, char* categorie, char* pays, int *enDanger){
	stringToString(&buffer,nom);
	stringToFloat(&buffer,la);
	stringToFloat(&buffer,lo);
	stringToString(&buffer,categorie);
	stringToString(&buffer,pays);

	while(*buffer!=','){
		buffer = buffer+1;
	}
	buffer = buffer+1;

	stringToInt(&buffer, enDanger);

}

void stringToString(char** buffer, char *dest){
	int k=0;
	while((*buffer)[k]!=','){
		dest[k]=(*buffer)[k];
		k++;
	}
	dest[k]='\0';
	*buffer = (*buffer)+k+1;
}

void stringToFloat(char **buffer, float *dest){
	int k=0;
	while((*buffer)[k]!=','){
		k++;
	}
	(*buffer)[k]='\0';
	*dest = atof(*buffer);
	*buffer = (*buffer) + k +1;
}

void stringToInt(char **buffer, int *dest){
	int k=0;
	while((*buffer)[k]!='\0'){
		k++;
	}
	(*buffer)[k]='\0';
	*dest = atoi(*buffer);
	*buffer = (*buffer) + k +1;
}