#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <SDL/SDL_gfxPrimitives.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_image.h>
#include <float.h>
#include <string.h>

#ifndef CONSTANTE_H
#define CONSTANTE_H

#define TRUE 1
#define FALSE 0

#define CP_WIDTH_RENDER 750
#define CP_WIDTH_MENU 200
#define CP_HEIGHT_RENDER 500 
#define CP_RAYON_X 0.006
#define CP_RAYON_Y 0.00075

#define MAX_SIZE_TAG 100
#define MAX_SIZE_MEMBER 500
#define MAX_SIZE_NODE_IN_WAY 2000

#define SIZE_EARTH 40075000
#define DIST_ONE_DEGREE 111319.4444

#define TYPE_WAY_RESIDENTIAL 1
#define TYPE_WAY_CYCLEWAY 2
#define TYPE_WAY_TERTIARY 3
#define TYPE_WAY_PEDESTRIAN 4
#define TYPE_WAY_PRIMARY 5
#define TYPE_WAY_UNCLASSIFIED 6
#define TYPE_WAY_BUILDING 7
#define TYPE_WAY_GRASS 8
#define TYPE_WAY_GRASSS 18
#define TYPE_WAY_FOOTWAY 9
#define TYPE_WAY_WALL 10
#define TYPE_WAY_RAIL 11
#define TYPE_WAY_LAYER 12
#define TYPE_WAY_BOUDARY_ADMIN 13
#define TYPE_WAY_BRIDGE 14
#define TYPE_WAY_RIVERBANK 15
#define TYPE_WAY_NATURALWATER 16 
#define TYPE_WAY_WALL_BUILDING 17
#define TYPE_WAY_COAST 18
#define TYPE_WAY_BUILDING_AREA 19
#define TYPE_WAY_CONSTRUCTION 20

#define MOOV_MID_CENTER 0
#define MOOV_MID_LEFT 1
#define MOOV_MID_RIGHT 2
#define MOOV_UP_CENTER 3
#define MOOV_UP_LEFT 4
#define MOOV_UP_RIGHT 5
#define MOOV_DOWN_CENTER 6
#define MOOV_DOWN_LEFT 7
#define MOOV_DOWN_RIGHT 8


#define ORDER_RIVERBANK 0
#define ORDER_WATER 1
#define ORDER_FOREST 2
#define ORDER_PARK 3
#define ORDER_UNCLASSIFIED 4
#define ORDER_SERVICE 5
#define ORDER_HIGHWAY 6
#define ORDER_FOOTWAY 7
#define ORDER_PEDESTRIAN 8
#define ORDER_BRIDGE 9
#define ORDER_BUILDING 10
#define ORDER_RESIDENTIAL 11
#define ORDER_CYCLEWAY 12
#define ORDER_TERTIARY 13
#define ORDER_SECONDARY 14
#define ORDER_PRIMARY 15
#define ORDER_WALL 16
#define ORDER_FENCE 17
#define ORDER_GRASS 18
#define ORDER_RAIL 19
#define ORDER_SUBWAY 20
#define ORDER_ADMINISTRATIVE 21


#define IMG_COFFEE 0
#define IMG_CHURCH 1
#define IMG_MUSEE 2
#define IMG_POSTE 3
#define IMG_RESTAURANT 4
#define IMG_TEL 5
#define IMG_TRAFFIC 6
#define IMG_VELO 7


#endif




