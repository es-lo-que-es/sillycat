#include "menus.hpp"
#include "globals.hpp"


MainMenu::MainMenu(SDL_Rect rect)
{
   mrect = rect;
   high_score.init("high score:", {rect.x, rect.y, rect.w, 24}, 24);
   high_score.update(globals.highscore);

   sound_switch.init(globals.gui.textures[TextureName::Sound], { 20, rect.h - 60, 40, 40 });

   rect.w = rect.w / 2;
   rect.h = rect.h / 4;

   rect.x += rect.w / 2;  
   rect.y += rect.h;

   play_button.init("PLAY", rect);
   rect.y += rect.h;
   exit_button.init("EXIT", rect);

   children.push_back(&sound_switch);
   children.push_back(&play_button);
   children.push_back(&exit_button);
   children.push_back(&high_score);
}


void MainMenu::render()
{
   if ( high_score.score() != globals.highscore ) 
      high_score.update(globals.highscore);

   Display::render();
}
