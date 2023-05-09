#include "gps.h"


char GPS_LOG[] = "$GPRMC,";
char GPS[80];
char GPS_PROCESSED[12][20];
char * token;
double curlng, curlat, deslng, deslat;
const double R = 6371000;
const double FINAL_lng, FINAL_lat;
double total_distance;
char Longitude[12];
char Latitude[12];


double ToDEGREE(double angle){
    int degree = (int)angle / 100;
    float min = angle - (float)degree*100;
    return(degree + (min/60));
}

double ToRAD(double angle){
    return angle * PI / 180;
}

void GPSread(){
    char UART_char;
    int count = 0;
    int i = 0;


    do{
        while(UART_Read() != GPS_LOG[count])
            count++;
    }while(count != 7);
    
    strcpy(GPS, "");
    UART_char = UART_Read();

    while(UART_char != '*'){
        GPS[i] = UART_char;
        UART_char = UART_Read();
        i++;
    }

    i = 0;
    token = strtok(GPS, ",");

    while (token != NULL) {
        strcpy(GPS_PROCESSED[i], token);
        token = strtok(NULL, ",");        
        i++;
    }

    if (strcmp(GPS_PROCESSED[1], "A") == 0){
        if (strcmp(GPS_PROCESSED[3], "N") == 0){
            curlat = atof(GPS_PROCESSED[2]);
        }
        else{
            curlat = -atof(GPS_PROCESSED[2]);
        }
        if (strcmp(GPS_PROCESSED[5], "E") == 0){
            curlng = atof(GPS_PROCESSED[4]);
        }
        else{   
            curlng = -atof(GPS_PROCESSED[4]);
        }

    }

}

double distance(){
    double currentLatrad = ToRAD(ToDEGREE(curlat)); 
    double destLatrad = ToRAD(ToDEGREE(deslat));
    double longDiff = ToRAD(ToDEGREE(deslng)-ToDEGREE(curlng));
    double latDiff = ToRAD(ToDEGREE(deslat)-ToDEGREE(curlat));
    double a = pow(sin(latDiff/2), 2)+cos(currentLatrad)*cos(destLatrad)*pow(sin(longDiff/2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R*c;
    total_distance += distance; // total distance moved saved in global var
    return distance;
}

