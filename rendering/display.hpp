#ifndef SILLYCAT_DISPLAY_HEADER
#define SILLYCAT_DISPLAY_HEADER

#include <SDL2/SDL.h>
#include <vector>


class Display {

 public:

   Display();
   virtual ~Display();
   explicit Display(SDL_Rect rect);

   SDL_Rect rect() const;
   void set_rect(SDL_Rect rect);
   bool in_rect(SDL_Point point) const;

   virtual void handle_event(SDL_Event * e);
   virtual void render();

 protected:
   std::vector<Display *> children;
   SDL_Rect mrect;

};


#endif
