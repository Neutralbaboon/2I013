#ifndef GESTION_ITINERAIRE
#define GESTION_ITINERAIRE

#include "site.h"

//---------------------
//-----Structures------
//---------------------

typedef struct lsite{
	int site;
	struct lsite *suivant;
} Lsite;

//---------------------
//-----Prototypes------
//---------------------

Lsite *ajouterListeItineraire(Lsite *liste, int site);
void libererListeItineraire(Lsite *iti);
void afficherListeItineraire(Site **tableau, Lsite *liste);
int compterPoints(Site **tableau, Lsite *liste);
void enregistrerItineraire(Site **tableau, Lsite *liste, float la, float lo);
void ouvrirItineraire(void);
void afficherPoint(Site **tableau, Lsite *liste);
void optimiserItineraire(double **distance, Lsite *liste);
double compterHeure(Site **tableau, double **distance, double la , double lo , Lsite *liste);





#endif