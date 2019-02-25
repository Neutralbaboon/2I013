#include <math.h>
#include <stdlib.h>
#include "haversine.h"

double toRad(double angleD){
	return (angleD * M_PI / 180.0);
}

double haversin(double val){
	return pow(sin(val / 2), 2);
}

double calculDistance(double nLat1, double nLon1, double nLat2, double nLon2){
	double dLat  = toRad(nLat2 - nLat1);
	double dLong = toRad(nLon2 - nLon1);
	double startLat = toRad(nLat1);
	double endLat = toRad(nLat2);
	double a = haversin(dLat) + cos(startLat) * cos(endLat) * haversin(dLong);
	double c = 2 * atan2(sqrt(a),sqrt(1 - a));
	return RAYON_TERRE * c; 
}

double **allouerMatriceDistance(int n){
	double **retour = (double **) malloc(sizeof(double*)*n);
	int k;
	for(k=0;k<n;k++){
		retour[k]=(double*)malloc(sizeof(double)*n);
	}

	return retour;
}

void libererMatriceDistance(double **mat, int n){
	int k;
	for(k=0;k<n;k++){
		free(mat[k]);
	}
	free(mat);
}

double **calculMatriceDistance(Site **sites, int taille){
	double **mat_distance= allouerMatriceDistance(taille);
	for(int i=0;i<taille;i++){
		for(int j=0;j<i+1;j++){
			if(i==j){
				mat_distance[i][j]=0; // coefficients diagonaux nuls
			}
			else{
				mat_distance[i][j]=calculDistance(sites[i]->la,sites[i]->lo,sites[j]->la,sites[j]->lo);
				mat_distance[j][i]=mat_distance[i][j]; // La matrice est symétrique

			}
		}
	}
	return mat_distance;
}




