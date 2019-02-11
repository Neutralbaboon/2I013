#ifndef LECTUREFICHIERS_H
#define LECTUREFICHIERS_H

#include <ctype.h>
#include <stdio.h>
#include "site.h"

//Lit le fichier .CSV et génère la liste chainée
Site *LectureCSV(char* fichier);

//Place la chaine de caractère jusqu'à la prochaine virgule dans dest et met le curseur après la virgule
void stringToArgs(char* buffer, char* nom, float* la, float *lo, char* categorie, char* pays, int *enDanger);

//Convertit la chaine de caractère jusqu'à la prochaine virgule en entier et met le curseur après la virgule
void stringToString(char** buffer, char *dest);

//Convertit la chaine de caractère jusqu'à la prochaine virgule en flottant et met le curseur après la virgule
void stringToFloat(char **buffer, float *dest);

//Convertit la chaine de caractère jusqu'à la prochaine virgule en entier et met le curseur après la virgule
void stringToInt(char **buffer, int *dest);

#endif