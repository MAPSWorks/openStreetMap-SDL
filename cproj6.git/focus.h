#ifndef FOCUS_H
#define FOCUS_H

void zoom_in(SDL_Surface *);
void zoom_out(SDL_Surface *);
void moov_up(SDL_Surface *);
void moov_down(SDL_Surface *);
void moov_right(SDL_Surface *);
void moov_left(SDL_Surface *);
int lat_in_bounds(double);
int lon_in_bounds(double);

#endif
