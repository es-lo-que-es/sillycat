#include "game_context.hpp"
#include "globals.hpp"
#include <stdio.h>

Globals globals;

const int player_hp = 9;
const int tick = 24;

const SDL_Rect rect = { 0, 0, 600, 600 };


int main()
{
   int speed = rect.w / 100;
   int font_size = rect.w / 16;

   try {

      globals.init(rect, tick, speed);
      GameContext context(rect, font_size, player_hp);

      context.loop();

   } catch ( std::exception &e ) {
      printf("something went wrong: %s\n", e.what());
   }

   return 0;
}
