#ifndef SILLYCAT_TEXT_BUTTON_HEADER
#define SILLYCAT_TEXT_BUTTON_HEADER

#include "centered_label.hpp"
#include "display.hpp"


class TextButton : public Display
{

 public:
   void render();
   void handle_event(SDL_Event * e);

   void init(const std::string &text, SDL_Rect r);
   TextButton(const std::string &text, SDL_Rect r);
   void set_click_handler(void (*ptr)(void *), void * par);

   TextButton();

 private:
   void (*mclick_handler)(void * par) = nullptr;
   void * mparameter = nullptr;

   CenteredLabel mlabel;
   bool mhovered = false;

};


#endif
