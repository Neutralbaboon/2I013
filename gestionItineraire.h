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





#endif