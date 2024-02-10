#ifndef SILLYCAT_GUARDS_HEADER
#define SILLYCAT_GUARDS_HEADER

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "util.hpp"


class Guard {
 public:
   Guard() { };
   Guard(const Guard &other) = delete;
   Guard& operator = (const Guard &other) = delete;
   virtual ~Guard() { };
};


struct SdlGuard : Guard {

   SdlGuard() {

      int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
      if ( result != 0 ) throw std::runtime_error(sdl_error("sdl init failed: "));

      result = TTF_Init();

      if ( result != 0 ) {
         SDL_Quit();
         throw std::runtime_error(sdl_error("sdl_ttf init failed: "));
      }

   }

   ~SdlGuard()
   { 
      TTF_Quit();
      SDL_Quit();
   }
};



class WindowGuard : Guard {

 public:
   WindowGuard() { };
   explicit WindowGuard(SDL_Window * w) { reset(w); }
   
   void reset(SDL_Window * w) {
      if ( window ) SDL_DestroyWindow(window);
      if ( w == nullptr ) throw std::runtime_error(sdl_error("bad sdl window: "));
      window = w;
   }

   ~WindowGuard() { SDL_DestroyWindow(window); }
   SDL_Window * get() const { return window; }

 private:
   SDL_Window * window = nullptr;
};


class RendererGuard : Guard {

 public:
   RendererGuard() { };
   explicit RendererGuard(SDL_Renderer * r) { reset(r); }

   void reset(SDL_Renderer * r) {
      if ( renderer ) SDL_DestroyRenderer(renderer);
      if ( r == nullptr ) throw std::runtime_error(sdl_error("bad sdl renderer: "));
      renderer = r;
   }

   ~RendererGuard() { SDL_DestroyRenderer(renderer); }
   SDL_Renderer * get() const { return renderer; }
   
 private:
   SDL_Renderer * renderer= nullptr;
};


class TextureGuard : Guard {

 public:
   TextureGuard() { }
   explicit TextureGuard(SDL_Texture * t) { reset(t); }

   explicit TextureGuard(TextureGuard &&other) {
      reset(other.texture);
      other.texture = nullptr;
   }
   
   void reset(SDL_Texture * t) {
      if ( texture ) SDL_DestroyTexture(texture);
      if ( t == nullptr ) throw std::runtime_error(sdl_error("bad sdl renderer: "));
      texture = t;
   }

   ~TextureGuard() { SDL_DestroyTexture(texture); }
   SDL_Texture * get() const { return texture; }
   
 private:
   SDL_Texture * texture = nullptr;
};


class SurfaceGuard : Guard {

 public:
   SurfaceGuard() { }
   explicit SurfaceGuard(SDL_Surface * s) { reset(s); }

   void reset(SDL_Surface * s) {
      if ( surface ) SDL_FreeSurface(surface);
      if ( s == nullptr ) throw std::runtime_error(sdl_error("bad sdl surface: "));
      surface = s;
   }

   ~SurfaceGuard() { SDL_FreeSurface(surface); }
   SDL_Surface * get() const { return surface; }
   
 private:
   SDL_Surface * surface = nullptr;
};



class FontGuard : Guard {

 public:
   FontGuard() { }
   explicit FontGuard(TTF_Font * f) { reset(f); }

   void reset(TTF_Font * f) {
      if ( font ) TTF_CloseFont(font);
      if ( f == nullptr ) throw std::runtime_error(sdl_error("bad sdl font: "));
      font = f;
   }

   TTF_Font * get() const { return font; }
   ~FontGuard() { TTF_CloseFont(font); }
   
 private:
   TTF_Font * font = nullptr;
};


#endif
