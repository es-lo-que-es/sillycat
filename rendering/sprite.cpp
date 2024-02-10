#include "sprite.hpp"
#include "globals.hpp"
#include <stdexcept>


Sprite::Sprite(SDL_Texture * texture, int period, int mframe_width)
   : mtexture(texture)
{
   mrect = { 0, 0, 0, 0 };
   mtick = mperiod = period;
   if ( mframe_width <= 0 ) throw std::runtime_error("invalide sprite mframe width");
   SDL_QueryTexture(texture, nullptr, nullptr, &mrect.w, &mrect.h);
   
   mframes = mrect.w / mframe_width;
   mrect.w = mframe_width;
}


void Sprite::reset()
{
   mrect.x = 0;
   mframe = 0;
}


void Sprite::next_frame()
{  
   if ( ++mframe == mframes ) return reset();
   mrect.x += mrect.w;
}


void Sprite::render(SDL_Rect * dest)
{
   SDL_RenderCopy(globals.gui.renderer(), mtexture, &mrect, dest);

   mtick -= globals.gui.tick();
   if ( mtick > 0 ) return;

   mtick = mperiod;
   next_frame();
}

