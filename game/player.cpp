#include "player.hpp"
#include "globals.hpp"
#include "util.hpp"


SDL_Rect Player::rect() const { return mrect; }


SDL_Rect Player::collision_rect() const { return mcollision_rect; }


int Player::score() const { return mscore; }


int Player::health() const { return mhealth; }


Player::Player(int size, int hp)
   : mstarting_health(hp)
{
   mrect = { 0, 0, size, size }; 
   reset();
}


void Player::reset()
{
   center_rect(mrect, globals.rect());

   int col_size = mrect.w / 2;
   int offs = col_size / 2;

   mcollision_rect = { mrect.x + offs, mrect.y + offs, col_size, col_size };

   mhealth = mstarting_health;
   mscore = 0;
}


bool Player::move(Direction dir)
{

   int s = globals.speed();
   SDL_Rect border = globals.rect();
   
   border.w -= mrect.w;
   border.h -= mrect.h;

   switch ( dir ) {

      case Right:
         if ( (mrect.x + s) > border.w ) return false; 
         mcollision_rect.x += s;
         mrect.x += s; 
         break;

      case Left:
         if ( (mrect.x - s) < border.x ) return false; 
         mcollision_rect.x -= s; 
         mrect.x -= s; 
         break;

      case Down:
         if ( (mrect.y + s) > border.h ) return false; 
         mcollision_rect.y += s;
         mrect.y += s; 
         break;

      case Up:
         if ( (mrect.y - s) < border.y ) return false; 
         mcollision_rect.y -= s; 
         mrect.y -= s; 
         break;
   }
   
   return true;
}


void Player::apply_effect(Effect effect)
{
   if ( effect.type == Random ) {
      effect.type = (EffectType)(rand() % (EFFECT_TYPE_COUNT-1));
      if ( effect.type == Death ) effect = { Health, -1 };
   }

   if ( globals.inverted() ) effect.value *= -1;

   switch ( effect.type ) {
      case Health: mhealth += effect.value; break;
      case Death: mhealth = 0; break;
      case Points: mscore += effect.value; break;
      case Speed: globals.mod_speed(effect.value); break;
      case Invert: globals.invert(); break;

      default: break;
   } 
}


void Player::eat_letters(Word &w)
{
   SDL_Rect r = w.rect(); 
   r.w = r.h = w.font_size();

   Direction dir = w.dir() == Up || w.dir() == Left ? rev(w.dir()) : w.dir();

   for ( Letter &l : w.letters ) {

      if ( l.ch != 0 ) {
         if ( rect_intersect( r, mcollision_rect) ) {
            apply_effect(l.effect);
            l.ch = 0;
         }
      }

      move_rect(r, w.font_size(), dir);
   }
}
