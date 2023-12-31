#include "globals.hpp"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <chrono>
#include <fstream>
#include <stdio.h>
#include <stdexcept>
#include <filesystem>


int Globals::tick() const { return mtick; }


int Globals::speed() const { return mspeed; } 


SDL_Rect Globals::rect() const { return mrect; }


SDL_Renderer * Globals::renderer() const { return mrenderer.get(); }


const std::vector<Font>& Globals::fonts() const { return mfonts; }


Globals::~Globals()
{
   std::fstream score("highscore", std::ios::binary | std::ios::out);
   if ( score.is_open() ) score.write((char*)&highscore, sizeof(highscore));
}


void Globals::mod_speed(int val)
{
   mspeed += val;

   if ( mspeed > mmax_speed ) mspeed = mmax_speed;
   else if ( mspeed < mmin_speed ) mspeed = mmin_speed;
}


using dir_iterator = std::filesystem::directory_iterator;

void Globals::init_fonts()
{
   for ( auto entry : dir_iterator("fonts") ) {

      bool not_ttf = entry.path().extension().compare(".ttf") != 0;
      if ( not_ttf ) continue;

      try { 
         mfonts.emplace_back(Font(entry.path().string(), config.alphabet, config.font_size));
         mfonts.back().set_color(config.font_color);
      } catch(std::exception &e) { 
         fprintf(stderr, "failed to create font: %s\n", e.what());
      }
   }

   if ( mfonts.size() == 0 ) {
      throw::std::runtime_error("no valid font found");
   }
}


void Globals::init(SDL_Rect r, int tick, int speed)
{
   mrect = r;
   mtick = tick;
   srand(time(0));
   
   mdefault_speed = mspeed = speed;

   mmin_speed = std::max(1.0, speed / 1.2);
   mmax_speed = std::max(1.0, speed * 1.4);
   
#ifdef EMSCRIPTEN_BUILD
   int window_flags = SDL_WINDOW_SHOWN;
#else
   int window_flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
#endif

   int pos = SDL_WINDOWPOS_CENTERED;
   mwindow.reset(SDL_CreateWindow("sillycat", pos, pos, r.w, r.h, window_flags));
   mrenderer.reset(SDL_CreateRenderer(mwindow.get(), -1, SDL_RENDERER_ACCELERATED));

   SDL_Color c = config.background_color;
   SDL_SetRenderDrawColor(mrenderer.get(), c.r, c.g, c.b, c.a);
   SDL_RenderSetLogicalSize(mrenderer.get(), r.w, r.h);

   std::fstream score("highscore", std::ios::binary | std::ios::in);
   if ( score.is_open() ) score.read((char*)&highscore, sizeof(highscore));

   mlasat_invert = std::chrono::time_point<std::chrono::high_resolution_clock>();

   textures.init();
   init_fonts();
}


bool Globals::inverted() const 
{
   return minverted;
}


void Globals::invert()
{
   auto now = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> elapsed = now - mlasat_invert;

   if ( elapsed.count() < minvert_period ) return;

   SDL_Color f = config.font_color;
   SDL_Color b = config.background_color;

   for ( Font &font : mfonts ) font.set_color(b);
   SDL_SetRenderDrawColor(mrenderer.get(), f.r, f.g, f.b, f.a);
   
   config.background_color = f;
   config.font_color = b;

   minverted = !minverted;
   mlasat_invert = now;
}


void Globals::reset()
{
   mlasat_invert = std::chrono::time_point<std::chrono::high_resolution_clock>();

   if ( minverted ) {

      SDL_Color f = config.font_color;
      SDL_Color b = config.background_color;

      SDL_SetRenderDrawColor(mrenderer.get(), f.r, f.g, f.b, f.a);
      for ( Font &font : mfonts ) font.set_color(b);

      config.background_color = f;
      config.font_color = b;

      minverted = false;
   }

   mspeed = mdefault_speed;
}
