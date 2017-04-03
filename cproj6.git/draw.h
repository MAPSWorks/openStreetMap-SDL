#ifndef DRAW_H
#define DRAW_H

void print_water_area(SDL_Surface *, short *, short *, int, char *);
void print_building(SDL_Surface *, short *, short *, int, char *);
void print_grass_area(SDL_Surface *, short *, short *, int, char *);
void print_brown_area(SDL_Surface *, short *, short *, int, char *);
void print_road_by_type(SDL_Surface *, short *, short *, int, char *, int);
void print_cycleway(SDL_Surface *, short *, short *, int );
void print_image_render(int, int, int, SDL_Surface *);
void print_element(SDL_Surface *, short *, short *, int, char *, int);
void print_inner(SDL_Surface *, short *, short *,int );

#endif
