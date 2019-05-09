#include <time.h>
#include <stdlib.h>
#include "gestionItineraire.h"
#include "haversine.h"
#include "site.h"
#include "gestionItineraire.h"


Lsite *lancerGrasp(Site **tableau, double** distance, int nbsite, float la, float lo, int parametre);
int *siteSuivant(Site **tableau, double **distance, int *sitevisite, Lsite* liste, int nbsite, int parametre, int actuel);
int *meilleursCandidats(Site **tableau, double **distance, int *sitevisiteoriginal, int parametre, int nbsite, int actuel);
int *copieSiteVisite(int *sitevisite, int nbsite);


