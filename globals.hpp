#ifndef SILLYCAT_GLOBALS_HEADER
#define SILLYCAT_GLOBALS_HEADER

#include "config.hpp"
#include "font.hpp"
#include "texture_pack.hpp"
#include "guard.hpp"
#include <SDL2/SDL.h>
#include <vector>


class Globals {
   
 public:
   bool run = true;
   int highscore = 0;

   void reset_speed();
   void mod_speed(int val);

   void init(SDL_Rect rect, int tick, int speed);

   TexturePack textures;
   const Config config;

   SDL_Renderer * renderer() const;
   const std::vector<Font>& fonts() const;
   SDL_Rect rect() const;

   int speed() const;
   int tick() const;

   ~Globals();

 private:
   SdlGuard msdl;
   WindowGuard mwindow;
   RendererGuard mrenderer;

   std::vector<Font> mfonts;
   void init_fonts();

   int mmax_speed, mmin_speed;
   int mdefault_speed, mspeed;

   SDL_Rect mrect;
   int mtick;
};


extern Globals globals;

#endif
