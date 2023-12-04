#ifndef SILLYCAT_PLAYER_HEADER
#define SILLYCAT_PLAYER_HEADER

#include "word.hpp"
#include "effects.hpp"
#include "direction.hpp"

#include <SDL2/SDL.h>


class Player {

 public:
   void reset();
   Player(int size, int hp);

   void apply_effect(Effect effect);
   bool move(Direction dir);
   void eat_letters(Word &word);

   SDL_Rect collision_rect() const;
   SDL_Rect rect() const;

   int health() const;
   int score() const;

 private:
   int mstarting_health;
   bool mmoving = false;

   SDL_Rect mcollision_rect;
   SDL_Rect mrect;
   int mhealth;

   int mscore = 0;

};

#endif
