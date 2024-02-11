#ifndef SILLYCAT_MENUS_HEADER
#define SILLYCAT_MENUS_HEADER

#include "display.hpp"
#include "score_label.hpp"
#include "switch_button.hpp"
#include "text_button.hpp"


struct MainMenu : public Display {

   MainMenu(SDL_Rect rect);

   SwitchButton sound_switch;
   TextButton play_button;
   TextButton exit_button;
   ScoreLabel high_score;
   
   void render();
};




#endif
