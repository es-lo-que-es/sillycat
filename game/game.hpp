#ifndef SILLYCAT_GAME_HEADER
#define SILLYCAT_GAME_HEADER

#include "word.hpp"
#include "player.hpp"

#include <vector>
#include <chrono>


class Game {

 public:
   void reset();
   Player player;
   Game(int font_size, int hp);

   const std::vector<Word>& words() const;
   bool over() const;

   bool move_player(Direction dir);
   bool do_tick();
   void end();

 private:
   void move_words();
   void spawn_word();
   std::vector<Word> mwords;

   std::chrono::time_point<std::chrono::high_resolution_clock> mtpoint;
   static const unsigned int mspawn_period = 384;
   Direction mlast_dir = Direction::Up;

   bool mover = false;
   int mfont_size;
};



#endif
