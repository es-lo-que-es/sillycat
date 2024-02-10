#ifndef SILLYCAT_GAME_DISPLAY_HEADER
#define SILLYCAT_GAME_DISPLAY_HEADER

#include "game.hpp"
#include "display.hpp"
#include "sprite.hpp"
#include "score_label.hpp"
#include "text_button.hpp"
#include "indication.hpp"
#include <array>


class GameDisplay : public Display {

 public:
   void render();
   void handle_event(SDL_Event * e);
   GameDisplay(Game * game, SDL_Rect rect);
   void reset();

 private:
   void render_player();
   void update_scores();

   std::array<bool, 4> active_directions;

   ScoreLabel mhealth_bar;
   ScoreLabel mscore_label;
   TextButton mclose_button;
   Indicator indicator;

   Sprite mplayer_sprite;
   Game * mgame;
};


#endif
