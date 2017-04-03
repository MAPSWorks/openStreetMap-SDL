#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
#include "sdl_ext.h"

 /**
	* \param ecran la surface de notre fenetre
	* \param point1 le point de départ
	* \param point2 le point de d'arrivée
	* \param couleur la couleur de la ligne
	* \param épaisseur l'épaisseur de la ligne
	* \author Fadyl Bello
	* \brief Impression d'une ligne sur le render
	* \fn la fonction crée un pixel(une surface) et imprime sur chaque pixel entre les deux points
	* \bug Segmentation fault pour des lignes trop petites(invisible à l'oeil nue)
	* \date Février 2016
	* \return EXIT_SUCESS quand tout est terminé
	* \version 1.0
	*/

long drawLine (SDL_Surface *ecran, SDL_Rect point1, SDL_Rect point2, SDL_Color couleur, long epaisseur)
{
    SDL_Surface *pixel = NULL;
    SDL_Rect position;
 	int H_V = 0;
    long horizontale = 0, verticale = 0, arrondi = 0, iMax = 0,i;
    double progression = 0, X = 0, Y = 0, resultat = 0;
    pixel = SDL_CreateRGBSurface(SDL_HWSURFACE, epaisseur, epaisseur, 32, 0, 0, 0, 0); 
    SDL_FillRect(pixel, NULL, SDL_MapRGB(ecran->format, couleur.r, couleur.g, couleur.b)); 
 
    
 
    horizontale = point2.x - point1.x;
    verticale = point2.y - point1.y;
 
    if (abs(horizontale) >= abs(verticale))
        H_V = 1;
 
    X = abs(horizontale);
    Y = abs(verticale);
 
    if (H_V == 1)
    {
        iMax = abs(horizontale);
        progression = Y/X;
    }
    else
    {
        iMax = abs(verticale);
        progression = X/Y;
    }
 
	
    for (i = 0; i < iMax; i++)
    {
        if (point2.x <= point1.x && point2.y >= point1.y)
        {
            if (H_V == 1)
            {
                position = point2;
                position.x = position.x + i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.y = position.y - arrondi;
                SDL_BlitSurface(pixel, NULL, ecran, &position);
            }
            else
            {
                position = point2;
                position.y = position.y - i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.x = position.x + arrondi;
                SDL_BlitSurface(pixel, NULL, ecran, &position);
            }
        }
        if (point2.x <= point1.x && point2.y <= point1.y)
        {
            if (H_V == 1)
            {
                position = point2;
                position.x = position.x + i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.y = position.y + arrondi;
                SDL_BlitSurface(pixel, NULL, ecran, &position);
            }
            else
            {
                position = point2;
                position.y = position.y + i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.x = position.x + arrondi;
                SDL_BlitSurface(pixel, NULL, ecran, &position);
            }
        }
        else if (point2.x >= point1.x && point2.y >= point1.y)
        {
            if (H_V == 1)
            {
                position = point2;
                position.x = position.x - i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.y = position.y - arrondi;
                SDL_BlitSurface(pixel, NULL, ecran, &position);
            }
            else
            {
                position = point2;
                position.y = position.y - i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.x = position.x - arrondi;
                SDL_BlitSurface(pixel, NULL, ecran, &position);
            }
        }
        else if (point2.x >= point1.x && point2.y <= point1.y)
        {
            if (H_V == 1)
            {
                position = point2;
                position.x = position.x - i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.y = position.y + arrondi;
                SDL_BlitSurface(pixel, NULL, ecran, &position);
            }
            else
            {
                position = point2;
                position.y = position.y + i;
                X = i;
                resultat = progression * X;
                arrondi = resultat;
                position.x = position.x - arrondi;
                SDL_BlitSurface(pixel, NULL, ecran, &position);
            }
        }
    }
    return 1;
}


