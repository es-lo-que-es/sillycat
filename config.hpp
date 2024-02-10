#ifndef SILLYCAT_CONFIG_HEADER
#define SILLYCAT_CONFIG_HEADER

#include "effects.hpp"

#include <string>
#include <vector>
#include <SDL2/SDL.h>


struct Config {
   
   const std::pair<std::u32string, Effect> &random_word_combo() const;
   std::vector<std::pair<std::u32string, Effect>> word_combos;

   SDL_Color background_color;
   SDL_Color font_color;

   std::u32string alphabet;
   int font_size;

   Config();
};

#endif
