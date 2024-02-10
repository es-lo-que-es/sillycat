#include "game.hpp"
#include "globals.hpp"
#include "util.hpp"
#include <chrono>
#include <time.h>


Game::Game(int font_size, int hp)
   : player(font_size*1.2, hp),
     mfont_size(font_size)
{ }


void Game::reset()
{
   mtpoint = std::chrono::time_point<std::chrono::high_resolution_clock>();

   player.reset();
   mwords.clear();

   mover = false;
}


void Game::move_words()
{
   for ( size_t i = 0; i < mwords.size(); ++i ) {

      if ( !mwords[i].move() ) {
         mwords[i] = std::move(mwords.back());
         mwords.pop_back();
         --i;
      }

   }
}


void Game::spawn_word()
{
   auto now = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> elapsed = now - mtpoint;

   if ( elapsed.count() < mspawn_period ) return;

   auto pair = globals.config.random_word_combo();

   int font_index = rand() % globals.gui.fonts().size();
   const Font * font = &globals.gui.fonts()[font_index];

   int quarter = mfont_size / 4;
   int fontsize = (mfont_size + quarter) - rand() % (mfont_size / 2);

   Word word(pair.first, fontsize, pair.second, font, mlast_dir);
   mwords.emplace_back(std::move(word));

   mlast_dir = inc(mlast_dir);
   mtpoint = now;
}


void Game::end()
{
   if ( player.score() > globals.highscore ) globals.highscore = player.score();
   globals.audio.play_sound(SoundName::Death);
   globals.reset();
   mover = true; 
}


bool Game::do_tick()
{
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
