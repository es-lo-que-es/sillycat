#include "indication.hpp"
#include "util.hpp"


SDL_Color INDICATION_COLORS[] = {
   { 50, 169, 169, 255 },
   { 134, 147, 147, 255 },
   { 50, 168, 82, 255 },
   { 169, 50, 50, 255 }
};


Indicator::Indicator(SDL_Rect rect)
{
   int offs = rect.w / 55;

   rect.x += offs; rect.y += offs;
   rect.w -= offs*2; rect.h -= offs*2;

   mrect = rect;
}


void Indicator::reset()
{
   count.fill(0);
}


void Indicator::indicate(Indication ind)
{
   count[ind] += 7;
}


void Indicator::render()
{
   for ( int i = 0; i < INDICATION_COUNT; ++i ) {

      if ( !count[i] ) continue;

      render_draw_rect(&mrect, INDICATION_COLORS[i]);
      --count[i];

   }
}
