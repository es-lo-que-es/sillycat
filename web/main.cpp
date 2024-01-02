#include <emscripten.h>
#include <emscripten/html5.h>

#include "game_context.hpp"
#include "globals.hpp"
#include <stdio.h>


Globals globals;

const int player_hp = 9;
const int tick = 32;

const SDL_Rect rect = { 0, 0, 600, 600 };


bool flag = false;
// i have no clue how to do frame pacing with emscripten 
EM_BOOL emscripten_loop(double time, void * par)
{
   SDL_Event e;
   GameContext * ctx = (GameContext*) par;
   
   if ( flag ) {
      while ( SDL_PollEvent(&e) ) ctx->display->handle_event(&e);

      if ( ctx->game_running ) {
         ctx->game_running = ctx->game.do_tick();
         if ( !ctx->game_running ) ctx->display = &ctx->main_menu;
      }

      SDL_RenderClear(globals.renderer());
      ctx->display->render();

   } else {
      SDL_RenderPresent(globals.renderer());
   }

   flag = !flag;
   emscripten_request_animation_frame(&emscripten_loop, ctx);

   return EM_TRUE;
}


int main()
{
   int speed = rect.w / 65;
   int font_size = rect.w / 16;

   globals.init(rect, tick, speed);
   GameContext * ctx = new GameContext(rect, font_size, player_hp);

   emscripten_request_animation_frame(&emscripten_loop, ctx);

   return 0;
}
