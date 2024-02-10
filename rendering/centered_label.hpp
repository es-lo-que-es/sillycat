#ifndef SILLYCAT_CENTERED_LABEL_HEADER
#define SILLYCAT_CENTERED_LABEL_HEADER

#include "display.hpp"
#include <SDL2/SDL.h>
#include <string>


class CenteredLabel : public Display {
   
 public:

   CenteredLabel();
   void init(const std::string &str, SDL_Rect rect, int font_size, bool background = false);
   CenteredLabel(const std::string &str, SDL_Rect rect, int font_size, bool background = false);
   
   void replace_tail(const char * str);
   void render();

 private:

   void adjust_alignment();

   std::string mtext;
   bool mbackground;

   SDL_Rect mtarget;
   int mfont_size;

   int minit_len;
};


#endif
