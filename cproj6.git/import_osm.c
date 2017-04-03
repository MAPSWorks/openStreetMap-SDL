/**
 * \file import_osm.c
 * \brief Importation de Fichier osm
 * \author Fadyl Bello
 * \version 1.0
 * \date 13 Mars 2016
 *
 * Programme permettant l'importation de fichier osm.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "import_osm.h"
 /**
 	* \param minlon La longitude  minimal
 	* \param minlat La latitude maximal
 	* \param maxlon La longitude minimal
 	* \param maxla La latitude maximal
	* \author Fadyl Bello
	* \brief Obtient la requete en fonction des paramètres
  * \version 1.0
  * \date 13 Mars 2016
	*/
void get_osmfile_request(float mminlon, float mminlat, float mmaxlon, float mmaxlat)
{
	char a[128];
	char b[128];
	char c[128];
	char d[128];
	char command[1024]= "wget -O ";
	char nom[514]=" \"http://api.openstreetmap.org/api/0.6/map?bbox=";
	char separate[3]=",";
	char end[3]="\"";
	char file[256] = "file-";
	char ext[10] = ".osm";
	char buffer[256];
	time_t t = time(NULL);
	printf("Paramètre d'entrée de la fonction get osm file..%f %f %f %f\n", mminlon,mminlat,mmaxlon,mmaxlat); 	
	strftime(buffer, sizeof(buffer), "%d-%m-%Y-%X", localtime(&t));
	strcat(file,((const char*)buffer));
	strcat(file,((const char*)ext));
	sprintf(a, "%f", mminlon);
	sprintf(b, "%f", mminlat);
	sprintf(c, "%f", mmaxlon);
	sprintf(d, "%f", mmaxlat);
  
 
	strcat(command,((const char*)file));
	strcat(command,((const char*)nom));
	strcat(command,((const char*)a));
	strcat(command,((const char*)separate));
	strcat(command,((const char*)b));
	strcat(command,((const char*)separate));
	strcat(command,((const char*)c));
	strcat(command,((const char*)separate));
	strcat(command,((const char*)d));
	strcat(command,((const char*)end));
	printf("%s",command);
	system(command);

}
