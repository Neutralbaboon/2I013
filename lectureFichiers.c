#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "site.h"
#include "lectureFichiers.h"


Site *LectureCSV(char* fichier){
	FILE *f;
	f = fopen(fichier,"r");
	if(!f){
		fprintf(stderr,"Erreur fichier inexistant ou permission insuffisante\n");
		return NULL;
	}
	printf("Lecture du fichier ...\n");

	char nom[MAX_NOM];
	float la;
	float lo;
	char categorie[MAX_CATEGORIE];
	char pays[MAX_PAYS];
	int enDanger;
	Site *save = NULL;
	char buffer[MAX_LIGNE];

	//Ignorer le commentaire en première ligne
	fgets(buffer,MAX_LIGNE, f);

	while(fgets(buffer, MAX_LIGNE, f)!=NULL){
		stringToArgs(buffer, nom, &la, &lo, categorie, pays, &enDanger);
		save = construireSite(nom, la, lo, categorie, pays, enDanger, save);
		if(!save){
			fprintf(stderr,"Erreur d'allocation . Pas assez de mémoire ?\n");
			return NULL;
		}
		affichageSite(save);
	}
	fclose(f);
	return save;
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