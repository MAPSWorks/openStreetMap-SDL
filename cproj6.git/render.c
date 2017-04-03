/**
 * \file render.c
 * \brief Parametre la fenetre SDL
 * \version 2.0
 * \date  Mars 2016
 *
 */


#include "constante.h"
#include "render.h"
#include "controller.h"
#include "draw.h"
#include "focus.h"
#include "entry_user.h"
#include "convert.h"
#include <time.h>


/**
 * \fn void sdl_main(int argc, char *argv[])
 * \brief Fonction principale
 * Lance l'affichage du render
 * \param argc Le nombre de paramÃ¨tres
 * \param argv Les paramÃ¨tres
 * \version 1.0
 */
void sdl_main(){
  SDL_Surface *window = NULL;
  load_image();
  SDL_Init(SDL_INIT_VIDEO);
  TTF_Init();
  SDL_WM_SetIcon(IMG_Load("img/icone.png"), NULL);
  window = SDL_SetVideoMode(CP_WIDTH_RENDER+CP_WIDTH_MENU,(int)proportion(), 32, SDL_HWSURFACE);
  SDL_EnableUNICODE(1);
  init_window(window);
  init_manager_way(window);
  background_menu(window);
  text_menu(window);
  load_zoom(window);
  SDL_Flip(window);
  init_manager_relation(window);
  init_manager_node(window);
  SDL_Flip(window);
  is_running(window);


  SDL_FreeSurface(window); 
  TTF_Quit();
  SDL_Quit();


}

/**
  * \fn void load_image()
  * \brief Associe a chaque image son lien
  * Initialise le dictionnaire d'images
  * \version 1.0
*/
void load_image()
{
	image_render[IMG_COFFEE]= IMG_Load("img/coffee.png");
	image_render[IMG_CHURCH]= IMG_Load("img/cproj_church.png");
	image_render[IMG_MUSEE]= IMG_Load("img/cproj_musée.png");
	image_render[IMG_POSTE]= IMG_Load("img/cproj_poste.png");
	image_render[IMG_RESTAURANT]= IMG_Load("img/cproj_restaurant.png");
	image_render[IMG_TEL]= IMG_Load("img/cproj_tel.png");
	image_render[IMG_TRAFFIC]= IMG_Load("img/cproj_traffic.png");
	image_render[IMG_VELO]= IMG_Load("img/cproj_velo.png");
}

void load_zoom(SDL_Surface *window)
{
	nb_zoom = 0;
	save_zoom[0] = rotozoomSurface(window, 0.0, 1.0, 1);
    save_zoom[1] = rotozoomSurface(window, 0.0, 2.0, 1);
}

/**
  * \fn void init_window(SDL_Surface *window)
  * \brief Initialise la fenetre SDL
  * \param window La fenetre SDL
  * \version 1.0
*/
void init_window(SDL_Surface *window){

  SDL_WM_SetCaption("Cproj 6 - Sy, Bello, Missoum !", NULL);
  SDL_FillRect(window, NULL, SDL_MapRGB(window->format, 125, 125, 125));
}

/**
 * \fn restart_window(SDL_Surface *window)
 * \brief Reinitialise la fenetre SDL
 * \param window La fenetre SDL
 * \version 1.0
 */
void restart_window(SDL_Surface *window){
  SDL_FreeSurface(window);
  init_window(window);
}

/**
 * \fn void text_menu(SDL_Surface *window)
 * \brief Gestion de la fenetre en cours
 * \param window La fenetre SDL
 * \version 1.0
 */
void is_running(SDL_Surface *window){
  int onBreak = 1; /* Booléen permettant de savoir si on est en pause.*/
  SDL_Event event; /* Permet la gestion des évenements.*/
 
  while(onBreak == 1){/* Tant qu'on est en pause*/

    SDL_WaitEvent(&event);/* On attendent un évenement*/
    switch(event.type){
    case SDL_QUIT: /* Si l'évenement est la croix pour quitter*/
      onBreak = 0;
      break;
    case SDL_KEYDOWN:
      switch(event.key.keysym.sym)
			{
			case SDLK_UP: moov_up(window);
				break;
			case SDLK_DOWN: moov_down(window);
				break;
			case SDLK_RIGHT: moov_right(window);
				break;
			case SDLK_LEFT: moov_left(window);
				break;
			case SDLK_i: zoom_in(window);
				break;
			case SDLK_o: zoom_out(window);
				break;
			case SDLK_e:export(window);
				break;
			case SDLK_t:
						background_menu(window);
				    	text_menu(window);
				    	entry_user_download_osm(window);
				break;
			case SDLK_g:
						background_menu(window);
				    	text_menu(window);
				    	entry_user_global_search(window);
				break;
			case SDLK_l:
						background_menu(window);
				    	text_menu(window);
						entry_user_local_search(window);
				break;
			default :
				break;
			}
      break;
    }
  }
}

/**
 * \fn void background_menu(SDL_Surface *window)
 * \brief Arriere plan
 * \param window La fenetre SDL
 * \version 1.0
 */
void background_menu(SDL_Surface *window){
  SDL_Rect position;
  SDL_Surface *lines[255] = {NULL};
  int i = 0;
  for(i =0; i < 255; i = i + 1){
    lines[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,CP_WIDTH_RENDER,4,32,0,0,0,0);
    position.x = CP_WIDTH_RENDER;
    position.y=i*4;
    SDL_FillRect(lines[i], NULL, SDL_MapRGB(window->format, i, i, i));
    SDL_BlitSurface(lines[i], NULL, window, &position); 
  }
}

/**
 * \fn void text_menu(SDL_Surface *window)
 * \brief Parametre le menu latteral
 * \param window La fenetre SDL
 * \version 1.0
 */
void text_menu(SDL_Surface *window)
{
  SDL_Rect position;
  TTF_Font *font_two;
  SDL_Color whiteColor;
  SDL_Surface *text_div_two, *text_div_three, *text_div_four, *text_div_five, *text_div_six, *text_div_seven;
  int space_between_div = 5;
  
  whiteColor.r =255;
  whiteColor.g =255;
  whiteColor.b =255;

  font_two = TTF_OpenFont("LongTime.ttf",10);
  
  text_div_two = TTF_RenderText_Blended(font_two, "Zoom In : i / Zoom Out : o", whiteColor);
  text_div_three = TTF_RenderText_Blended(font_two, "Directional Keys to move", whiteColor);
  text_div_four = TTF_RenderText_Blended(font_two, "Export : e", whiteColor);
  text_div_five = TTF_RenderText_Blended(font_two, "Download OSM : t", whiteColor);
  text_div_six = TTF_RenderText_Blended(font_two, "Global search : g", whiteColor);
  text_div_seven = TTF_RenderText_Blended(font_two, "Local search : l", whiteColor);
  
  position.x = (CP_WIDTH_RENDER+(CP_WIDTH_MENU/2)) - (text_div_two->w /2);
  position.y = space_between_div;
  SDL_BlitSurface(text_div_two,NULL,window,&position);

  position.x = (CP_WIDTH_RENDER+(CP_WIDTH_MENU/2)) - (text_div_three->w /2);
  position.y = space_between_div*2 + text_div_two->h ;
  SDL_BlitSurface(text_div_three,NULL,window,&position);

  position.x = (CP_WIDTH_RENDER+(CP_WIDTH_MENU/2)) - (text_div_four->w /2);
  position.y = space_between_div*3 + text_div_two->h + text_div_three->h ;
  SDL_BlitSurface(text_div_four,NULL,window,&position);
  
  position.x = (CP_WIDTH_RENDER+(CP_WIDTH_MENU/2)) - (text_div_five->w /2);
  position.y = space_between_div*4 + text_div_two->h + text_div_three->h+text_div_four->h ;
  SDL_BlitSurface(text_div_five,NULL,window,&position);  
  
  position.x = (CP_WIDTH_RENDER+(CP_WIDTH_MENU/2)) - (text_div_six->w /2);
  position.y = space_between_div*5 + text_div_two->h + text_div_three->h+text_div_four->h+text_div_five->h ;
  SDL_BlitSurface(text_div_six,NULL,window,&position); 
   
  position.x = (CP_WIDTH_RENDER+(CP_WIDTH_MENU/2)) - (text_div_seven->w /2);
  position.y = space_between_div*6 + text_div_two->h + text_div_three->h+text_div_four->h+text_div_five->h +text_div_six->h  ;
  SDL_BlitSurface(text_div_seven,NULL,window,&position);  

}

SDL_Rect get_pos_line(short x[], short y[], int taille)
{
  int min_x=x[0],max_x =0,i,min_y=y[0],max_y =0;
  SDL_Rect position;
  for(i=0; i < taille; i++)
    {
      if(x[i]> max_x) max_x=x[i];
      if(x[i]< min_x) min_x=x[i];
      if(y[i]> max_y) max_y=y[i];
      if(y[i]< min_y) min_y=y[i];
    }

  position.x = (max_x-min_x)/2;
  position.y = (max_y-min_y)/2;
  return position;

}


/**
 * \fn export(SDL_Surface *window)
 * \brief Export la fenetre en cours dans un fichier .png
 * \param window La fenetre SDL
 * \version 1.0
 */
void export(SDL_Surface *window)
{
	SDL_Surface *export = NULL;
	SDL_Rect p_screen;
	time_t t = time(NULL);
	char file_bmp[256] = "export_render/rendu-";
	char file_png[256] = "export_render/rendu-";
	char buffer[256];
	char extension_bmp[5]=".bmp";
	char extension_png[5]=".png";
	char command[1024] ="convert ";
	char option[28]= " ";
	export =  SDL_CreateRGBSurface(SDL_HWSURFACE,CP_WIDTH_RENDER,CP_HEIGHT_RENDER,32,0,0,0,0);
	
	p_screen.x = 0;
	p_screen.y = 0;
	p_screen.h = CP_HEIGHT_RENDER;
	p_screen.w = CP_WIDTH_RENDER;
	SDL_BlitSurface(window,&p_screen, export, NULL);

  
	strftime(buffer, sizeof(buffer), "%d-%m-%Y-%X", localtime(&t));
	strcat(file_bmp,((const char*)buffer));
	strcat(file_png,((const char*)buffer));
	strcat(file_bmp,((const char*)extension_bmp));
	strcat(file_png,((const char*)extension_png));
	SDL_SaveBMP(export,file_bmp);
	
	strcat(command,((const char*)file_bmp));
	strcat(command,((const char*)option));
	strcat(command,((const char*)file_png));
	system(command);
	printf("Export enregistré ici : %s\n", file_png);
}



