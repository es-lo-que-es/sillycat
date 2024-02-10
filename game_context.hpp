#ifndef SILLYCAT_GAME_CONTEXT_HEADER
#define SILLYCAT_GAME_CONTEXT_HEADER


#include "display.hpp"
#include "game_display.hpp"
#include "menus.hpp"


struct GameContext {

   Game game;
   GameDisplay game_display;
   MainMenu main_menu;

   bool game_running = false;
   Display * display = nullptr;

   void init(SDL_Rect rect, int board_size, int player_health);
   GameContext(SDL_Rect rect, int board_size, int player_health);
   GameContext();
   void loop();
};


#endif
