#include "game.hpp"
#include "globals.hpp"
#include "util.hpp"
#include <time.h>


Game::Game(int font_size, int hp)
   : mfont_size(font_size), player(font_size*1.2, hp)
{ }


void Game::reset()
{
   mover = false;
   player.reset();
   mwords.clear();
   mtick = 0;
}


void Game::move_words()
{
   for ( int i = 0; i < mwords.size(); ++i ) {

      if ( !mwords[i].move() ) {
         mwords.erase(mwords.begin() + i);
         --i;
      }

   }
}


void Game::spawn_word()
{
   if ( mtick % 18 != 0 ) return;
   Direction dir = Direction((mtick / 18) % 4);

   auto pair = globals.config.random_word_combo();

   int font_index = rand() % globals.fonts().size();
   const Font * font = &globals.fonts()[font_index];

   int quarter = mfont_size / 4;
   int fontsize = (mfont_size + quarter) - rand() % (mfont_size / 2);

   Word word(pair.first, fontsize, pair.second, font, dir);
   mwords.emplace_back(std::move(word));
}


void Game::end()
{
   if ( player.score() > globals.highscore ) globals.highscore = player.score();
   globals.reset_speed();

   mover = true; 
}


bool Game::do_tick()
{
   ++mtick;

   move_words();
   spawn_word();
   
   for ( Word &w : mwords ) {
      if ( rect_intersect(player.collision_rect(), w.rect()) ) player.eat_letters(w);
   } 

   if ( player.health() <= 0 ) end();

   return !mover;
}


const std::vector<Word>& Game::words() const { return mwords; }


bool Game::over() const { return mover; }
