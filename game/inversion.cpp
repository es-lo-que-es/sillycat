#include "inversion.hpp"
#include "globals.hpp"


Inversion::Inversion()
{
   mlasat_invert = std::chrono::time_point<std::chrono::high_resolution_clock>();
}


bool Inversion::active() const 
{
   return mactive;
}


void Inversion::apply_invert()
{
   SDL_Color f = globals.config.font_color;
   SDL_Color b = globals.config.background_color;
   
   globals.gui.update_colors(b, f);
   
   globals.config.background_color = f;
   globals.config.font_color = b;

   mactive = !mactive;
}


void Inversion::trigger()
{
   auto now = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> elapsed = now - mlasat_invert;

   if ( elapsed.count() < minterval ) return;

   mlasat_invert = now;
   apply_invert();
}


void Inversion::reset()
{
   if ( mactive ) apply_invert();
   mlasat_invert = std::chrono::time_point<std::chrono::high_resolution_clock>();
}
