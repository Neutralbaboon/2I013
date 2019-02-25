#include "PlusProcheVoisin.h"


Site **PlusProcheVoisin(Site **site){
	Site **file = LectureCSV(fichier);
	Site **save =NULL;
	
	double distance;
	
	double tabPlusProche[];
	Site tabSitePlusProche[];
	int indiceTab=0;
	
	
	int nbSite;
	
	//Pour le site en argument
	
		//recherche des sites les plus proches
		for(int j=0;j<nbSite;j++){
			//ne pas prendre le même site
			if(site->nom != file[j]->nom){
				distance = calculDistance(site->la,site->lo,file[j]->la,file[j]->lo);
				//Si tabPlusProche était vide jusqu'à présent
				if(indiceTab==0){
					tabPlusProche[0]=distance;
					indiceTab++;
				}
				//Si le tableau est déja rempli, on parcours le tableau des sites proches pour trouver sa place dinsertion
				else{
					for(int k=0;k<indiceTab;k++){
						if(distance<tabPlusProche[k]){
							tabPlusProche[k]=distance;
						
				
				
				
				
