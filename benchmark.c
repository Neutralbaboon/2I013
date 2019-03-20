#include <stdio.h>
#include <stdlib.h>
#include "lectureFichiers.h"
#include "site.h"
#include "haversine.h"
#include "procheVoisin.h"
#include "gestionItineraire.h"
#include "benchmark.h"
#include <time.h>




void benchmark(Site **tableau, Lsite *liste,int nbTest,int n){
	for(int i=0;i<nbTest;i++){
	
	
	afficherListeItineraire(tableau,liste);

	afficherPoint(tableau,liste);

	enregistrerItineraire(tableau,liste,rand()*MAX_LAT,rand()*MAX_LONG);
	//ouvrirItineraire();


	libererListeItineraire(liste);
	//libererMatriceDistance(distance,n);
	libererSite(tableau, n);

	}	

}

	
	
	
