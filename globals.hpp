#ifndef SILLYCAT_GLOBALS_HEADER
#define SILLYCAT_GLOBALS_HEADER

#include "audio_globals.hpp"
#include "config.hpp"
#include "gui_globals.hpp"
#include "inversion.hpp"
#include "speed_control.hpp"


struct Globals {
   
   Config config;
   GuiGlobals gui;
   AudioGlobals audio;

   Inversion inversion;
   SpeedControl speed;

   int highscore = 0;
   bool run = true;

   void init(SDL_Rect rect, int tick, int speed);
   void reset();
   ~Globals();
};


extern Globals globals;

#endif
