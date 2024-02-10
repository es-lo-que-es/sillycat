#include "switch_button.hpp"

#include "util.hpp"
#include "globals.hpp"
#include <SDL2/SDL_render.h>


void SwitchButton::init(SDL_Texture * texture, SDL_Rect rect)
{
   mtexture = texture;
   mrect = rect;
}


void SwitchButton::set_click_handler(void (*ptr)(void*), void * par)
{
   mclick_handler = ptr; 
   mparameter = par;
}


void SwitchButton::handle_event(SDL_Event * e)
{
   if ( e->type == SDL_MOUSEBUTTONDOWN ) {

      if ( !in_rect({e->motion.x, e->motion.y}) ) return;
      if ( mclick_handler != nullptr ) mclick_handler(mparameter);
      mactive = !mactive;

   } else if ( e->type == SDL_MOUSEMOTION ) {
      mhovered = in_rect({e->motion.x, e->motion.y});
   } 
}


void SwitchButton::render()
{
   //if ( !mactive ) render_cross_rect(&mrect, globals.config.font_color);
   if ( mhovered ) render_draw_rect(&mrect, globals.config.font_color);
   
   SDL_RenderCopy(globals.gui.renderer(), mtexture, nullptr, &mrect);
}
