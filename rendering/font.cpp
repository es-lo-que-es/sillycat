#include "font.hpp"
#include "globals.hpp"
#include "util.hpp"
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <algorithm>


const int max_width = 2048;

const int rmask = 0x000000ff;
const int gmask = 0x0000ff00;
const int bmask = 0x00ff0000;
const int amask = 0xff000000;


void append_glyph(SDL_Surface * target, TTF_Font * font, SDL_Rect r, uint32_t ch)
{
   int res = TTF_GlyphIsProvided32(font, ch);
   if ( res == 0 ) ch = '?'; 

   int advance = 0;
   // align glyph to the rect center
   TTF_GlyphMetrics32(font, ch, NULL, NULL, NULL, NULL, &advance);
   r.x += (r.w - advance) / 2;

   SDL_Surface * glyph = TTF_RenderGlyph32_Solid(font, ch, {255, 255, 255, 255});
   if ( glyph == nullptr ) throw std::runtime_error(sdl_error("failed to render a glyph: "));

   SDL_BlitSurface(glyph, nullptr, target, &r);
   SDL_FreeSurface(glyph);
} 


SDL_Rect glyph_rect(TTF_Font * font) 
{
   SurfaceGuard surface(TTF_RenderGlyph32_Solid(font, 'A', { 0, 0, 0, 0 }));
   return { 0, 0, surface.get()->w, surface.get()->h };
}


Font::Font(const std::string &path, const std::u32string &abc, int size)
   : mcharset(abc)
{
   mrect.w = size;
   mrect.x = mrect.y = 0;

   // sorting charset in case its not so i can use binary search
   std::sort(mcharset.begin(), mcharset.end());

   FontGuard font(TTF_OpenFont(path.c_str(), size));
   mrect.h = glyph_rect(font.get()).h;
   
   mrowsize = max_width / size;
   SurfaceGuard surface(SDL_CreateRGBSurface(0, max_width, max_width, 32, rmask, gmask, bmask, amask));

   int i = 0;
   SDL_Rect r = mrect;

   while ( i < mcharset.size() ) {

      for ( int j = 0; j < mrowsize && i < mcharset.size(); ++j ) {

         append_glyph(surface.get(), font.get(), r, mcharset[i]);

         r.x += r.w;
         ++i;
      } 

      r.y += r.h;
      r.x = 0;
   }
   
   mtexture_guard.reset(SDL_CreateTextureFromSurface(globals.gui.renderer(), surface.get()));
}


int Font::find_character(uint32_t ch) const
{
   auto it = std::lower_bound(mcharset.begin(), mcharset.end(), ch);
   if ( it == mcharset.end() || *it != ch ) return -1;

   return it - mcharset.begin();
}


void Font::render_character(uint32_t ch, SDL_Rect * dest) const
{
   int index = find_character(ch);
   if ( index == -1 ) return;

   SDL_Rect r = mrect;
   r.y = (index / mrowsize) * r.h;
   r.x = (index % mrowsize) * r.w;

   SDL_RenderCopy(globals.gui.renderer(), mtexture_guard.get(), &r, dest);
}


void Font::render_string(const std::string &str, SDL_Point point, int font_size) const
{
   SDL_Rect r = { point.x, point.y, font_size, font_size };

   for ( char c : str ) {
      render_character((uint32_t)c, &r);
      r.x += r.w;
   }
}


void Font::set_color(SDL_Color c)
{
   SDL_SetTextureColorMod(mtexture_guard.get(), c.r, c.g, c.b);
}
