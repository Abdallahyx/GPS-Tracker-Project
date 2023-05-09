#ifndef GPS_H_
#define GPS_H_


#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.142857 


double ToDEGREE(double angle);
double ToRAD(double angle);
void GPSread();
double distance();

#endif