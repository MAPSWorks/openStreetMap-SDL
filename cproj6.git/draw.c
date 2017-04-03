/**
 * \file draw.c
 * \brief Dessines les elements de la carte
 * \version 1.0
 * \date  Mars 2016
 *
 */

#include "constante.h"
#include "render.h"
#include "sdl_ext.h"

/**
 * \fn void print_water_area(SDL_Surface *window, short x[], short y[], int taille, char *s)
 * \brief Dessine les zones d'eau
 * \param window La fenetre SDL
 * \param x[]
 * \param y[]
 * \param taille
 * \param s
 * \version 1.0
 */
void print_water_area(SDL_Surface *window, short x[], short y[], int taille, char *s)
{
	int i=0;
	short tmp_x[MAX_SIZE_NODE_IN_WAY],tmp_y[MAX_SIZE_NODE_IN_WAY];

	for(i=0; i<taille;i++)
	{
		tmp_x[i] = CP_HEIGHT_RENDER-x[i+1];
		tmp_y[i] = y[i+1];
	}
	 filledPolygonRGBA(window,tmp_y,tmp_x,taille-1,0,200, 255, 155);
	 printf("%s",s);
}

/**
 * \fn void print_building(SDL_Surface *window, short x[], short y[], int taille, char *s)
 * \brief Dessine les batiments
 * \param window La fenetre SDL
 * \param x[]
 * \param y[]
 * \param taille
 * \param s
 * \version 1.0
 */
void print_building(SDL_Surface *window, short x[], short y[], int taille, char *s)
{
	int i=0;
	short tmp_x[MAX_SIZE_NODE_IN_WAY],tmp_y[MAX_SIZE_NODE_IN_WAY];

	for(i=0; i<taille;i++)
	{
		tmp_x[i] = CP_HEIGHT_RENDER-x[i+1];
		tmp_y[i] = y[i+1];
	}
	 filledPolygonRGBA(window,tmp_y,tmp_x,taille-1,130,90,130, 255);
	 print_road_by_type(window,y,x,taille,s,TYPE_WAY_WALL_BUILDING);
	 printf("%s",s);
}

/**
 * \fn void print_grass_area(SDL_Surface *window, short x[], short y[], int taille, char *s)
 * \brief Dessine les espaces verts
 * \param window La fenetre SDL
 * \param x[]
 * \param y[]
 * \param taille
 * \param s
 * \version 1.0
 */
void print_grass_area(SDL_Surface *window, short x[], short y[], int taille, char *s)
{
	int i=0;
	short tmp_x[MAX_SIZE_NODE_IN_WAY],tmp_y[MAX_SIZE_NODE_IN_WAY];

	for(i=0; i<taille;i++)
	{
		tmp_x[i] = CP_HEIGHT_RENDER-x[i+1];
		tmp_y[i] = y[i+1];
	}
	 filledPolygonRGBA(window,tmp_y,tmp_x,taille-1,0,140, 0, 255);
	 printf("%s",s);
}

/**
 * \fn void print_grey_building(SDL_Surface *window, short x[], short y[], int taille, char *s)
 * \brief Dessine les espaces verts
 * \param window La fenetre SDL
 * \param x[] position lon
 * \param y[] position lat
 * \param taille nombre de noeud
 * \param s nom du uilding
 * \version 1.0
 */
void print_grey_building(SDL_Surface *window, short x[], short y[], int taille, char *s)
{
	int i=0;
	short tmp_x[MAX_SIZE_NODE_IN_WAY],tmp_y[MAX_SIZE_NODE_IN_WAY];

	for(i=0; i<taille;i++)
	{
		tmp_x[i] = CP_HEIGHT_RENDER-x[i+1];
		tmp_y[i] = y[i+1];
	}
	 filledPolygonRGBA(window,tmp_y,tmp_x,taille-1,10,10, 10, 155);
	 print_road_by_type(window,y,x,taille,s,TYPE_WAY_BUILDING_AREA);
	 printf("%s",s);
}

/**
 * \fn void print_grey_building(SDL_Surface *window, short x[], short y[], int taille, char *s)
 * \brief Dessine les espaces verts
 * \param window La fenetre SDL
 * \param x[] position lon
 * \param y[] position lat
 * \param taille nombre de noeud
 * \param s nom du uilding
 * \version 1.0
 */
void print_brown_area(SDL_Surface *window, short x[], short y[], int taille, char *s)
{
	int i=0;
	short tmp_x[MAX_SIZE_NODE_IN_WAY],tmp_y[MAX_SIZE_NODE_IN_WAY];

	for(i=0; i<taille;i++)
	{
		tmp_x[i] = CP_HEIGHT_RENDER-x[i+1];
		tmp_y[i] = y[i+1];
	}
	 filledPolygonRGBA(window,tmp_y,tmp_x,taille-1,237,104,59, 195);
	 printf("%s",s);
}

/**
 * \fn void print_road_by_type(SDL_Surface *window, short x[], short y[], int taille, char *s, int type)
 * \brief Dessine les chemins selon leur type
 * \param window La fenetre SDL
 * \param x[]
 * \param y[]
 * \param taille
 * \param s le nom de la way
 * \param type le type de la route
 * \version 1.0
 */
void print_road_by_type(SDL_Surface *window, short x[], short y[], int taille, char *s, int type)
{
  int i,size=5;
  SDL_Rect point1, point2;
  SDL_Color Color;
  if(type == TYPE_WAY_PRIMARY)
  {
  	Color.r = 178;
  	Color.g = 34;
  	Color.b = 34;
  	size=8;
  }

   if(type == TYPE_WAY_RAIL)
  {
  	Color.r = 150;
  	Color.g = 20;
  	Color.b = 20;
  	size=2;
  }
  if(type == TYPE_WAY_TERTIARY)
  {
  	Color.r = 255;
  	Color.g = 200;
  	Color.b = 160;
  	size=8;
  }
  if(type == TYPE_WAY_PEDESTRIAN)
  {
  	Color.r = 155;
  	Color.g = 155;
  	Color.b = 155;
  	size=3;
  }
  if(type == TYPE_WAY_RESIDENTIAL)
  {
  	Color.r = 255;
  	Color.g = 255;
  	Color.b = 255;
  	size=8;
  }

  if(type == TYPE_WAY_UNCLASSIFIED)
  {
  	Color.r = 255;
  	Color.g = 255;
  	Color.b = 255;
  	size=2;
  }

  if(type == TYPE_WAY_WALL)
  {
  	Color.r = 100;
  	Color.g = 100;
  	Color.b = 100;
  	size=2;
  }
  if(type == TYPE_WAY_BOUDARY_ADMIN)
  {
  	Color.r = 150;
  	Color.g = 0;
  	Color.b = 200;
  	size=2;
  }

  if(type == TYPE_WAY_BRIDGE)
  {
  	Color.r = 20;
  	Color.g = 20;
  	Color.b = 20;
  	size=2;
  }
  
  if(type == TYPE_WAY_BUILDING_AREA)
  {
  	Color.r = 20;
  	Color.g = 20;
  	Color.b = 20;
  	size=2;
  }
  if(type == TYPE_WAY_RIVERBANK)
  {
  	Color.r = 90;
  	Color.g = 100;
  	Color.b = 233;
  	size=2;
  }
   if(type == TYPE_WAY_GRASS)
  {
  	Color.r = 90;
  	Color.g = 205;
  	Color.b = 0;
  	size=2;
  }
   if(type == TYPE_WAY_WALL_BUILDING)
  {
  	Color.r = 80;
  	Color.g = 45;
  	Color.b = 80;
  	size=1;
  }
  for(i = 0; i < taille-1; i++)
    {
      point1.x = x[i];
      point1.y = CP_HEIGHT_RENDER-y[i];
      point2.x = x[i+1];
      point2.y = CP_HEIGHT_RENDER-y[i+1];
      drawLine ( window, point1, point2, Color, size);

    }
  printf("%s",s);
}

/**
 * \fn void void print_cycleway(SDL_Surface *window, short x[], short y[], int taille)
 * \brief Dessine les pistes cyclables
 * \param window La fenetre SDL
 * \param x[]
 * \param y[]
 * \param taille
 * \version 1.0
 */
void print_cycleway(SDL_Surface *window, short x[], short y[], int taille)
{
  int i;
  SDL_Rect point1, point2;
  SDL_Color Color2;
  Color2.r = 90;
  Color2.g = 100;
  Color2.b = 233;
  for(i = 0; i < taille-1; i++)
    {
      point1.x = x[i];
      point1.y = CP_HEIGHT_RENDER-y[i];
      point2.x = x[i+1];
      point2.y = CP_HEIGHT_RENDER-y[i+1];
      drawLine ( window, point1, point2, Color2, 2);
    }
}

/**
 * \fn void print_image_render(int type, int x, int y,SDL_Surface *window)
 * \brief Affiche les images
 * \param window La fenetre SDL
 * \param x abscisse
 * \param y ordonnee
 * \param type le type de l image
 * \version 1.0
 */
void print_image_render(int type, int x, int y,SDL_Surface *window)
{
	SDL_Rect pos;
	pos.x=x;
	pos.y=CP_HEIGHT_RENDER-y;
	pos.h=16;
	pos.w=16;
	SDL_BlitSurface(image_render[type],NULL, window, &pos);
}

/**
 * \param window La surface où l'on imprime l'element
 * \param x les positions de latitude
 * \param y les positions de longitude
 * \param taille le nombre de point à placer
 * \param name le nom de l'élement(ex :Rue Pilkington)
 * \param type, le type d'élement à imprimer
 * \author Fadyl Bello & Amadou Sy
 * \brief Affiche elements selon leur type
 * \version 1.0
 */
void print_element(SDL_Surface *window, short x[], short y[], int taille, char *name, int type)
{
	if(type == TYPE_WAY_RESIDENTIAL)	print_road_by_type(window,y,x,taille,name,TYPE_WAY_RESIDENTIAL);
	if(type == TYPE_WAY_CYCLEWAY)	print_cycleway(window,y,x,taille);
	if(type == TYPE_WAY_TERTIARY)	print_road_by_type(window,y,x,taille,name,TYPE_WAY_TERTIARY);
	if(type == TYPE_WAY_PEDESTRIAN)	print_road_by_type(window,y,x,taille,name,TYPE_WAY_PEDESTRIAN);
	if(type == TYPE_WAY_PRIMARY)	print_road_by_type(window,y,x,taille,name,TYPE_WAY_PRIMARY);
	if(type == TYPE_WAY_UNCLASSIFIED)	print_road_by_type(window,y,x,taille,name,TYPE_WAY_UNCLASSIFIED);
	if(type == TYPE_WAY_FOOTWAY)	print_road_by_type(window,y,x,taille,name,TYPE_WAY_PEDESTRIAN);
	if(type == TYPE_WAY_WALL)	print_road_by_type(window,y,x,taille,name,TYPE_WAY_WALL);
	if(type == TYPE_WAY_RAIL)	print_road_by_type(window,y,x,taille,name,TYPE_WAY_RAIL);
	if(type == TYPE_WAY_BOUDARY_ADMIN)	print_road_by_type(window,y,x,taille,name,TYPE_WAY_BOUDARY_ADMIN);
	if(type == TYPE_WAY_BRIDGE)	print_road_by_type(window,y,x,taille,name,TYPE_WAY_BRIDGE);
	if(type == TYPE_WAY_COAST)	print_road_by_type(window,y,x,taille,name,TYPE_WAY_RIVERBANK);
	if(type == TYPE_WAY_RIVERBANK)	print_water_area(window,x,y,taille,name);
	if(type == TYPE_WAY_NATURALWATER)	print_water_area(window,x,y,taille,name);
	if(type == TYPE_WAY_BUILDING)	print_building(window,x,y,taille,name);
	if(type == TYPE_WAY_GRASS) print_grass_area(window,x,y,taille,name);
	if(type == TYPE_WAY_BUILDING_AREA)  print_building(window,x,y,taille,name);
	if(type == TYPE_WAY_CONSTRUCTION) print_brown_area(window,x,y,taille,name);
}

/**
 * \param window La surface où l'on imprime l'element
 * \param x les positions de latitude
 * \param y les positions de longitude
 * \param taille le nombre de point à placer
 * \param name le nom de l'élement(ex :Rue Pilkington)
 * \author Amadou Sy
 * \brief Affiche Inner
 * \version 1.0
 */
void print_inner(SDL_Surface *window, short x[], short y[],int taille)
{
	int i=0;
	short tmp_x[MAX_SIZE_NODE_IN_WAY],tmp_y[MAX_SIZE_NODE_IN_WAY];

	for(i=0; i<taille;i++)
	{
		tmp_x[i] = CP_HEIGHT_RENDER-x[i+1];
		tmp_y[i] = y[i+1];
	}
	 filledPolygonRGBA(window,tmp_y,tmp_x,taille-1,80,80,80, 255);
}
