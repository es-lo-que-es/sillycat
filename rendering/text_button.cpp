#include "text_button.hpp" 
#include "globals.hpp"
#include "util.hpp"
#include <SDL2/SDL_events.h>


TextButton::TextButton() { }


TextButton::TextButton(const std::string &text, SDL_Rect r)
{
   init(text, r);
}


void TextButton::init(const std::string &text, SDL_Rect r)
{ 
   int font_size = r.w / text.length();
   mlabel.init(text, r, font_size, true);

   children.push_back(&mlabel);
   mrect = r;
}


void TextButton::set_click_handler(void (*ptr)(void*), void * par)
{
   mclick_handler = ptr; 
   mparameter = par;
}


void TextButton::handle_event(SDL_Event * e)
{
   if ( e->type == SDL_MOUSEBUTTONDOWN ) {
      if ( mclick_handler != nullptr ) {
         if (in_rect({e->motion.x, e->motion.y})) mclick_handler(mparameter);
      }
   } else if ( e->type == SDL_MOUSEMOTION ) {
      mhovered = in_rect({e->motion.x, e->motion.y});
   } 
}


void TextButton::render()
{
   Display::render();

   if ( mhovered ) {
      render_draw_rect(&mrect, globals.config.font_color);
   }
}
