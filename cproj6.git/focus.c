/**
 * \file focus.c
 * \brief Gestion des zooms et deplacements dans la map
 * \version 2.0
 * \date  Mars 2016
 *
 */

#include "constante.h"
#include "render.h"
#include "element.h"
#include "controller.h"
/**
 * \fn moov_up(SDL_Surface *window)
 * \brief Gere le deplacement vers le haut
 * \param window La fenetre SDL
 * \version 1.0
 */
void moov_up(SDL_Surface *window)
{
 /* SDL_Rect position,screen;
 	screen.x=0;
 	screen.y=0;
  if(nb_zoom ==1)// Si on a zoomer alors on peut bouger
 	{
 		//selon le zoom on choisit quelle partie on affiche
		 printf("moov up : %d\n",pos_moov);
 		if(pos_moov == MOOV_DOWN_LEFT)
 		{

  		position.x = 0;
 			position.y = 0;
 		  SDL_BlitSurface(save_zoom[1],&position,window,&screen);
 	 	}

 		if(pos_moov == MOOV_DOWN_RIGHT)
 		{
 			position.x = CP_WIDTH_RENDER/2;
 			position.y = 0;
 		  SDL_BlitSurface(save_zoom[1],&position,window,&screen);
 		}
	}
	background_menu(window);
	text_menu(window);
  SDL_Flip(window);*/
	SDL_Flip(window);
}

/**
 * \fn moov_down(SDL_Surface *window)
 * \brief Gere le deplacement vers le bas
 * \param window La fenetre SDL
 * \version 1.0
 */
void moov_down(SDL_Surface *window)
{
 /*	SDL_Rect position,screen;
 	screen.x=0;
 	screen.y=0;
  if(nb_zoom ==1)// Si on a zoomer alors on peut bouger
 	{
	  printf("moov down : %d\n",pos_moov);
 		if(pos_moov == MOOV_UP_LEFT)
 		{
 			printf("MOOV DOWN LEFT : \n");
 			SDL_Rect area;
			area.x=0;
			area.y = CP_HEIGHT_RENDER/2;
		 	  SDL_BlitSurface(save_zoom[1],NULL,window,&position);
		 	  nb_zoom=1;
		 	  pos_moov = MOOV_DOWN_LEFT;

			background_menu(window);
			text_menu(window);
			SDL_Flip(window);
 	 	}

 		if(pos_moov == MOOV_UP_RIGHT)
 		{
 			position.x = CP_WIDTH_RENDER/2;
 			position.y = CP_HEIGHT_RENDER/2;
 		  SDL_BlitSurface(save_zoom[1],&position,window,&screen);
 		   pos_moov = MOOV_DOWN_RIGHT;
 		}
	}
*/

	SDL_Flip(window);

}

/**
 * \fn moov_right(SDL_Surface *window)
 * \brief Gere le deplacement vers la droite
 * \param window La fenetre SDL
 * \version 1.0
 */
void moov_right(SDL_Surface *window)
{
	SDL_Flip(window);
}

/**
 * \fn moov_left(SDL_Surface *window)
 * \brief Gere le deplacement vers la gauche
 * \param window La fenetre SDL
 * \version 1.0
 */
void moov_left(SDL_Surface *window)
{
	SDL_Flip(window);
}

/**
 * \fn zoom_in(SDL_Surface *window)
 * \brief Effectue zoom avant
 * \param window La fenetre SDL
 * \version 1.0
 */
/*void zoom_in(SDL_Surface *window){

 	if(mbounds.true_maxlat>=0)
		mbounds.true_maxlat = mbounds.center_y-(mbounds.center_y/2.0);
	else mbounds.true_maxlat = mbounds.center_y+(mbounds.center_y/2.0);
	
	if(mbounds.true_minlat>=0)
		mbounds.true_minlat = mbounds.center_y-(mbounds.center_y/2.0);
	else mbounds.true_maxlat = mbounds.center_y+(mbounds.center_y/2.0);
	
	if(mbounds.true_maxlon>=0)
		mbounds.true_maxlon = mbounds.center_x-(mbounds.center_x/2.0);
	else mbounds.true_maxlat = mbounds.center_y+(mbounds.center_y/2.0);
	
	if(mbounds.true_minlon>=0)
		mbounds.true_minlon = mbounds.center_x-(mbounds.center_x/2.0);
	else mbounds.true_maxlat = mbounds.center_y+(mbounds.center_y/2.0);
	printf("zoom in\n");
	printf("lat(%f|%f) \n lon(%f|%f) \n truelat(%f | %f) \n truelon(%f | %f) \n center x; %f \n center y; %f\n\n",mbounds.minlat, mbounds.maxlat, mbounds.minlon, mbounds.maxlon,mbounds.true_minlat, mbounds.true_maxlat, mbounds.true_minlon, mbounds.true_maxlon,mbounds.center_x,mbounds.center_y);
	restart_window(window);
	background_menu(window);
	text_menu(window);
	init_manager_way(window);
	print_image_render(0, 50, 50,window);
  	SDL_Flip(window);

}*/



void zoom_in(SDL_Surface *window)
{
  SDL_Rect position;
  position.x = 0;
  position.y = 0;
  printf("zoom in : %d\n",nb_zoom);
  if(nb_zoom ==0)
 	{
 	  SDL_BlitSurface(save_zoom[1],NULL,window,&position);
 	  nb_zoom=1;
 	  pos_moov = MOOV_UP_LEFT;
	}
	printf("zoom in : %d\n",nb_zoom);
	background_menu(window);
	text_menu(window);
  SDL_Flip(window);
}


/**
 * \fn zoom_out(SDL_Surface *window)
 * \brief Effectue zoom arriere
 * \param window La fenetre SDL
 * \version 1.0
 */
void zoom_out(SDL_Surface *window)
{
  SDL_Rect position;
  position.x = 0;
  position.y = 0;
  printf("zoom out : %d\n",nb_zoom);
  if(nb_zoom ==1)
 	{
 	 SDL_BlitSurface(save_zoom[0],NULL,window,&position);
 	 nb_zoom=0;

	}
	printf("zoom out : %d\n",nb_zoom);
	init_manager_relation(window);
  	init_manager_node(window);
	background_menu(window);
	text_menu(window);
 	SDL_Flip(window);

}

int lat_in_bounds(double lat)
{
	if(lat <0)
	{
		if(lat >= mbounds.true_minlat && lat <= mbounds.true_minlat)
			return TRUE;
	}
	else
	{
		if(lat <= mbounds.true_maxlat && lat >= mbounds.true_minlat)
			return TRUE;
	}
	return TRUE;

}

int lon_in_bounds(double lon)
{
	if(lon <0)
	{
		if(lon >= mbounds.true_minlon && lon <= mbounds.true_maxlon)
			return TRUE;
	}
	else
	{
		if(lon <= mbounds.true_maxlat && lon >= mbounds.true_minlat)
			return TRUE;
	}
	return TRUE;
}
