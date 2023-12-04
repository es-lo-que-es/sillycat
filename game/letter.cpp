#include "letter.hpp"
#include "globals.hpp"
#include "font.hpp"


Letter::Letter()
   : ch(0), font(nullptr)
{ }


Letter::Letter(uint32_t ch, Effect effect, const Font * font) 
   : ch(ch), effect(effect), font(font) 
{ 
   if ( effect.type == Random ) 
      font = &globals.fonts()[rand()%globals.fonts().size()];
}


void Letter::render(SDL_Rect * dest) const
{
   if ( font != nullptr) font->render_character(ch, dest);
}
