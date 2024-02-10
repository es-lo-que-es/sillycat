#include "gui_globals.hpp"

#include <filesystem>
using dir_iterator = std::filesystem::directory_iterator;


int GuiGlobals::tick() const 
{ 
   return mtick;
}


SDL_Rect GuiGlobals::rect() const 
{ 
   return mrect;
}


SDL_Renderer * GuiGlobals::renderer() const 
{ 
   return mrenderer.get();
}


const std::vector<Font>& GuiGlobals::fonts() const 
{ 
   return mfonts;
}


void GuiGlobals::init_fonts(const Config &config)
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


void GuiGlobals::init(const Config &config, SDL_Rect r, int tick)
{
   mtick = tick; mrect = r;

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

   init_fonts(config);
   textures.init();
}


void GuiGlobals::update_colors(SDL_Color f, SDL_Color b)
{
   for ( Font &font : mfonts ) font.set_color(f);
   SDL_SetRenderDrawColor(mrenderer.get(), b.r, b.g, b.b, b.a);
}
