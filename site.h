#ifndef SITE_H
#define SITE_H

//---------------------
//-----Constantes------
//---------------------

	//LECTURE FICHIERS
#define MAX_NOM 200
#define MAX_CATEGORIE 50
#define MAX_PAYS 100
#define MAX_LIGNE MAX_NOM+MAX_CATEGORIE+MAX_PAYS+50

	//CONSTANTES SUJETS

#define MAX_VOYAGE 3*7*24
#define TEMPS_SITE 6
#define	VITESSE 80

//---------------------
//-----Structures------
//---------------------

typedef struct site{
	char* nom;
	float la;
	float lo;
	char* categorie;
	char* pays;
	int enDanger;
	int visite;
} Site;

//---------------------
//-----Prototypes------
//---------------------

Site *construireSite(char* nom, float la, float lo, char* categorie, char* pays, int enDanger);
void libererSite(Site **liste, int n);



#endif