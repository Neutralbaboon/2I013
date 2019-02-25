#ifndef SITE_H
#define SITE_H

//---------------------
//-----Constantes------
//---------------------

#define MAX_NOM 200
#define MAX_CATEGORIE 50
#define MAX_PAYS 50
#define MAX_LIGNE MAX_NOM+MAX_CATEGORIE+MAX_PAYS+50


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
} Site;

//---------------------
//-----Prototypes------
//---------------------

Site *construireSite(char* nom, float la, float lo, char* categorie, char* pays, int enDanger);
void libererSite(Site **liste, int n);



#endif