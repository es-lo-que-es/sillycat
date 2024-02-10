#ifndef SILLYCAT_UTIL_HEADER
#define SILLYCAT_UTIL_HEADER

#include "direction.hpp"
#include <SDL2/SDL.h>
#include <string>


std::string sdl_error(const char * str);

void render_fill_rect(SDL_Rect * rect, SDL_Color col);
void render_draw_rect(SDL_Rect * rect, SDL_Color col, int width = 2);

SDL_Texture * load_png_texture(const char * filename);
SDL_Texture * copy_texture(SDL_Texture * texture);

void move_rect(SDL_Rect &r, int step, Direction dir);
bool rect_intersect(SDL_Rect a, SDL_Rect b);
void center_rect(SDL_Rect &a, SDL_Rect b);

void print_rect(SDL_Rect r);

#endif
