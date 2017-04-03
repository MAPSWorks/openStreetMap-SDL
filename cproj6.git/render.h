SDL_Surface *image_render[30];
int nb_zoom;
int pos_moov;
SDL_Surface *save_zoom[2];

#ifndef RENDER_H
#define RENDER_H

void sdl_main();
void init_window(SDL_Surface *);
void restart_window(SDL_Surface *);
void is_running(SDL_Surface *); 
void background_menu(SDL_Surface *); 
void text_menu(SDL_Surface *); 
void print_water_area(SDL_Surface *, short *, short *, int, char* );
void print_building(SDL_Surface *, short *, short *, int, char* );
void print_grass_area(SDL_Surface *, short *, short *, int, char* );
void print_road_by_type(SDL_Surface *, short *, short *, int , char *,int);
void print_cycleway(SDL_Surface *, short *, short *y, int);
SDL_Rect get_pos_polygon(short *, short *, int);
SDL_Rect get_pos_line(short *, short *, int);
void export(SDL_Surface *);
void load_image();
void load_zoom(SDL_Surface *);
void print_image_render(int, int , int ,SDL_Surface *);
void print_element(SDL_Surface *, short *, short *, int , char *,int);
void entry_user_download_osm(SDL_Surface *);

#endif
