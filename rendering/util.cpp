#include "util.hpp"

#include "SDL2/SDL_image.h"
#include "globals.hpp"

#include <SDL2/SDL_rect.h>
#include <stdexcept>


std::string sdl_error(const char * str) 
{
   return std::string(str) + SDL_GetError();
}


void render_fill_rect(SDL_Rect * rect, SDL_Color col)
{
   SDL_Color c;
   SDL_Renderer * ren = globals.gui.renderer();
   SDL_GetRenderDrawColor(ren, &c.r, &c.g, &c.b, &c.a);
   SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, col.a);

   SDL_RenderFillRect(ren, rect);

   SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
}


// its not trivial to control line width with SDL_RenderDrawRect 
void render_draw_rect(SDL_Rect * rect, SDL_Color col, int width)
{
   SDL_Rect r;
   SDL_Color c;
   SDL_Renderer * ren = globals.gui.renderer();
   SDL_GetRenderDrawColor(ren, &c.r, &c.g, &c.b, &c.a);
   SDL_SetRenderDrawColor(ren, col.r, col.g, col.b, col.a);


   // horizontal lines
   r = *rect;
   r.h = width;
   SDL_RenderFillRect(ren, &r);
   r.y = r.y + rect->h - width;
   SDL_RenderFillRect(ren, &r);

   // vertical lines
   r = *rect;
   r.w = width;
   SDL_RenderFillRect(ren, &r);
   r.x = r.x + rect->w - width;
   SDL_RenderFillRect(ren, &r);

   SDL_SetRenderDrawColor(ren, c.r, c.g, c.b, c.a);
}



SDL_Texture * load_png_texture(const char * filename)
{
   SDL_Renderer * ren = globals.gui.renderer();
   SDL_Surface * surface = IMG_Load(filename);

   if ( surface == NULL ) throw std::runtime_error(sdl_error("failed to create a surface: "));

   SDL_Texture * texture = SDL_CreateTextureFromSurface(ren, surface);
   SDL_FreeSurface(surface);

   return texture;
}


SDL_Texture * copy_texture(SDL_Texture * texture)
{
   int width, height;
   SDL_Renderer * ren = globals.gui.renderer();
   int res = SDL_QueryTexture(texture, NULL, NULL, &width, &height);
   if ( res != 0 ) throw std::runtime_error(sdl_error("failed to query a texture: "));

   SDL_Texture * new_texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
   if ( new_texture == NULL ) throw std::runtime_error(sdl_error("failed to create a texture: "));

   SDL_SetTextureBlendMode(new_texture, SDL_BLENDMODE_BLEND);
   SDL_SetRenderTarget(ren, new_texture);
   SDL_RenderCopy(ren, texture, NULL, NULL);
   SDL_SetRenderTarget(ren, NULL);

   return new_texture;
}



bool rect_intersect(SDL_Rect a, SDL_Rect b)
{
   SDL_Rect intersection;
   return SDL_IntersectRect(&a, &b, &intersection);
}


void center_rect(SDL_Rect &a, SDL_Rect b)
{
   a.x = ( b.w - a.w ) / 2;
   a.y = ( b.h - a.h ) / 2;
}


void move_rect(SDL_Rect &r, int s, Direction dir)
{
   switch ( dir ) {
      case Direction::Right: r.x += s; break;
      case Direction::Left: r.x -= s; break;
      case Direction::Down: r.y += s; break;
      case Direction::Up: r.y -= s; break;
   }
}


void print_rect(SDL_Rect r)
{
   printf("{ %d, %d, %d, %d }\n", r.x, r.y, r.w, r.h);
}
