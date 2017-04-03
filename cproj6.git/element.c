#include <stdio.h>
#include <string.h>
#include "constante.h"
#include "element.h"
#include "convert.h"

/**
	* \param nb_node Le nombre de node dans le fichier XML
	* \param nb_way Le nombre de ways dans le fichier XML
	* \author Fadyl Bello
	* \brief Déclaration de nos tableaux de way/node
	* \fn la fonction prend les tailles des Node/Way
	* Elle initialise les Var Globales des tailles des tableaux de structure
	* Elle iniitialise les tableaux de structure
	* \date Février 2016
	* \version 1.0
*/
void init_tabs(int nb_node, int nb_way, int nb_relation)
{
	size_tab_node =nb_node;
	size_tab_way =nb_way;
	size_tab_relation = nb_relation;
	tab_node = calloc (size_tab_node+1, sizeof (Node));
	tab_way = calloc (size_tab_way+1, sizeof (Way));
	tab_relation = calloc (size_tab_relation+1, sizeof (Relation));
}

/**
	* \author Fadyl Bello
	* \brief suppression des tableaux alloues
	* \todo utilisation des free pour libérer la mémoire
	* \date Février 2016
	* \version 1.0
*/
void close_tabs()
{
	free(tab_relation);
	free(tab_way);
	free(tab_node);
	tab_node= NULL;
	tab_way=NULL;
	tab_relation=NULL;
}

/**
	* \param id l'identifiant du Node
	* \param lat La lattitude du Node
	* \param lon La longitude du Node
	* \param pos La position dans le tableau de node
	* \author Fadyl Bello
	* \brief Initialise le node avec \a id, \a lat, \a lon à position \a pos
	* \date Février 2016
	* \version 1.0
*/
void add_node(int id, double lat, double lon, int pos)
{
  	tab_node[pos].id=id;
	 tab_node[pos].lat=lat;
	 tab_node[pos].lon=lon;
}

/**
	* \param id l'identifiant de la Way
	* \param pos La position dans le tableau de la Way
	* \author Fadyl Bello
	* \brief Initialise la Way avec \a id, à position \a pos
	* \date Février 2016
	* \version 1.0
*/
void add_way(int id, int pos)
{
   tab_way[pos].id=id;
}


/**
	* \param id l'identifiant de la Relation
	* \param pos La position dans le tableau de Relation
	* \author Fadyl Bello
	* \brief Initialise la Relation avec \a id, à position \a pos
	* \date 11 Mars 2016
	* \version 1.0
*/
void add_relation(int id, int pos)
{
   tab_relation[pos].id=id;
}

/**
	* \param a La latitude maximal
	* \param b La longitude maximal
	* \param c La latitude minimal
	* \param d La longitude minimal
	* \author Fadyl Bello
	* \brief Initialise la bounds avec \a a, \a b, \a c, \a d
	* \details La fonction initialise 2 fois les extremités en lat/lon pour la gestion du Zoom
	* \date Février 2016
	* \version 1.0
*/
void add_bounds(double a, double b, double c, double d)
{
     mbounds.maxlat=a;
	 mbounds.maxlon=b;
	 mbounds.minlat=c;
	 mbounds.minlon=d;
	 mbounds.true_maxlat=a;
	 mbounds.true_maxlon=b;
	 mbounds.true_minlat=c;
	 mbounds.true_minlon=d;

	mbounds.center_y = fabs((mbounds.maxlat - mbounds.minlat)/2.0) + mbounds.minlat;
	mbounds.center_x = fabs((mbounds.maxlon - mbounds.minlon)/2.0) + mbounds.minlon;
	mbounds.rayon_y = fabs((mbounds.maxlat - mbounds.minlat)/2.0);
	mbounds.rayon_x = fabs((mbounds.maxlon - mbounds.minlon)/2.0);


	printf("lat(%f|%f) \n lon(%f|%f) \n truelat(%f | %f) \n truelon(%f | %f) \n center x; %f \n center y; %f\n\n",mbounds.minlat, mbounds.maxlat, mbounds.minlon, mbounds.maxlon,mbounds.true_minlat, mbounds.true_maxlat, mbounds.true_minlon, mbounds.true_maxlon,mbounds.center_x,mbounds.center_y);


	if(fabs(mbounds.center_y+CP_RAYON_Y) > fabs(mbounds.maxlat))
	{
		/**
		*Si le rayon que l'on veut afficher est plus grand que la latitude on réduit
		if(mbounds.true_maxlat<0) mbounds.true_maxlat = mbounds.center_y-CP_RAYON_Y;
		 else mbounds.true_maxlat = mbounds.center_y+CP_RAYON_Y;
		if(mbounds.true_minlat<0)  mbounds.true_minlat= mbounds.center_y+CP_RAYON_Y;
		 else mbounds.center_y-CP_RAYON_Y;*/
	}
	printf("%f %f\n",fabs(mbounds.center_y+CP_RAYON_Y),fabs(mbounds.maxlat));

	if(fabs(mbounds.center_x+CP_RAYON_X) > fabs(mbounds.maxlon))
	{
		/**if(mbounds.true_maxlon<0) mbounds.true_maxlon = mbounds.center_x-CP_RAYON_X;
		 else mbounds.true_maxlon = mbounds.center_x+CP_RAYON_X;
		if(mbounds.true_maxlon<0)mbounds.true_maxlon = mbounds.center_x+CP_RAYON_X;
		 else mbounds.true_maxlon = mbounds.center_x-CP_RAYON_X;*/
	}
	printf("%f %f\n",fabs(mbounds.center_x+CP_RAYON_X), fabs(mbounds.maxlon));

	printf("\nlat(%f|%f) \n lon(%f|%f) \n truelat(%f | %f) \n truelon(%f | %f) \n center x; %f \n center y; %f\n\n",mbounds.minlat, mbounds.maxlat, mbounds.minlon, mbounds.maxlon,mbounds.true_minlat, mbounds.true_maxlat, mbounds.true_minlon, mbounds.true_maxlon,mbounds.center_x,mbounds.center_y);

}

/**
	* \param k la clé(Key) du Tag
	* \param v la valeur(Value) du Tag
	* \param pos_node La position du Node contenant le tag
	* \param pos_tag La position du tag dans le tableau de tag
	* \author Fadyl Bello
	* \brief Ajoute un Tag dans le tableau de tag de la structure Node
	* \date Février 2016
	* \version 1.0
*/
void add_tag_in_node(char *k, char *v, int pos_node, int pos_tag)
{
	tab_node[pos_node].list_tag[pos_tag].k = k;
	tab_node[pos_node].list_tag[pos_tag].v = v;
	/**printf("Affiche tag: %s %s\n",tab_node[pos_node].list_tag[pos_tag].k,tab_node[pos_node].list_tag[pos_tag].v);*/
}

void add_one_member(char *type, int ref, char *role, int pos_relation, int pos_member)
{
	tab_relation[pos_relation].list_member[pos_member].type = type;
	tab_relation[pos_relation].list_member[pos_member].ref = ref;
	tab_relation[pos_relation].list_member[pos_member].role = role;
}

void add_tag_in_relation(char *k, char *v, int pos_relation, int pos_tag)
{
	tab_relation[pos_relation].list_tag[pos_tag].k = k;
	tab_relation[pos_relation].list_tag[pos_tag].v = v;
}

/**
	* \param k la clé(Key) du Tag
	* \param v la valeur(Value) du Tag
	* \param pos_way La position de la Way contenant le tag
	* \param pos_tag La position du tag dans le tableau de tag
	* \author Fadyl Bello
	* \brief Ajoute un Tag dans le tableau de tag de la structure Way
	* \date Février 2016
	* \version 1.0
*/
void add_tag_in_way(char *k, char *v, int pos_way, int pos_tag)
{
	tab_way[pos_way].list_tag[pos_tag].k = k;
	tab_way[pos_way].list_tag[pos_tag].v = v;
}

/**
	* \param idnode un identifiant du noeud composant la way
	* \param pos_way La position du Way
	* \param pos_node La position dans le tableau de node de la structure Way
	* \author Fadyl Bello
	* \brief Ajoute un identifiant de Node dans le tableau de Node de la structure Way
	* \date Février 2016
	* \version 1.0
*/
void add_one_idnode_in_way(int idnode, int pos_way, int pos_node)
{
	tab_way[pos_way].list_node[pos_node] = idnode;
}

/**
	* \param a La lattitude à convertir en pixel
	* \return la position de la latitude sur notre render
	* \author Fadyl Bello
	* \brief convertion de la latitude en pixel
	* \details convertie la distance en lattitude(latitude minimal(bounds),lattitude Node)
	* en pixel grâce à un rapport ingénieux.
	* \date Février 2016
	* \version 1.0
*/
int convert_lat_to_pixel(double a)
{
	double lat_min_map =mbounds.true_minlat;
	double lat_max_map =mbounds.true_maxlat;
	double lat_node = a;

	double dist_min_to_node = (lat_node - lat_min_map);
	double dist_min_to_max = (lat_max_map - lat_min_map);
	double percent = dist_min_to_node/dist_min_to_max;
	return CP_HEIGHT_RENDER*percent;
	

}

/**
	* \param a La longitude à convertir en pixel
	* \return la position de la longitude sur notre render
	* \author Fadyl Bello
	* \brief convertion de la longitude en pixel
	* \details convertie la distance en longitude(longitude minimal(bounds),longitude Node)
	* en pixel grâce à un rapport ingénieux.
	* \date Février 2016
	* \version 1.0
*/
int convert_lon_to_pixel(double a)
{
	double lon_min_map = mbounds.true_minlon;
	double lon_max_map = mbounds.true_maxlon;
	double lon_node = a;

	double dist_min_to_node = (lon_node - lon_min_map)*DIST_ONE_DEGREE;
	double dist_min_to_max = (lon_max_map - lon_min_map)*DIST_ONE_DEGREE;
	double percent = dist_min_to_node/dist_min_to_max;

	return CP_WIDTH_RENDER*percent;

}

/**
	* \param a le premier node à comparer
	* \param b le deuxième node à comparer
	* \return Un int \e n qui vaut 0 a=b, est positif si a>b, -1 sinon
	* \author Fadyl Bello
	* \brief comparaison de Node
	* \date Février 2016
	* \version 1.0
*/
int compare_node(const void *a, const void *b)
{
   Node *nodeA = (Node *)a;
   Node *nodeB = (Node *)b;
   return ( nodeA->id - nodeB->id );
}
/**
	* \param a le premier way à comparer
	* \param b le deuxième way à comparer
	* \return Un int \e n qui vaut 0 a=b, est positif si a>b, -1 sinon
	* \author Fadyl Bello
	* \brief comparaison de Way par id
	* \date Février 2016
	* \version 1.0
*/
int compare_way_by_id(const void *a, const void *b)
{
	Way *nodeA = (Way *)a;
	Way *nodeB = (Way *)b;
	return ( nodeA->id - nodeB->id );
}

/**
	* \param a le premier way à comparer
	* \param b le deuxième way à comparer
	* \return Un int \e n qui vaut 0 a=b, est positif si a>b, -1 sinon
	* \author Fadyl Bello
	* \brief comparaison de Way par ordre d'affichage
	* \date Février 2016
	* \version 1.0
*/
int compare_way_by_order(const void *a, const void *b)
{
	Way *nodeA = (Way *)a;
	Way *nodeB = (Way *)b;
	return ( nodeA->order - nodeB->order );
}

/**
	* \author Fadyl Bello
	* \brief qsort() sur le tableau de Node
	* \date Février 2016
	* \version 1.0
*/
void tab_node_sort()
{
	qsort (tab_node,size_tab_node, sizeof(Node), compare_node);
}

/**
	* \author Fadyl Bello
	* \brief qsort() sur le tableau de Way par ordre d'affichage
	* \date Février 2016
	* \version 1.0
*/
void tab_way_sort_by_order()
{
	qsort (tab_way,size_tab_way, sizeof(Way), compare_way_by_order);
}

/**
	* \author Fadyl Bello
	* \brief qsort() sur le tableau de Way par id
	* \date Février 2016
	* \version 1.0
*/
void tab_way_sort_by_id()
{
	qsort (tab_way,size_tab_way, sizeof(Way), compare_way_by_id);
}

/**
	* \param id_node_searching l'identifiant du noeud que l'on cherche
	* \author Fadyl Bello
	* \brief une simple recherche dichotomique sur notre tableau de Node
	* \date Février 2016
	* \version 1.0
*/
int search_node_i(int id_node_searching)
{
	  int first_node_tab;
	  int last_node_tab;
	  int mid_node_tab;
	  int node_find;
	  int pos =0;
      first_node_tab=0;
      last_node_tab=size_tab_node;
      node_find=0;
      
      while((first_node_tab <= last_node_tab)&&(node_find==0))
      {
				
		mid_node_tab=(first_node_tab+last_node_tab)/2;
			if(tab_node[mid_node_tab +1].id==id_node_searching) {node_find=1; pos= mid_node_tab +1; }
  			if(tab_node[mid_node_tab].id==id_node_searching){ node_find=1; pos= mid_node_tab;  }
  			else
			{
			  if(tab_node[mid_node_tab].id>id_node_searching) last_node_tab = mid_node_tab -1;
			  else first_node_tab = mid_node_tab +1;
			}
 	  }
	return pos;
}

/**
	* \param id_way_searching l'identifiant de la way que l'on cherche
	* \author Fadyl Bello
	* \brief une simple recherche dichotomique sur notre tableau de way
	* \date 27 Mars 2016
	* \version 1.0
*/
int search_way_i(int id_way_searching)
{
	  int first_way_tab;
	  int last_way_tab;
	  int mid_way_tab;
	  int way_find;
	  int pos =0;
      first_way_tab=0;
      last_way_tab=size_tab_way;
      way_find=0;
      
      while((first_way_tab <= last_way_tab)&&(way_find==0))
      {
				
		mid_way_tab=(first_way_tab+last_way_tab)/2;
			if(tab_way[mid_way_tab +1].id==id_way_searching) {way_find=1; pos= mid_way_tab +1; }
  			if(tab_way[mid_way_tab].id==id_way_searching){ way_find=1; pos= mid_way_tab;  }
  			else
			{
			  if(tab_way[mid_way_tab].id>id_way_searching) last_way_tab = mid_way_tab -1;
			  else first_way_tab = mid_way_tab +1;
			}
 	  }
	return pos;
}
/**
	* \param pos_way La position de la way
	* \param order l'ordre que l'on veut ajouter
	* \author Fadyl Bello
	* \brief On vérifie si on doit mettre le nouvelle ordre ou pas
	* \date Février 2016
	* \version 1.0
*/
void check_order_way(int pos_way,int order)
{
	if(tab_way[pos_way].order < order) tab_way[pos_way].order=order;
}

