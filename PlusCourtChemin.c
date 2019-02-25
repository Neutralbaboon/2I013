int GetCatgeorie( site *s){
	if(s->categorie=="Cultural"){
		return 1;
	}
	else{
		return -1;
	}
}

Site ** PlusCourtChemin( Site ** sites , taille,  double ){
		double **mat= matrice(sites, taille);
		int cn=1; // 1 pour les sites culturels et -1 pour les sites naturels
		int  nbSites=0;
		float temps=504;
		float temps_retour_depart;
		int nbPoints=0;
		int nbPays;
		char pays[MAX_PAYS];
		Site ** Itineraire;
		
		
		while( temps>6+temps_départ_site){
			for(int i=0; i<taille;i++){
				if((mat) &&(GetCategories(sites[i]==cn){
					
					cn=-cn;
				}
				if(sites[i]->enDanger){
					nbpoints+=3;
				}
				if(sites[i]->pays!=pays){
					nbPays++;
				}
				nbSites++;
				pays=sites[i]->pays;
				site_actuelle=site[i];
				if(sites[i]->enDanger==0){
					nbPoints+=1;
				}
				temps_retour_depart=80*mat[i][site_actuelle];
		}
	}
	nbPoints+= 2*nbPays; 
		
