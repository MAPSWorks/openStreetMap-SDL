#include "constante.h"
#include "import_osm.h"
#include "render.h"
#include "recherche.h"

/**
 * \param window surface où écrire la valeur de retour
 * \brief Récupere les valeurs lat/lon de l'utilisateur
 * \author Fadyl Bello
 * \version 1.0
 * \date 23 Mars 2016
 */
void entry_user_download_osm(SDL_Surface *window)
{
    char lat[16],lon[16], letter;
    int index=0, end=0,instructions=0;
    SDL_Event event;
    SDL_Rect position,position_instructions;
	TTF_Font *font;
	SDL_Color whiteColor;
	SDL_Surface *text_one,*text_instructions;
	float minlat,maxlat,minlon,maxlon;
	
	whiteColor.r =255;
	whiteColor.g =255;
	whiteColor.b =255;
	
	font = TTF_OpenFont("LongTime.ttf",10);
	position.x= CP_WIDTH_RENDER+10;
    position.y=320;
    
    position_instructions.x= CP_WIDTH_RENDER+10;
    position_instructions.y=300;
    
     text_instructions = TTF_RenderUTF8_Blended(font,"Taper le centre de la latitude", whiteColor);           
     SDL_BlitSurface(text_instructions,NULL,window,&position_instructions);
     SDL_Flip(window);

    while (!end)
    {
        SDL_WaitEvent(&event);
         
        if (event.type==SDL_KEYDOWN)
        {
     
            letter=event.key.keysym.unicode;
                 
            if ((letter>=SDLK_0 && letter<=SDLK_9) || letter == SDLK_PERIOD)
            {
 				if(instructions ==0)
 				{
                  lat[index]=letter;
                  lat[index+1]='\0';
                  text_one = TTF_RenderUTF8_Blended(font,lat, whiteColor);
                }
                else
                {
                  lon[index]=letter;
                  lon[index+1]='\0';
                  text_one = TTF_RenderUTF8_Blended(font,lon, whiteColor);
                }
                
                index++;/*on se prépare à recevoir la prochaine lettre*/  
                SDL_BlitSurface(text_one,NULL,window,&position);
                SDL_Flip(window);
            }
             
            if (letter==SDLK_BACKSPACE && index>0)
            {    
            	printf("effacer\n");
            	index--;
            	lat[index]='\0';
            	background_menu(window);
				text_menu(window);
				if(instructions == 0)
				{
					text_one = TTF_RenderUTF8_Blended(font,lat, whiteColor);
					text_instructions = TTF_RenderUTF8_Blended(font,"Taper le centre de la latitude", whiteColor);      
				}
				else
				{
					text_one = TTF_RenderUTF8_Blended(font,lat, whiteColor);
				    text_instructions = TTF_RenderUTF8_Blended(font,"Taper le centre de la longitude", whiteColor);   
				}
				SDL_BlitSurface(text_one,NULL,window,&position);
				SDL_BlitSurface(text_instructions,NULL,window,&position_instructions);
				SDL_Flip(window);
            	
            } 
            if (letter==SDLK_RETURN)/*return*/
            {
            	if(instructions ==0)
            	{
            		 instructions = 1;
            		 background_menu(window);
  					 text_menu(window);
            		 text_instructions = TTF_RenderUTF8_Blended(font,"Taper le centre de la longitude", whiteColor);           
					 SDL_BlitSurface(text_instructions,NULL,window,&position_instructions);
					 SDL_Flip(window);
					 printf("lat : %s\n", lat);
					 index = 0;
           		}
           		else
           		{
           			background_menu(window);
				    text_menu(window);
        		    text_instructions = TTF_RenderUTF8_Blended(font,"Fichier Téléchargé!", whiteColor);           
				    SDL_BlitSurface(text_instructions,NULL,window,&position_instructions);
				    SDL_Flip(window);
           			printf("lat : %s && lon : %s\n", lat,lon);
           			minlon = strtof(lon,NULL) - CP_RAYON_X ;
           			minlat = strtof(lat,NULL) - CP_RAYON_Y;
           			maxlon = strtof(lon,NULL) + CP_RAYON_X;
           			maxlat = strtof(lat,NULL) + CP_RAYON_Y;
           			printf(" Param ; %f %f %f %f\n", minlon,minlat,maxlon,maxlat);
           			get_osmfile_request(minlon,minlat,maxlon,maxlat);
                	end=1;
                }
            }
        }
    }
}

/**
 * \param window surface où écrire la valeur de retour
 * \brief Récupere les valeurs (6max) utilisateur de la recherche globale
 * \author Fadyl Bello
 * \version 1.0
 * \date 23 Mars 2016
 */
void entry_user_global_search(SDL_Surface *window)
{
	char elem[6][16], letter;
	int index=0, end=0,instructions=0,i;
	SDL_Event event;
	SDL_Rect position[6],position_instructions;
	TTF_Font *font;
	SDL_Color whiteColor;
	SDL_Surface *text[6],*text_instructions;

	whiteColor.r =255;
	whiteColor.g =255;
	whiteColor.b =255;

	font = TTF_OpenFont("LongTime.ttf",10);
	for(i = 0; i <6; i++)
	{
		position[i].x= CP_WIDTH_RENDER+10;
		position[i].y=320 +i*20;
		elem[i][0] = '\0';
	}
	position_instructions.x= CP_WIDTH_RENDER+10;
	position_instructions.y=300;

	text_instructions = TTF_RenderUTF8_Blended(font,"Taper votre lieu(Entrée pour terminé)", whiteColor);           
	SDL_BlitSurface(text_instructions,NULL,window,&position_instructions);
	SDL_Flip(window);
	
	while (!end)
    {
        SDL_WaitEvent(&event);
         
        if (event.type==SDL_KEYDOWN)
        {
            letter=event.key.keysym.unicode;
                 
            if ((letter>=SDLK_0 && letter<=SDLK_9) || (letter>=SDLK_a && letter<=SDLK_z))
            {
 			  /*On rempli l'instruction où on est*/
              elem[instructions][index]=letter;
              elem[instructions][index+1]='\0';
              index++;
              /* on affiche là où on est*/
              for(i = 0; i < 6; i++)
              {
              	text[i] = TTF_RenderUTF8_Blended(font,elem[i], whiteColor);
              	SDL_BlitSurface(text[i],NULL,window,&position[i]);
           	  }	
           	  
              SDL_Flip(window);
            }
             
            if (letter==SDLK_BACKSPACE && index>0)/*corerction si on se trompe*/
            {    
            	
            	index--;
            	elem[instructions][index]='\0';
            	background_menu(window);
				text_menu(window);

				for(i = 0; i < 6; i++)
		          {
		          	text[i] = TTF_RenderUTF8_Blended(font,elem[i], whiteColor);
		          	SDL_BlitSurface(text[i],NULL,window,&position[i]);
		       	  }	
				
				SDL_BlitSurface(text_instructions,NULL,window,&position_instructions);
				SDL_Flip(window);
            	
            } 
            if (letter==SDLK_SPACE)
            {
            	
            	if(instructions <= 5)
            	{
            		instructions++;
            		index=0;
            	}
            	else
            	{
            		letter = SDLK_RETURN;
            	}
            }
            if (letter==SDLK_RETURN)
            {
            	
           			background_menu(window);
				    text_menu(window);
				    get_datasearch_request(elem[0],elem[1],elem[2],elem[3],elem[4],elem[5],window,font,position_instructions);
        		   
                	end=1;
            }
        } 
    }

}

/**
 * \param window surface où écrire la valeur de retour
 * \brief Récupere les valeurs lat/lon de la recherche globale
 * \todo la fonction
 * \author Fadyl Bello
 * \version 1.0
 * \date 23 Mars 2016
 */
void entry_user_local_search(SDL_Surface *window)
{
	SDL_Flip(window);
}
