#include "constante.h"
#include "controller.h"
#include "render.h"
#include "read_xml.h"
#include "element.h"
#include "main.h"
#include "convert.h"


 /**
	* \param argc Le nombre de paramètre dans notre ligne de commande
	* \param argc Les paramètre de notre ligne de commande
	* \author Fadyl Bello
	* \author Amadou SY
	* \brief lancement du main
	* \fn la fonction prend le nom du fichier en argument pour la lecture XML
	* Si pas d'argument ça prend test3.osm comme argument par défaut
	* lit les fichiers et Initialise nos tableaux de structure
	* Lance l'affichage de notre render
	* \bug OSM_FILE request envoie des valeurs en float bizzare
	* \date Mars 2016
	* \return EXIT_SUCESS quand tout est terminé
	* \version 2.0
	*/
int main(int argc, char *argv[])
{

	char *s;

	/* Si le nom du fichier n'est pas specifier
	* test3.osm par défaut
	* Si trop d'argument on retourne une erreur
	* si 2 arguments on le prend en compte
	*/
	if(argc == 1)
		s = "test3.osm"; 
	else
	{
		if (argc != 2)
		{
			fprintf(stderr, "Veuillez specifier nom du fichier osm valide \n");
			return EXIT_FAILURE;
		}
		else
		{
			s = get_name(argv[1]);
		}
	}
	
	read_size_elmt(s);
	lib_main(s);
	tab_node_sort();
	tab_way_sort_by_order();
	sdl_main();
	close_tabs();
	return EXIT_SUCCESS;
}

/**
 * \param name le nom du fichier a ouvrir
 * \brief lancement du main
 * \fn la fonction prend le nom du fichier en argument pour la lecture XML
 * demande à l'utilisateur de specifier un nom de fichier valide
 * \author Amadou Sy
 * \date Mars 2016
 * \return EXIT_SUCESS quand tout est terminé
 * \version 1.0
 */
char* get_name(char *name)
{
	while(fopen(name, "r") == NULL){
		char *namedotosm = strcat(name, ".osm");
		if(fopen(namedotosm, "r") != NULL)
			return namedotosm;
		fprintf(stderr, "Fichier inexistant !\nOuvrir un nouveau fichier : ");
		scanf("%s", name);
	}
	return name;
}
