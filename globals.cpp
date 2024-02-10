#include "globals.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <chrono>
#include <fstream>
#include <stdio.h>
#include <stdexcept>


Globals::~Globals()
{
   std::fstream score("highscore", std::ios::binary | std::ios::out);
   if ( score.is_open() ) score.write((char*)&highscore, sizeof(highscore));
}



void Globals::init(SDL_Rect r, int tick, int s)
{
   speed.init(s);
   srand(time(0));
   
   std::fstream score("highscore", std::ios::binary | std::ios::in);
   if ( score.is_open() ) score.read((char*)&highscore, sizeof(highscore));

   gui.init(config, r, tick);
}


void Globals::reset()
{
   inversion.reset();
   speed.reset();
}
