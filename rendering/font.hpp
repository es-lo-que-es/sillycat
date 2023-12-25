#ifndef SILLYCAT_FONT_HEADER
#define SILLYCAT_FONT_HEADER

#include "guard.hpp"
#include <SDL2/SDL.h>
#include <string>


class Font {

 public:
   Font(const std::string &path, const std::u32string &abc, int font_size);

   void render_character(uint32_t ch, SDL_Rect * dest) const;
   int find_character(uint32_t ch) const;

   void render_string(const std::string &str, SDL_Point point, int font_size) const;
   void set_color(SDL_Color col);

 private:
   TextureGuard mtexture_guard;
   std::u32string mcharset;
   int mrowsize;

   SDL_Rect mrect;
};



#endif
