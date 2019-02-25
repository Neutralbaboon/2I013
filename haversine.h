#ifndef HAVERSINE_H
#define HAVERSINE_H

#include "site.h"

#define RAYON_TERRE 6371

double toRad(double angleD);
double haversin(double val);
double calculDistance(double nLat1, double nLon1, double nLat2, double nLon2);
double **allouerMatriceDistance(int n);
void libererMatriceDistance(double **mat, int n);
double **calculMatriceDistance(Site ** sites, int taille);

#endif
