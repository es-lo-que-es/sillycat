#include "font.hpp"
#include "globals.hpp"
#include "util.hpp"
#include <SDL2/SDL_ttf.h>
#include <stdexcept>


const int rmask = 0x000000ff;
const int gmask = 0x0000ff00;
const int bmask = 0x00ff0000;
const int amask = 0xff000000;


void append_glyph(SDL_Surface * target, TTF_Font * font, SDL_Rect r, SDL_Color col, uint32_t ch)
{
   int res = TTF_GlyphIsProvided32(font, ch);
   if ( res == 0 ) ch = '?'; 

   int advance = 0;
   // align glyph to the rect center
   TTF_GlyphMetrics32(font, ch, NULL, NULL, NULL, NULL, &advance);
   r.x += (r.w - advance) / 2;

   SDL_Surface * glyph = TTF_RenderGlyph32_Solid(font, ch, col);
   if ( glyph == nullptr ) throw std::runtime_error(sdl_error("failed to render a glyph: "));

   SDL_BlitSurface(glyph, nullptr, target, &r);
   SDL_FreeSurface(glyph);
} 


SDL_Rect glyph_rect(TTF_Font * font) 
{
   SurfaceGuard surface(TTF_RenderGlyph32_Solid(font, 'A', { 0 }));
   return { 0, 0, surface.get()->w, surface.get()->h };
}


Font::Font(const std::string &path, const std::u32string &abc, SDL_Color col, int size)
   : charset(abc)
{
   rect.w = size;

   FontGuard font(TTF_OpenFont(path.c_str(), size));
   rect.h = glyph_rect(font.get()).h;
   
   int w = size * abc.length();
   SurfaceGuard surface(SDL_CreateRGBSurface(0, w, rect.h, 32, rmask, gmask, bmask, amask));

   SDL_Rect r = rect;
   for ( uint32_t ch : charset ) {
      append_glyph(surface.get(), font.get(), r, col, ch);
      r.x += r.w; 
   }
   
   texture_guard.reset(SDL_CreateTextureFromSurface(globals.renderer(), surface.get()));
}


int Font::find_character(uint32_t ch) const
{
   for ( int i = 0; i < charset.length(); ++i ) 
      if ( charset[i] == ch ) return i;

   return -1;
}


void Font::render_character(uint32_t ch, SDL_Rect * dest) const
{
   int index = find_character(ch);
   if ( index == -1 ) return;

   SDL_Rect r = rect;
   r.x = r.w * index;

   SDL_RenderCopy(globals.renderer(), texture_guard.get(), &r, dest);
}


void Font::render_string(const std::string &str, SDL_Point point, int font_size) const
{
   SDL_Rect r = { point.x, point.y, font_size, font_size };

   for ( char c : str ) {
      render_character((uint32_t)c, &r);
      r.x += r.w;
   }
}
