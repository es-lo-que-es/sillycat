#include "game_context.hpp"
#include "game_display.hpp"
#include "globals.hpp"
#include "menus.hpp"
#include <chrono>
#include <cmath>


void exit_game(void * par)
{
   /*UNUSED*/ (void) par;
   globals.run = false;
}


void switch_mute(void * par)
{
   /*UNUSED*/ (void) par;
   globals.audio.switch_mute();
}


void start_game(void * par)
{
   GameContext * ctx = (GameContext * ) par;
   ctx->display = &ctx->game_display;

   ctx->game.reset();
   ctx->game_display.reset();

   ctx->game_running = true;
}


GameContext::GameContext(SDL_Rect r, int size, int hp)
   : game(size, hp),
     game_display(&game, r),
     main_menu(r)
{
   main_menu.play_button.set_click_handler(start_game, this);
   main_menu.sound_switch.set_click_handler(switch_mute, nullptr);
   main_menu.exit_button.set_click_handler(exit_game, nullptr);
   display = &main_menu;
}


void GameContext::loop()
{
   SDL_Event e;
   using namespace std::chrono;

   while ( globals.run ) {

      auto fstart = high_resolution_clock::now();

      while ( SDL_PollEvent(&e) ) display->handle_event(&e);
      
      if ( game_running ) {
         game_running = game.do_tick();
         if ( !game_running ) display = &main_menu;
      }
      
      SDL_RenderClear(globals.gui.renderer());
      display->render();

      auto fend = high_resolution_clock::now();
      std::chrono::duration<double, std::milli> elapsed = fend - fstart;

      int delay = globals.gui.tick() - std::round(elapsed.count());
      SDL_Delay(delay > 0 ? delay : 0);

      SDL_RenderPresent(globals.gui.renderer());
   }
}
