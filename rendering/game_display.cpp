#include "game_display.hpp"
#include "direction.hpp"
#include "game.hpp"
#include "globals.hpp"
#include "util.hpp"


void GameDisplay::reset()
{
   mscore_label.update(mgame->player.score());
   mhealth_bar.update(mgame->player.health());

   active_directions.fill(0);
   indicator.reset();
}


void close_button_handler(void * par)
{
   Game * game = (Game*) par;
   game->end();
}


GameDisplay::GameDisplay(Game * game, SDL_Rect rect)
   : Display(rect), 
     indicator(rect),
     mplayer_sprite(globals.gui.textures[TextureName::Cat], globals.gui.tick()*7, 64)
{
   mgame = game;
   mscore_label.init("score:", {rect.x, rect.y, rect.w, 20}, 14);
   mclose_button.init("X", {rect.w - 48, 8, 40, 40});
   mhealth_bar.init("hp:", {rect.x, rect.y, 100, 20}, 14);

   mclose_button.set_click_handler(close_button_handler, game);

   children.push_back(&indicator);
   children.push_back(&mclose_button);
   children.push_back(&mscore_label);
   children.push_back(&mhealth_bar);
}


void GameDisplay::render_player()
{
   SDL_Rect r = mgame->player.rect();
   mplayer_sprite.render(&r);
}


void GameDisplay::update_scores()
{
   int diff = mscore_label.score() - mgame->player.score();

   if ( diff != 0 ) {
      mscore_label.update(mgame->player.score());
      indicator.indicate( diff < 0 ? Indication::PointGain : Indication::PointLoss);
   }

   diff = mhealth_bar.score() - mgame->player.health();

   if ( diff != 0 ) {
      mhealth_bar.update(mgame->player.health());
      indicator.indicate( diff < 0 ? Indication::HpGain : Indication::HpLoss);
   }
}


void GameDisplay::render()
{
   for ( const Word & w : mgame->words() ) {
      
      SDL_Rect r = w.rect();
      r.w = r.h = w.font_size();

      Direction dir = uleft_direction(w.dir()) ? rev(w.dir()) : w.dir();

      for ( const Letter &l : w.letters ) {

         l.render(&r);
         move_rect(r, r.w, dir);

      }
   }

   for ( int i = 0; i < 4; ++i ) {
      if ( active_directions[i] ) mgame->player.move(Direction(i));
   }

   update_scores();
   render_player();

   Display::render();
}


void GameDisplay::handle_event(SDL_Event * e)
{
   Direction dir;
   Display::handle_event(e);

   switch ( e->key.keysym.sym ) {
      case SDLK_LEFT: case SDLK_a: dir = Direction::Left; break;
      case SDLK_RIGHT: case SDLK_d: dir = Direction::Right; break;
      case SDLK_UP: case SDLK_w: dir = Direction::Up; break;
      case SDLK_DOWN: case SDLK_s: dir = Direction::Down; break;
      default: return;
   }

   int index = (int)dir;
   if ( e->type == SDL_KEYDOWN ) active_directions[index] = true;
   else if ( e->type == SDL_KEYUP ) active_directions[index] = false;
}
