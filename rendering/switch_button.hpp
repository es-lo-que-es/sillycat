#ifndef SILLYCAT_SWITCH_BUTTON_HEADER
#define SILLYCAT_SWITCH_BUTTON_HEADER

#include "display.hpp"


class SwitchButton : public Display {

 public:
   void init(SDL_Texture * texture, SDL_Rect rect);
   void set_click_handler(void (*ptr)(void *), void * par);

   void handle_event(SDL_Event * e);
   void render();

 private:
   void (*mclick_handler)(void * par) = nullptr;
   void * mparameter = nullptr;

   SDL_Texture * mtexture;
   bool mhovered = false;
   bool mactive = true;

};


#endif
