#ifndef SILLYCAT_LETTER_HEADER
#define SILLYCAT_LETTER_HEADER

#include "effects.hpp"
#include "font.hpp"


struct Letter {

   Letter();
   Letter(uint32_t ch, Effect effect, const Font * font);

   void render(SDL_Rect * dest) const;

   const Font * font;
   Effect effect;

   uint32_t ch;
};


#endif
