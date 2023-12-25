#include "indication.hpp"
#include "util.hpp"

using namespace std::chrono;


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
   for ( auto &tp : mtpoints ) tp = high_resolution_clock::from_time_t(0);
}


void Indicator::indicate(Indication ind)
{

   mtpoints[ind] = high_resolution_clock::now();
}


void Indicator::render()
{
   auto now = high_resolution_clock::now();

   for ( int i = 0; i < INDICATION_COUNT; ++i ) {
      duration<double, std::milli> elapsed = now - mtpoints[i];
      if ( elapsed.count() < mperiod ) render_draw_rect(&mrect, INDICATION_COLORS[i]);
   }
}
