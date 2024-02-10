#include "letter.hpp"
#include "globals.hpp"
#include "font.hpp"


Letter::Letter()
   : font(nullptr), ch(0)
{ }


Letter::Letter(uint32_t ch, Effect effect, const Font * font) 
   : font(font), effect(effect), ch(ch)
{ 
   if ( effect.type == EffectType::Random ) 
      font = &globals.gui.fonts()[rand()%globals.gui.fonts().size()];
}


void Letter::render(SDL_Rect * dest) const
{
   if ( font != nullptr) font->render_character(ch, dest);
}
