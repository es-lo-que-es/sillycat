#include "game_context.hpp"
#include "game_display.hpp"
#include "globals.hpp"
#include "menus.hpp"


void exit_game(void * par)
{
   globals.run = false;
}


void start_game(void * par)
{
   GameContext * ctx = (GameContext * ) par;
   ctx->display = &ctx->game_display;

   ctx->game_running = true;

   ctx->game_display.reset();
   ctx->game.reset();
}


GameContext::GameContext(SDL_Rect r, int size, int hp)
   : game(size, hp),
     game_display(&game, r),
     main_menu(r)
{
   main_menu.play_button.set_click_handler(start_game, this);
   main_menu.exit_button.set_click_handler(exit_game, nullptr);
   display = &main_menu;
}


void GameContext::loop()
{
   SDL_Event e;

   while ( globals.run ) {

      while ( SDL_PollEvent(&e) ) display->handle_event(&e);

      if ( game_running ) {
         game_running = game.do_tick();
         if ( !game_running ) display = &main_menu;
      }

      SDL_RenderClear(globals.renderer());
      display->render();
      SDL_RenderPresent(globals.renderer());

      SDL_Delay(globals.tick());
   }
}
