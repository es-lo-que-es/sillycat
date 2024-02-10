#include "indication.hpp"
#include "globals.hpp"
#include "util.hpp"

using namespace std::chrono;


SDL_Color INDICATION_COLORS[] = {
   { 50, 169, 169, 255 },  // blue
   { 134, 147, 147, 255 }, // gray
   { 50, 168, 82, 255 },   // green
   { 169, 50, 50, 255 }    // red
};


SoundName INDICATION_SOUNDS[] = { SoundName::Gain, SoundName::Loss, SoundName::Gain, SoundName::Loss };


Indicator::Indicator(SDL_Rect rect)
{
   int offs = 8;

   rect.x += offs; rect.y += offs;
   rect.w -= offs*2; rect.h -= offs*2;

   mrect = rect;
}


void Indicator::reset()
{
   for ( auto &tp : mtpoints ) tp = time_point<high_resolution_clock>();
}


void Indicator::indicate(Indication ind)
{
   int index = (int)ind;
   globals.audio.play_sound(INDICATION_SOUNDS[index]);
   mtpoints[index] = high_resolution_clock::now();
}


void Indicator::render()
{
   auto now = high_resolution_clock::now();

   for ( int i = 0; i < (int)Indication::Count; ++i ) {
      duration<double, std::milli> elapsed = now - mtpoints[i];
      if ( elapsed.count() < mperiod ) render_draw_rect(&mrect, INDICATION_COLORS[i], 5);
   }
}
