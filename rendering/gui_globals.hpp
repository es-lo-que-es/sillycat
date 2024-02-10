#ifndef SILLYCAT_GUI_GLOBALS_HEADER
#define SILLYCAT_GUI_GLOBALS_HEADER

#include "config.hpp"
#include "texture_pack.hpp"
#include "guard.hpp"
#include "font.hpp"

#include <vector>


class GuiGlobals {
 
 public:
   int tick() const;
   SDL_Rect rect() const;

   TexturePack textures;

   SDL_Renderer * renderer() const;
   const std::vector<Font>& fonts() const;

   void init(const Config &config, SDL_Rect rect, int tick);
   void update_colors(SDL_Color f, SDL_Color b);

 private:
   SdlGuard msdl;
   WindowGuard mwindow;
   RendererGuard mrenderer;

   void init_fonts(const Config &config);
   std::vector<Font> mfonts;

   SDL_Rect mrect;
   int mtick;
};


#endif
