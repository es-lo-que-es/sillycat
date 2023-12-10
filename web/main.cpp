#include <emscripten.h>
#include <emscripten/html5.h>

#include "game_context.hpp"
#include "globals.hpp"
#include <stdio.h>


Globals globals;

const int player_hp = 9;
const int tick = 24;

const SDL_Rect rect = { 0, 0, 600, 600 };


void emscripten_loop(void * par)
{
   SDL_Event e;
   GameContext * ctx = (GameContext*) par;

   while ( SDL_PollEvent(&e) ) ctx->display->handle_event(&e);

   if ( ctx->game_running ) {
      ctx->game_running = ctx->game.do_tick();
      if ( !ctx->game_running ) ctx->display = &ctx->main_menu;
   }

   SDL_RenderClear(globals.renderer());
   ctx->display->render();
   SDL_RenderPresent(globals.renderer());
}


int main()
{
   int speed = rect.w / 100;
   int font_size = rect.w / 16;

   globals.init(rect, tick, speed);
   GameContext * ctx = new GameContext(rect, font_size, player_hp);

   emscripten_set_main_loop_arg(&emscripten_loop, ctx, globals.tick(), 0);

   return 0;
}
