/**
 * \file recherche.c
 * \brief Recherche locale et globale d'un lieu
 * \author Fadyl Bello
 * \version 1.0
 * \date 13 Mars 2016
 */

#include <time.h>
#include <libxml/xpath.h>
#include <libxml/parser.h>
#include "constante.h"
#include "recherche.h"


/**
	* \param s nom du fichier
	* \author Fadyl Bello
	* \brief Obtient la requete en fonction des paramètres
	* \version 1.0
	* \desc on vérifie que le fichier est bien là
	* on regarde dans l'élement place la référence de boundigbox et on la renvoie
	* \date 13 Mars 2016
*/
void get_bounds( char *s, SDL_Surface *window,TTF_Font *font,SDL_Rect position)
{
	xmlDocPtr doc;
    xmlNodePtr racine,node;
    char* recherche="boundingbox";
	SDL_Color whiteColor;
	const char* bounds;
	char result[128]="le lieu chercher est : ";
	int result_fine=0;
	whiteColor.r =255;
	whiteColor.g =255;
	whiteColor.b =255;
    doc = xmlParseFile(s);
    SDL_BlitSurface(TTF_RenderUTF8_Blended(font,result, whiteColor),NULL,window,&position);
    position.y = position.y+20;
    if (doc == NULL)
    {
    	fprintf(stderr, "Document XML invalide\n");
    	exit(EXIT_FAILURE);
    }
    
    racine = xmlDocGetRootElement(doc);
    if (racine == NULL)
    {
		 fprintf(stderr, "Document XML vierge\n");
		 exit(EXIT_FAILURE);
	}
		node = racine->xmlChildrenNode;
		while (node != NULL) 
		{
			if(node->type == XML_ELEMENT_NODE)
			{
				if(strcmp((const char*)node->name,(const char*)"place")==0)
				{				
						 printf("%s",xmlGetProp(node,(const xmlChar*)recherche));
						 result_fine=1;
						 bounds = (const char*)xmlGetProp(node,(const xmlChar*)recherche);
						 SDL_BlitSurface(TTF_RenderUTF8_Blended(font,bounds, whiteColor),NULL,window,&position);
						 					
				}
			}
			node = node->next;
		}
	if(result_fine==0) 
	  SDL_BlitSurface(TTF_RenderUTF8_Blended(font,"Not find....", whiteColor),NULL,window,&position);
		
	
	SDL_Flip(window);	
    xmlFreeDoc(doc); 
  

}
 /**
 	* \param param1 Premier paramètre de recherche
 	* \param param2 Deuxième paramètre de recherche
 	* \param param3 Premier paramètre de recherche
 	* \param param3 Premier paramètre de recherche
	* \author Fadyl Bello
	* \brief Obtient la requete en fonction des paramètres
  * \version 1.0
  * \date 13 Mars 2016
	*/
void get_datasearch_request(char *a, char *b, char *c, char *d, char *e, char *f, SDL_Surface *window,TTF_Font *font,SDL_Rect position)
{
	time_t t = time(NULL);
	char file[256] = "data_place-";
	char ext[10] = ".osm";
	char buffer[256];
	char commande[1024]="wget -O ";
	char nom[514]=" \"http://nominatim.openstreetmap.org/search?q=";
	char nom2[514]="&format=xml&polygon=1&addressdetails=1\"";
	char separate[3]="+";
	
 	strftime(buffer, sizeof(buffer), "%d-%m-%Y-%X", localtime(&t));
	strcat(file,((const char*)buffer));
	strcat(file,((const char*)ext));
  

	strcat(commande,((const char*)file));
	strcat(commande,((const char*)nom));
	if(strcmp(a,"")!=0)
	{
		strcat(commande,((const char*)a));
	}
	if(strcmp(b,"")!=0)
	{
		strcat(commande,((const char*)separate));
		strcat(commande,((const char*)b));
	}
	if(strcmp(c,"")!=0)
	{
		strcat(commande,((const char*)separate));
		strcat(commande,((const char*)c));
	}
	
	if(strcmp(d,"")!=0)
	{
		strcat(commande,((const char*)separate));
		strcat(commande,((const char*)d));
	}
	if(strcmp(e,"")!=0)
	{
		strcat(commande,((const char*)separate));
		strcat(commande,((const char*)e));
	}
	if(strcmp(f,"")!=0)
	{
		strcat(commande,((const char*)separate));
		strcat(commande,((const char*)f));
	}
	
	strcat(commande,((const char*)nom2));
	system(commande);
	get_bounds(file,window,font,position);
}



