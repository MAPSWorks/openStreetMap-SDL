#include <stdio.h>
#include <string.h>
#include "constante.h"
#include "element.h"
#include "controller.h"
#include "focus.h"
#include "draw.h"


 /**
 	* \param window la surface sur laquelle on affichera le render
	* \author Fadyl Bello
	* \brief parcours notre tableau de Way et les affiche un à un sur le render
	* \todo séparer la fonction avec des sous-fonctions
	* \bug la lecture des tag des noeuds ne marchent pas
	* \date Février 2016
	* \version 1.0
	*/
void init_manager_way(SDL_Surface *window)
{
	int nb_way, nb_node,nb_tag,size_tab_node;
	char *name="";
	int type;
	const char* key;
	const char* value;
	short *x;
	short *y;
	
	
	for(nb_way =0; nb_way < size_tab_way+1;nb_way++)
	{
		size_tab_node=0;
		x=calloc (MAX_SIZE_NODE_IN_WAY, sizeof (int));
		y=calloc (MAX_SIZE_NODE_IN_WAY, sizeof (int));
		if(x==NULL || y == NULL) printf("failed calloc");
		type=0;
		for(nb_tag =0; nb_tag < MAX_SIZE_TAG ;nb_tag++)
		{
			 key = (const char *)tab_way[nb_way].list_tag[nb_tag].k;
			 value = (const char *)tab_way[nb_way].list_tag[nb_tag].v;


				if(tab_way[nb_way].list_tag[nb_tag].k == NULL) break;/** Si plus de tag on sort*/
				if(tab_way[nb_way].list_tag[nb_tag].k != NULL){;/** Si plus de tag on sort*/

					if(get_tag_type((char *)key,(char *)value) != 0 )
						type = get_tag_type((char *)key,(char *)value);
					

					/**On sauvegarde le nom s'il existe*/
					if(strcmp(key,(const char *)"name") == 0)
					{
		 				/**name = strcpy((char *)name,(const char *)tab_way[nb_way].list_tag[nb_tag].v);*/
					}
				/**printf("K : %s, V : %s \t", tab_way[nb_way].list_tag[nb_tag].k, tab_way[nb_way].list_tag[nb_tag].v);*/
			}
			
			
		}

		for(nb_node =0; nb_node < MAX_SIZE_NODE_IN_WAY ;nb_node++)
		{
			if(tab_way[nb_way].list_node[nb_node] != 0)
			{
				int pos_node = search_node_i(tab_way[nb_way].list_node[nb_node]);
					size_tab_node++;
					if(lat_in_bounds(tab_node[pos_node].lat))
						x[nb_node] = convert_lat_to_pixel(tab_node[pos_node].lat);
					if(lon_in_bounds(tab_node[pos_node].lon))
						y[nb_node] = convert_lon_to_pixel(tab_node[pos_node].lon);

					/**printf("Noeud %d : pixel(%d,%d) lat(%f,%f) pos(%d)\n", nb_node, x[nb_node],y[nb_node],tab_node[pos_node].lat,tab_node[pos_node].lon,pos_node);*/

			}
			else
			{
				break;
			}
		}
		 if(type == 0)
		 {
				for(nb_tag =0; nb_tag < MAX_SIZE_TAG ;nb_tag++)
				{
					 key = (const char *)tab_way[nb_way].list_tag[nb_tag].k;
					 value = (const char *)tab_way[nb_way].list_tag[nb_tag].v;


						if(tab_way[nb_way].list_tag[nb_tag].k == NULL) break;/** Si plus de tag on sort*/
						if(tab_way[nb_way].list_tag[nb_tag].k != NULL){;/** Si plus de tag on sort*/

							if(get_tag_type((char *)key,(char *)value) != 0 )
								type = get_tag_type((char *)key,(char *)value);
					

							
						printf("K : %s, V : %s \n", tab_way[nb_way].list_tag[nb_tag].k, tab_way[nb_way].list_tag[nb_tag].v);
					}
			
			
		}
		 }
		
		if(type==0)
		printf("\n\t\t\tnb way :%d :type way : %d,id_way:%d \n", nb_way,type,tab_way[nb_way].id);
		print_element(window,x,y,size_tab_node,name,type);
		free(x);
		free(y);
		x=NULL;
		y=NULL;
	}
}

 /**
 	* \param key Numéro de clé d'un Tag
 	* \param value Valeur de la clé
	* \author Fadyl Bello & Amadou Sy
	* \brief récupére le type d'un tag
	* \date Mars 2016
	* \version 1.0
	*/
	
int get_tag_type(char* key, char* value)
{
		if(strcmp(key,"highway") == 0)
		{
			if(strcmp(value,"residential") ==0) return TYPE_WAY_RESIDENTIAL;
			if(strcmp(value,"cycleway") ==0) return TYPE_WAY_CYCLEWAY;
			if(strcmp(value,"tertiary") ==0 || strcmp(value,"secondary") ==0 ) return TYPE_WAY_TERTIARY;
			if(strcmp(value,"primary") ==0) return TYPE_WAY_PRIMARY;
			if(strcmp(value,"pedestrian") ==0)
				return TYPE_WAY_PEDESTRIAN;
			if(strcmp(value,"footway") ==0)
				return TYPE_WAY_FOOTWAY;
			if(strcmp(value,"unclassified") ==0)
				return TYPE_WAY_UNCLASSIFIED;
			if(strcmp(value,"service") ==0)
				return TYPE_WAY_UNCLASSIFIED;
			if(strcmp(value,(const char*)"motorway") ==0) return TYPE_WAY_UNCLASSIFIED;
			if(strcmp(value,(const char*)"trunk") ==0) return TYPE_WAY_UNCLASSIFIED;
			if(strcmp(value,(const char*)"trak") ==0) return TYPE_WAY_UNCLASSIFIED;
		}
		
		
		if(strcmp(key,"building") == 0)
		{
			if(strcmp(value,"yes") ==0)
				return TYPE_WAY_BUILDING;
			if(strcmp(value,"church") ==0)
				return TYPE_WAY_BUILDING_AREA;

		}
		if(strcmp(key,"area") == 0)return TYPE_WAY_BUILDING_AREA;
		if(strcmp(key,"amenity") == 0)
			if(strcmp(value,"source") == 0)
				return TYPE_WAY_BUILDING_AREA;
		if(strcmp(key,"barrier") == 0)
		{
			if(strcmp(value,"wall") ==0 || strcmp(value,"fence") ==0)
				return TYPE_WAY_WALL;

		}
		if(strcmp(key,"landuse") == 0)
		{
			if(strcmp(value,"grass") ==0) return TYPE_WAY_GRASS;
			if(strcmp(value,"forest") ==0) return TYPE_WAY_GRASS;
			if(strcmp(value,"construction") ==0) return TYPE_WAY_CONSTRUCTION;
		}
		if(strcmp(key,"leisure") == 0)
		{
			if(strcmp(value,"park") ==0) return TYPE_WAY_GRASS;
		}

		if(strcmp(key,"railway") == 0)
		{
			if(strcmp(value,"rail") ==0) return TYPE_WAY_RAIL;
			if(strcmp(value,"subway") ==0) return TYPE_WAY_RAIL;
		}
		if(strcmp(key,"boundary") == 0)
		{
			if(strcmp(value,"administrative") ==0) return TYPE_WAY_BOUDARY_ADMIN;
		}
		if(strcmp(key,"bridge") == 0)
		{
			if(strcmp(value,"yes") ==0) return TYPE_WAY_BRIDGE;
		}
		if(strcmp(key,"waterway") == 0)
		{
			if(strcmp(value,"riverbank") ==0) return TYPE_WAY_RIVERBANK;
		}

		if(strcmp(key,"natural") == 0)
		{
			if(strcmp(value,"water") ==0) return TYPE_WAY_NATURALWATER;
			if(strcmp(value,"coastline") ==0) return TYPE_WAY_COAST;
		}

		return 0;
}


 /**
 	* \param window la surface sur laquelle on affichera le render
	* \author Fadyl Bello
	* \brief On imprimera au niveau des Nodes les tags(restaurants, café, hotel...)
	* \bug Impression des images
	* \date 11 Mars 2016
	* \version 1.0
	*/
void init_manager_node(SDL_Surface *window)
{
	int nb_node,i;
	for(nb_node =0; nb_node < size_tab_node; nb_node++)
	{
					 short x = convert_lat_to_pixel(tab_node[nb_node].lat);
					 short y = convert_lon_to_pixel(tab_node[nb_node].lon);

					 for(i=0;i< MAX_SIZE_TAG;i++)
					 {
					 		if(tab_node[nb_node].list_tag[i].k != NULL)
					 		{
					 			if(strcmp((const char *)tab_node[nb_node].list_tag[i].k,"phone") ==0)
										print_image_render(IMG_TEL,y,x,window);
								if(strcmp((const char *)tab_node[nb_node].list_tag[i].k,"tourism") ==0)
										print_image_render(IMG_MUSEE,y,x,window);
								if(strcmp((const char *)tab_node[nb_node].list_tag[i].k,"highway") ==0)
									if(strcmp((const char *)tab_node[nb_node].list_tag[i].k,"traffic_signals") ==0)
											print_image_render(IMG_TRAFFIC,y,x,window);

						 		if(strcmp((const char *)tab_node[nb_node].list_tag[i].k,"amenity") == 0)
								{
									if(strcmp((const char *)tab_node[nb_node].list_tag[i].v,"cafe") ==0)
										print_image_render(IMG_COFFEE,y,x,window);
									if(strcmp((const char *)tab_node[nb_node].list_tag[i].v,"bar") ==0)
										print_image_render(IMG_COFFEE,y,x,window);
									if(strcmp((const char *)tab_node[nb_node].list_tag[i].v,"theatre") ==0)
										print_image_render(IMG_MUSEE,y,x,window);
									if(strcmp((const char *)tab_node[nb_node].list_tag[i].v,"restaurant") ==0)
										print_image_render(IMG_RESTAURANT,y,x,window);
									if(strcmp((const char *)tab_node[nb_node].list_tag[i].v,"bar") ==0)
										print_image_render(IMG_COFFEE,y,x,window);



								}
							}
					 }
		 }
}

/**
	* \param window la surface sur laquelle on affichera le render
	* \author Fadyl Bello
	* \brief On imprimera les relations inner par dessus le render original
	* \todo initialiser les way contenant un inner avec un champs Inner à 1
	* \date 11 Mars 2016
	* \version 1.0
*/
void init_manager_relation(SDL_Surface *window)
{
	int pos_relation,pos_member;
	int nb_way,nb_node;
	int size_tab_node;
	short *x;
	short *y;
	tab_way_sort_by_id();
	
	for(pos_relation =0; pos_relation < size_tab_relation; pos_relation++)
	{
		x=calloc (MAX_SIZE_NODE_IN_WAY, sizeof (int));
		y=calloc (MAX_SIZE_NODE_IN_WAY, sizeof (int));
		if(x==NULL || y == NULL) printf("failed calloc");
		
		if((const char *)tab_relation[pos_relation].list_member[0].type == NULL) break;
		
			for(pos_member=0;pos_member< MAX_SIZE_MEMBER;pos_member++)
			{
				if((const char *)tab_relation[pos_relation].list_member[pos_member].type == NULL) break;
		 		if(strcmp((const char *)tab_relation[pos_relation].list_member[pos_member].type,"") == 0) break;
		 		if(strcmp((const char *)tab_relation[pos_relation].list_member[pos_member].type,(const char *)"way") == 0)
				{
						
					if(strcmp((const char *)tab_relation[pos_relation].list_member[pos_member].role,(const char *)"inner") == 0)
					{
							nb_way = search_way_i(tab_relation[pos_relation].list_member[pos_member].ref);
							size_tab_node=0;
							for(nb_node =0; nb_node < MAX_SIZE_NODE_IN_WAY ;nb_node++)
							{
								if(tab_way[nb_way].list_node[nb_node] != 0)
								{
									int pos_node = search_node_i(tab_way[nb_way].list_node[nb_node]);
									size_tab_node++;
									x[nb_node] = convert_lat_to_pixel(tab_node[pos_node].lat);
									y[nb_node] = convert_lon_to_pixel(tab_node[pos_node].lon);
								}
								else
								{
									break;
								}
							}
							
							print_inner(window,x,y,size_tab_node);
					}
				}
			 }
	}
}

